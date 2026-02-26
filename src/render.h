/*
 * render.h - Fonctions de rendu (arrière-plan, menu, quiz)
 */
#ifndef RENDER_H
#define RENDER_H

#include "defs.h"

/* Affiche l'arrière-plan (image ou couleur verte de secours) */
void renderBackground(SDL_Renderer *renderer, SDL_Texture *background);

/* Affiche l'écran du menu (boutons Quiz / Puzzle) */
void renderMenu(SDL_Renderer *renderer, TTF_Font *font, Assets *assets,
                Button *quizBtn, Button *puzzleBtn);

/* Affiche l'écran du quiz (titre, question, réponses A/B/C) */
void renderQuiz(SDL_Renderer *renderer, TTF_Font *font, Assets *assets,
                Button *answers, size_t answerCount);

#endif /* RENDER_H */
