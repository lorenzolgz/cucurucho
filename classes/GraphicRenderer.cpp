//
// Created by rodrigosouto on 20/4/20.
//

#include <iostream>
#include <exception>
#include "GraphicRenderer.h"
#include "Log.h"

SDL_Renderer* GraphicRenderer::instance = nullptr;

SDL_Renderer* GraphicRenderer::getInstance(){
	if (instance == nullptr) {
		l.error("GraphicRenderer no fue creado correctamente");
		throw std::runtime_error("GraphicRenderer not created.");
	}

	return instance;
}

void GraphicRenderer::setInstance(SDL_Renderer *gRenderer) {
	GraphicRenderer::instance = gRenderer;
}

GraphicRenderer::GraphicRenderer(){
	l.info("Creando instancia de GraphicRenderer.");
}
