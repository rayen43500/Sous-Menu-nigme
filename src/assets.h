/*
 * assets.h - Chargement et libération des ressources
 */
#ifndef ASSETS_H
#define ASSETS_H

#include "defs.h"

/* Initialise SDL, TTF, Mixer, Image et crée la fenêtre + renderer */
bool initSDL(SDL_Window **window, SDL_Renderer **renderer);

/* Charge toutes les ressources (images, sons, polices) */
bool loadAssets(SDL_Renderer *renderer, Assets *assets);

/* Libère toutes les ressources */
void unloadAssets(Assets *assets);

#endif /* ASSETS_H */
