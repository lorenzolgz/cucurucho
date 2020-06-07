#include <iostream>
#include "GraphicRenderer.h"
#include "../../commons/utils/Log.h"

SDL_Renderer* GraphicRenderer::instance = nullptr;

SDL_Renderer* GraphicRenderer::getInstance(){
	if (instance == nullptr) {
		l->info("GraphicRenderer no fue creado correctamente");
		throw std::runtime_error("GraphicRenderer not created.");
	}

	return instance;
}

void GraphicRenderer::setInstance(SDL_Renderer *gRenderer) {
	GraphicRenderer::instance = gRenderer;
}

GraphicRenderer::GraphicRenderer(){
	l->info("Creando instancia de GraphicRenderer.");
}
