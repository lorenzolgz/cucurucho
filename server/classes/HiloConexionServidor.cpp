#include "HiloConexionServidor.h"
#include "../../commons/utils/Log.h"
#include "../../commons/connections/ControladorDeSesiones.h"

HiloConexionServidor::HiloConexionServidor(ConexionServidor* conexionServidor, int jugador, std::string username) {
	this->conexionServidor = conexionServidor;
	this->jugador = jugador;
	this->username = username;
	this->activo = true;
	this->continuarLoopeando = true;
}

void HiloConexionServidor::run() {
	l->info("Comenzando a correr HiloConexionServidor.");

	try{
		// !!!! Sirve repetir esto?
        nlohmann::json mensajeRecibido = conexionServidor->recibirMensaje();
        l->debug("recHiloConexionServidor " + mensajeRecibido.dump());
        colaReceptora->push(mensajeRecibido);

        while (continuarLoopeando) {
            nlohmann::json mensajeRecibido = conexionServidor->recibirMensaje();
            l->debug("recHiloConexionServidor " + mensajeRecibido.dump());
            colaReceptora->push(mensajeRecibido);

            while (colaEnviadora->size() > MAX_COLA_EMISORA_SERVIDOR) {
                nlohmann::json json = colaEnviadora->pop();
                // Solo se deberian matar los mensajes de ESTADO_TICK
                if (json["tipoMensaje"] != ESTADO_TICK) {
                    colaEnviadora->push_back(json);
                    break;
                }
            }

            if (!colaEnviadora->empty()) {
                nlohmann::json mensajeAEnviar = colaEnviadora->pop();
                l->debug("envHiloConexionServidor " + mensajeAEnviar.dump());
                conexionServidor->enviarMensaje(mensajeAEnviar);
            }
        }
    } catch (...) { // !!!!! catcheo y logueo
		l->error("Error en el loop de HiloConexionServidor.");
	    cicloReconectar();
	}

	l->info("Se termino el HiloConexionServidor.");
}

void HiloConexionServidor::enviarEstadoTick(struct EstadoTick* estadoTick) {

	nlohmann::json mensajeJson;
	mensajeJson["tipoMensaje"] = ESTADO_TICK;
	mensajeJson["numeroNivel"] = estadoTick->nuevoNivel;
	int i = 0, j = 0;
	// TODO enviar solo los enemigos necesarios. Ya no tiene que ser un struct con un array de largo fijo, porque el JSON es dinamico.
	for (; i< MAX_JUGADORES; i++) {
		mensajeJson["estadosJugadores"][i]["helper1"]["posicionX"] = estadoTick->estadosJugadores[i].helper1.posicionX;
		mensajeJson["estadosJugadores"][i]["helper1"]["posicionY"] = estadoTick->estadosJugadores[i].helper1.posicionY;
		mensajeJson["estadosJugadores"][i]["helper1"]["angulo"] = estadoTick->estadosJugadores[i].helper1.angulo;
		mensajeJson["estadosJugadores"][i]["helper2"]["posicionX"] = estadoTick->estadosJugadores[i].helper2.posicionX;
		mensajeJson["estadosJugadores"][i]["helper2"]["posicionY"] = estadoTick->estadosJugadores[i].helper2.posicionY;
		mensajeJson["estadosJugadores"][i]["helper2"]["angulo"] = estadoTick->estadosJugadores[i].helper2.angulo;
		mensajeJson["estadosJugadores"][i]["posicionX"] = estadoTick->estadosJugadores[i].posicionX;
		mensajeJson["estadosJugadores"][i]["posicionY"] = estadoTick->estadosJugadores[i].posicionY;
        mensajeJson["estadosJugadores"][i]["presente"] = estadoTick->estadosJugadores[i].presente;
    }
	for (; j< MAX_ENEMIGOS; j++) {
		mensajeJson["estadosEnemigos"][j]["posicionX"] = estadoTick->estadosEnemigos[j].posicionX;
		mensajeJson["estadosEnemigos"][j]["posicionY"] = estadoTick->estadosEnemigos[j].posicionY;
		mensajeJson["estadosEnemigos"][j]["clase"] = estadoTick->estadosEnemigos[j].clase;
	}

	colaEnviadora->push(mensajeJson);
}

void HiloConexionServidor::enviarInformacionNivel(struct InformacionNivel* informacionNivel) {

	nlohmann::json mensajeJson = {
			{"tipoMensaje", INFORMACION_NIVEL},
			{"numeroNivel",  informacionNivel->numeroNivel},
			{"velocidad", informacionNivel->velocidad},
			{"informacionFinNivel",   informacionNivel->informacionFinNivel}
	};
	for ( int i = 0 ; i < MAX_FONDOS ; i++ ){
		mensajeJson["informacionFondo"][i]["velocidad"] = informacionNivel->informacionFondo[i].pVelocidad;
		mensajeJson["informacionFondo"][i]["fondo"] = informacionNivel->informacionFondo[i].pFondo;
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
