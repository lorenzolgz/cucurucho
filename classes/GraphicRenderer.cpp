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
		l.error("GraphicRenderer not created");
		throw std::runtime_error("GraphicRenderer not created.");
	}

	return instance;
}

void GraphicRenderer::setInstance(SDL_Renderer *gRenderer) {
	GraphicRenderer::instance = gRenderer;
}

GraphicRenderer::GraphicRenderer(){
	l.error("Creating GraphicRenderer instance.");
}
