//
// Created by rodrigosouto on 20/4/20.
//

#ifndef CUCURUCHO_GRAPHICRENDERER_H
#define CUCURUCHO_GRAPHICRENDERER_H


#include <SDL_render.h>

class GraphicRenderer {
public:
	static SDL_Renderer *getInstance();
	static void setInstance(SDL_Renderer *gRenderer);

private:
	GraphicRenderer();
	static SDL_Renderer *instance;
};


#endif //CUCURUCHO_GRAPHICRENDERER_H
