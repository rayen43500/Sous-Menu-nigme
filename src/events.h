/*
 * events.h - Gestion des événements souris/clavier
 */
#ifndef EVENTS_H
#define EVENTS_H

#include "defs.h"

/* Gère les événements dans l'écran Menu */
void handleMenuEvents(SDL_Event *e, Button *quizBtn, Button *puzzleBtn,
                      Screen *screen, Assets *assets, bool *quizMusicStarted);

/* Gère les événements dans l'écran Quiz */
void handleQuizEvents(SDL_Event *e, Button *answers, size_t answerCount,
                      Assets *assets);

#endif /* EVENTS_H */
