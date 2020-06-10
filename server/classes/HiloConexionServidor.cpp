#include "HiloConexionServidor.h"
#include "../../commons/utils/Log.h"

HiloConexionServidor::HiloConexionServidor(ConexionServidor* conexionServidor) {
	this->conexionServidor = conexionServidor;
}

void HiloConexionServidor::run() {
	l->info("Comenzando a correr HiloConexionServidor");

	nlohmann::json mensajeRecibido = conexionServidor->recibirMensaje();
	l->error("!!!! recHiloConexionServidor " + mensajeRecibido.dump());
	colaReceptora->push(mensajeRecibido);

	while (true) {

		nlohmann::json mensajeRecibido = conexionServidor->recibirMensaje();
		//l->error("!!!! recHiloConexionServidor " + mensajeRecibido.dump());
		colaReceptora->push(mensajeRecibido);

		//l->error("!!!! whileHiloConexionServidor");
		if (!colaEnviadora->empty()) {
			nlohmann::json mensajeAEnviar = colaEnviadora->pop();
		//	l->error("!!!! envHiloConexionServidor " + mensajeAEnviar.dump());
			conexionServidor->enviarMensaje(mensajeAEnviar);

		} else {
			l->error("!!!! colaVacia");
			continue;
		}

	}
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
}
