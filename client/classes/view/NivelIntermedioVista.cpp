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


void NivelIntermedioVista::renderEsperaJugador(JugadorVista* jugador, char* nombre, Vector offset, int colorTexto) {
	Vector posicionJugadorBase = Vector(ancho / 3, alto * 1 / 12);
	Vector posicionNombreBase = Vector(ancho * 7 / 15, alto * 1 / 12 + JUGADOR_SRC_ALTO / 3);
	struct EstadoJugador estado = generarEstadoJugador(posicionJugadorBase + offset);

	if (strlen(nombre) > 0) {
		estado.presente = true;
		TextoVista::eRender(std::string(nombre), posicionNombreBase + offset, colorTexto, ALINEACION_IZQUIERDA);
	} else {
		estado.presente = false;
	}
	jugador->render(estado);
}


void NivelIntermedioVista::renderEstadoLogin(struct EstadoLogin estadoLogin) {
	setViewport(ancho, alto);
	for (int i = 0; i < estadoLogin.cantidadJugadores ; i++) {
		Vector offset = Vector(0, alto * 7 / 12) / estadoLogin.cantidadJugadores * i;
		renderEsperaJugador((*jugadores)[i], estadoLogin.jugadores[i], offset, i + 1);
	}

	if (estadoLogin.estadoLogin == LOGIN_ESPERAR) {
		TextoVista::eRender(std::string("ESPERANDO JUGADORES..."), Vector(ancho / 2, alto * 5 / 7), TEXTO_COLOR_NARANJA, ALINEACION_CENTRO);
	} else if (estadoLogin.estadoLogin == LOGIN_COMENZAR) {
		TextoVista::eRender(std::string("COMENZANDO PARTIDA..."), Vector(ancho / 2, alto * 5 / 7), TEXTO_COLOR_VERDE, ALINEACION_CENTRO);
	}
}

void NivelIntermedioVista::renderNivelIntermedio(struct EstadoTick estadoTick) {
	setViewport(ancho, alto);
	int cantidadJugadores = 0;

	for (auto & estadosJugador : estadoTick.estadosJugadores) {
		if (strlen(estadosJugador.usuario) > 0) {
			cantidadJugadores++;
		}
	}

	for (int i = 0; i < cantidadJugadores; i++) {
		EstadoJugador estado = estadoTick.estadosJugadores[i];
		Vector offset = Vector(0, alto * 8 / 12) / cantidadJugadores * i - Vector(ancho / 5, 0);
		renderEsperaJugador((*jugadores)[i], estado.usuario, offset, i + 1);

		Vector posicionPuntajeBase = Vector(ancho * 12 / 15, alto * 1 / 12 + JUGADOR_SRC_ALTO / 3);
		TextoVista::eRender(std::to_string(estado.puntos), posicionPuntajeBase + offset, TEXTO_COLOR_NARANJA, ALINEACION_IZQUIERDA);
	}

	std::string texto = "COMENZANDO PROXIMO NIVEL...";
	if (estadoTick.numeroNivel == -1) {
		texto = "JUEGO FINALIZADO!";
	}
	TextoVista::eRender(texto, Vector(ancho / 2, alto * 5 / 7), TEXTO_COLOR_VERDE, ALINEACION_CENTRO);
}
