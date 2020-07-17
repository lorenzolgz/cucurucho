#include "HudVista.h"
#include "../GeneradorDeTexturas.h"
#include "../GraphicRenderer.h"
#include "ManagerVista.h"
#include <string>
#include "../../../commons/utils/Constantes.h"

const char VIDA_NAVE_IZQ = 30;
const char VIDA_NAVE_DER = 31;

HudVista::HudVista() {
	this->gRenderer = GraphicRenderer::getInstance();
    GeneradorDeTexturas *generadorDeTexturas = GeneradorDeTexturas::getInstance();
    this->textura = generadorDeTexturas->generarTextura("hud.png");
	this->puntaje = new std::string;
    *this->puntaje = "0";
    this->vidas = new std::string;
    *this->vidas = "00";

    this->nuevoTexto(this->puntaje, Vector(156, 24), TEXTO_COLOR_ROJO, ALINEACION_CENTRO);
    this->nuevoTexto(this->vidas, Vector(864, 24), TEXTO_COLOR_NARANJA, ALINEACION_IZQUIERDA);
}

void HudVista::render(EstadoLogin estadoLogin, std::string username) {
    SDL_Rect hudrect = {(PANTALLA_ANCHO - HUD_SRC_ANCHO) / 2, 0, HUD_SRC_ANCHO, HUD_SRC_ALTO};
	SDL_RenderSetViewport(gRenderer, &hudrect);

	SDL_Rect srcrect = {0, 0, HUD_SRC_ANCHO, HUD_SRC_ALTO};
	SDL_Rect dstrect = {0, 0, HUD_SRC_ANCHO, HUD_SRC_ALTO};
	SDL_RenderCopy(gRenderer, textura, &srcrect, &dstrect);

    for (TextoVista* c : textos) {
        c->render();
    }

	struct TextoVistaParams params = TextoVistaParams(Vector(528, 24), estadoLogin.nroJugador, ALINEACION_CENTRO);
    TextoVista::eRender(username, params);
    params = TextoVistaParams(Vector(792, 24), estadoLogin.nroJugador, ALINEACION_IZQUIERDA);
    TextoVista::eRender(std::string({VIDA_NAVE_IZQ, VIDA_NAVE_DER}), params);

    if (toast != nullptr) {
        toast->render();
    }
}

void HudVista::nuevoTexto(std::string* texto, Vector posicion, int color, int alineacionIzq) {
	struct TextoVistaParams params;
	params.posicion = posicion;
	params.color = color;
	params.alineacion = alineacionIzq;
	textos.emplace_back(new TextoVista(texto, params));
}

void HudVista::setCantidadVidasEnergiaPuntos(int cantidadVidas, int energia, int puntos) {
    *this->vidas = "0" + std::to_string(cantidadVidas);
	*this->puntaje = std::to_string(puntos);
}
