//
// Created by camix on 4/5/20.
//

#include "NivelIntermedioVista.h"
#include "../GraphicRenderer.h"
#include "TextoVista.h"
#include "HudVista.h"
#include <string>

NivelIntermedioVista::NivelIntermedioVista(std::vector<JugadorVista*>* jugadores, int ancho, int alto) {
    NivelIntermedioVista::gRenderer = GraphicRenderer::getInstance();
	NivelIntermedioVista::jugadores = jugadores;
	NivelIntermedioVista::ancho = ancho;
	NivelIntermedioVista::alto = alto;
	NivelIntermedioVista::campoVista = new CampoVista(2, -1);
	campoVista->nuevoFondo("dungeon_3.png", 0, 0, 3.5);
	campoVista->nuevoFondo("dungeon_5.png", 0, 0, 4.75);
	campoVista->nuevoFondo("dungeon_4.png", 0, 0, 5.5);

    l->info("La vista del Nivel Intermedio fue creada correctamente.");
}


// Funcion para generar el estado del jugador y los helpers a partir de un vector posicion.
// Utilizado para la pantalla de espera.
struct EstadoJugador generarEstadoJugador(Vector posicion) {
	struct EstadoJugador estadoJugador;
	estadoJugador.posicionX = posicion.getX();
	estadoJugador.posicionY = posicion.getY();
	estadoJugador.presente = true;

	// Sin helpers
	Vector posicionHelper1 = posicion + Vector(-10000, -10000);
	estadoJugador.helper1.posicionX = posicionHelper1.getX();
	estadoJugador.helper1.posicionY = posicionHelper1.getY();

	Vector posicionHelper2 = posicion + Vector(-10000, -10000);
	estadoJugador.helper2.posicionX = posicionHelper2.getX();
	estadoJugador.helper2.posicionY = posicionHelper2.getY();

	// Estos son valores dummies que no se usan
	estadoJugador.energia = 0;
	estadoJugador.cantidadVidas = 3;
	estadoJugador.esInvencible = false;

	// Sin esto no se renderiza el jugador.
	estadoJugador.estaMuerto = false;

	return estadoJugador;
}


void setViewport(int ancho, int alto) {
	// Render Campo
	SDL_Rect posCampo = { 0, HUD_SRC_ALTO, ancho, alto };
	SDL_RenderSetViewport(GraphicRenderer::getInstance(), &posCampo);
}

void NivelIntermedioVista::renderComun() {
	setViewport(ancho, alto);
	EstadoTick estadoTick;
	estadoTick.posX = 1;
	estadoTick.numeroNivel = -1;
	campoVista->render(estadoTick);
}

void NivelIntermedioVista::renderEsperaJugador(JugadorVista* jugador, char* nombre, Vector posicionJugador, struct TextoVistaParams params, int estaMuerto) {
	struct EstadoJugador estado = generarEstadoJugador(posicionJugador);

	if (strlen(nombre) > 0) {
		estado.presente = !estaMuerto;
		TextoVista::eRender(std::string(nombre), params);
	} else {
		estado.presente = false;
	}
	jugador->render(estado);
}

void NivelIntermedioVista::renderEstadoLogin(struct EstadoLogin estadoLogin) {
	renderComun();

	struct TextoVistaParams params;
	for (int i = 0; i < estadoLogin.cantidadJugadores ; i++) {
		Vector posicionJugador = Vector(ancho / 3, alto * 1 / 12 + alto * 2 / 3 / estadoLogin.cantidadJugadores * i);
		Vector posicionNombre = posicionJugador + Vector(ancho * 2 / 15, JUGADOR_SRC_ALTO / 3);
		params = TextoVistaParams(posicionNombre, i + 1, ALINEACION_IZQUIERDA);
		renderEsperaJugador((*jugadores)[i], estadoLogin.jugadores[i], posicionJugador, params, false);
	}

	params = TextoVistaParams(Vector(ancho / 2, alto * 5 / 7), TEXTO_COLOR_NARANJA, ALINEACION_CENTRO);
	if (estadoLogin.estadoLogin == LOGIN_ESPERAR) {
		TextoVista::eRender(std::string("ESPERANDO JUGADORES..."), params);
	} else if (estadoLogin.estadoLogin == LOGIN_COMENZAR) {
		params.color = TEXTO_COLOR_VERDE;
		TextoVista::eRender(std::string("COMENZANDO PARTIDA..."), params);
	}
}

void NivelIntermedioVista::actualizarEstadoTick(struct EstadoTick tick) {
	if (tick.numeroNivel != estadoTick.numeroNivel) {
		estadoTick = tick;
		for (auto & estadoJugador : estadoTick.estadosJugadores) {
			estadoJugador.puntos = 0;
		}
	}

	for (int i = 0; i < MAX_JUGADORES; i++) {
		estadoTick.estadosJugadores[i].puntos += tick.estadosJugadores[i].puntos / (TIMEOUT_PROXIMO_NIVEL / 3 * 60);
		if (tick.estadosJugadores[i].puntos < estadoTick.estadosJugadores[i].puntos) {
			estadoTick.estadosJugadores[i].puntos = tick.estadosJugadores[i].puntos;
		}
	}
}

void NivelIntermedioVista::renderNivelIntermedio(struct EstadoTick nuevoTick) {
	renderComun();
	actualizarEstadoTick(nuevoTick);

	int cantidadJugadores = 0;
	for (auto & estadosJugador : estadoTick.estadosJugadores) {
		if (strlen(estadosJugador.usuario) > 0) {
			cantidadJugadores++;
		}
	}

	for (int i = 0; i < cantidadJugadores; i++) {
		EstadoJugador estado = estadoTick.estadosJugadores[i];
		Vector posicionJugador = Vector( -JUGADOR_SRC_ANCHO / 2, alto / 8);
		if (cantidadJugadores % 2 != 0) {
			posicionJugador = posicionJugador + Vector(ancho  * (i + 1) / (cantidadJugadores + 1), 0);
		} else {
			posicionJugador = posicionJugador + Vector(ancho  * (2 * i + 1) / (cantidadJugadores * 2), 0);
		}
		Vector posicionTexto = posicionJugador + Vector(JUGADOR_SRC_ANCHO / 2 - LETRA_ANCHO / 2, JUGADOR_SRC_ALTO * 3 / 2);

		struct TextoVistaParams params = TextoVistaParams(posicionTexto, i + 1, ALINEACION_CENTRO);
		renderEsperaJugador((*jugadores)[i], estado.usuario, posicionJugador, params, estado.estaMuerto);

		params.posicion = params.posicion + Vector(0, LETRA_ALTO);
		params.color = TEXTO_COLOR_NARANJA;
		for (int puntosParcial : estado.puntosParciales) {
			params.posicion = params.posicion + Vector(0, LETRA_ALTO * 3 / 2);
			params.size = TEXTO_SIZE_SMALL;
			TextoVista::eRender("+" + std::to_string(puntosParcial), params);
		}

		params.posicion = params.posicion + Vector(0, LETRA_ALTO * 2);
		params.color = TEXTO_COLOR_ROJO;
		TextoVista::eRender(std::to_string(estado.puntos), params);
	}

	std::string texto = "COMENZANDO PROXIMO NIVEL...";
	if (estadoTick.numeroNivel == -1) {
		texto = "JUEGO FINALIZADO!";
	}

	struct TextoVistaParams params = TextoVistaParams(Vector(ancho / 2, alto * 5 / 7), TEXTO_COLOR_VERDE, ALINEACION_CENTRO);
	TextoVista::eRender(texto, params);
}
