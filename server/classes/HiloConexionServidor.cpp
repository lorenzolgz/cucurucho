#include "HiloConexionServidor.h"
#include "../../commons/connections/ControladorDeSesiones.h"

HiloConexionServidor::HiloConexionServidor(ConexionServidor *conexionServidor, int jugador, std::string username,
                                           Configuracion *config) {
	this->conexionServidor = conexionServidor;
	this->jugador = jugador;
	this->username = username;
	this->activo = true;
	this->config = config;
	this->continuarLoopeando = true;
}

void HiloConexionServidor::run() {
	l->info("Comenzando a correr HiloConexionServidor.");
	this->conexionServidor->enableTimeout();

	try{
        while (continuarLoopeando || !colaEnviadora->empty()) {
            nlohmann::json mensajeRecibido = conexionServidor->recibirMensaje();
            l->debug("recHiloConexionServidor " + mensajeRecibido.dump());
            colaReceptora->push(mensajeRecibido);

            while (colaEnviadora->size() > config->getMaxColaEmisora() && continuarLoopeando) {
                nlohmann::json json = colaEnviadora->pop();
                // Solo se deberian matar los mensajes de ESTADO_TICK que no indican fin del juego
                // TODO: quiero llorar
                if (json["tipoMensaje"] != ESTADO_TICK || json["numeroNivel"] == FIN_DE_JUEGO) {
                    colaEnviadora->push_back(json);
                    break;
                }
                l->debug("desencolandoMensaje " + json.dump());
            }

            if (!colaEnviadora->empty()) {
                nlohmann::json mensajeAEnviar = colaEnviadora->pop();
                conexionServidor->enviarMensaje(mensajeAEnviar);
                l->debug("envHiloConexionServidor " + mensajeAEnviar.dump());
            }
        }
    } catch (...) { // !!!! catcheo y logueo
		l->error("Error en el loop de HiloConexionServidor.");
	    cicloReconectar();
	}

	l->info("Se termino el HiloConexionServidor.");
}

void HiloConexionServidor::enviarEstadoTick(struct EstadoTick* estadoTick) {

	nlohmann::json mensajeJson;
	mensajeJson["tipoMensaje"] = ESTADO_TICK;
	mensajeJson["nuevoNivel"] = estadoTick->nuevoNivel;
	mensajeJson["numeroNivel"] = estadoTick->numeroNivel;
	mensajeJson["posX"] = estadoTick->posX;
	int i = 0;

	for (; i< MAX_JUGADORES; i++) {
		mensajeJson["estadosJugadores"][i]["helper1"]["posicionX"] = estadoTick->estadosJugadores[i].helper1.posicionX;
		mensajeJson["estadosJugadores"][i]["helper1"]["posicionY"] = estadoTick->estadosJugadores[i].helper1.posicionY;
		mensajeJson["estadosJugadores"][i]["helper1"]["angulo"] = estadoTick->estadosJugadores[i].helper1.angulo;
		mensajeJson["estadosJugadores"][i]["helper2"]["posicionX"] = estadoTick->estadosJugadores[i].helper2.posicionX;
		mensajeJson["estadosJugadores"][i]["helper2"]["posicionY"] = estadoTick->estadosJugadores[i].helper2.posicionY;
		mensajeJson["estadosJugadores"][i]["helper2"]["angulo"] = estadoTick->estadosJugadores[i].helper2.angulo;
		mensajeJson["estadosJugadores"][i]["posicionX"] = estadoTick->estadosJugadores[i].posicionX;
		mensajeJson["estadosJugadores"][i]["posicionY"] = estadoTick->estadosJugadores[i].posicionY;
		mensajeJson["estadosJugadores"][i]["energia"] = estadoTick->estadosJugadores[i].energia;
		mensajeJson["estadosJugadores"][i]["cantidadVidas"] = estadoTick->estadosJugadores[i].cantidadVidas;
		mensajeJson["estadosJugadores"][i]["esInvencible"] = estadoTick->estadosJugadores[i].esInvencible;
		mensajeJson["estadosJugadores"][i]["estaMuerto"] = estadoTick->estadosJugadores[i].estaMuerto;
		mensajeJson["estadosJugadores"][i]["presente"] = estadoTick->estadosJugadores[i].presente;
		mensajeJson["estadosJugadores"][i]["puntos"] = estadoTick->estadosJugadores[i].puntos;
		mensajeJson["estadosJugadores"][i]["usuario"] = std::string(estadoTick->estadosJugadores[i].usuario);
		for (int puntajeParcial : estadoTick->estadosJugadores[i].puntosParciales) {
			mensajeJson["estadosJugadores"][i]["puntosParciales"].push_back(puntajeParcial);
		}
	}
	for (EstadoEnemigo estadoEnemigo : estadoTick->estadosEnemigos) {
        nlohmann::json mensajeEnemigo = {
				{"posicionX", estadoEnemigo.posicionX},
				{"posicionY", estadoEnemigo.posicionY},
				{"energia", estadoEnemigo.energia},
				{"clase", estadoEnemigo.clase},
				{"anguloDir", estadoEnemigo.anguloDir}
        };
        mensajeJson["estadosEnemigos"].push_back(mensajeEnemigo);

	}
    for (EstadoDisparo estadoDisparo : estadoTick->estadosDisparos) {
        nlohmann::json mensajeDisparo = {
				{"posicionX", estadoDisparo.posicionX},
				{"posicionY", estadoDisparo.posicionY},
				{"nroJugador", estadoDisparo.nroJugador},
				{"energia", estadoDisparo.energia},
                {"inicio", estadoDisparo.inicio}
        };
        mensajeJson["estadosDisparos"].push_back(mensajeDisparo);
    }

    for (EstadoDisparo estadoDisparoEnemigo: estadoTick->estadosDisparosEnemigos){
        nlohmann::json mensajeDisparo = {
                {"posicionX", estadoDisparoEnemigo.posicionX},
                {"posicionY", estadoDisparoEnemigo.posicionY},
                {"nroJugador", estadoDisparoEnemigo.nroJugador},
				{"energia", estadoDisparoEnemigo.energia},
                {"inicio",estadoDisparoEnemigo.inicio}
        };
        mensajeJson["estadosDisparosEnemigos"].push_back(mensajeDisparo);
    }
    colaEnviadora->push(mensajeJson);
}

void HiloConexionServidor::enviarInformacionNivel(struct InformacionNivel* informacionNivel) {

	nlohmann::json mensajeJson = {
				{"tipoMensaje", INFORMACION_NIVEL},
				{"numeroNivel",  informacionNivel->numeroNivel},
				{"velocidad", informacionNivel->velocidad},
				{"informacionFinNivel",   informacionNivel->informacionFinNivel},
				{"audioNivel", informacionNivel->audioNivel}
	};
	for (InformacionFondo informacionFondo: informacionNivel->informacionFondo){
        nlohmann::json mensajeFondo= {
				{"velocidad", informacionFondo.pVelocidad},
				{"fondo", informacionFondo.pFondo}
        };
	    mensajeJson["informacionFondo"].push_back(mensajeFondo);
	}
	colaEnviadora->push(mensajeJson);

	HiloConexionServidor::informacionNivelActual = informacionNivel;
}

void HiloConexionServidor::cicloReconectar() {
    this->activo = false;
    this->conexionServidor->cerrar();
    this->conexionServidor->setClientSocket(-1);
    l->error("Cliente " + this->username + " perdio la conexion.");

    while (this->conexionServidor->getClientSocket() < 0) {
    	if (!continuarLoopeando) {
			return;
    	}
        std::this_thread::sleep_for(std::chrono::milliseconds(150));
    }

    l->info("Cliente " + this->username + " reconectado.");

    this->activo = true;
    while (this->colaEnviadora->size() != 0) {
    	this->colaEnviadora->pop();
    }

    try {
		if (!continuarLoopeando) {
			return;
		}

		this->enviarInformacionNivel(this->informacionNivelActual);
    } catch (...) {
        cicloReconectar();
        return;
    }

    run();
}

void HiloConexionServidor::terminar() {
	continuarLoopeando = false;
}
