/*
 * button.h - Dessin et interaction des boutons
 */
#ifndef BUTTON_H
#define BUTTON_H

#include "defs.h"

/* Dessine un bouton (couleur change au survol) */
void drawButton(SDL_Renderer *renderer, TTF_Font *font, const Button *btn,
                SDL_Color base, SDL_Color hover, SDL_Color textColor);

/* Joue un son bref si le bouton vient d'être survolé */
void playHoverIfNeeded(Button *btn, bool nowHovered, Mix_Chunk *hoverSfx);

#endif /* BUTTON_H */
