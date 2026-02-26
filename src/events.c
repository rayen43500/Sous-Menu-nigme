/*
 * events.c - Implémentation de la gestion des événements
 */
#include "events.h"
#include "button.h"
#include "utils.h"

void handleMenuEvents(SDL_Event *e, Button *quizBtn, Button *puzzleBtn,
                      Screen *screen, Assets *assets, bool *quizMusicStarted) {
    if (e->type == SDL_MOUSEMOTION) {
        int mx = e->motion.x;
        int my = e->motion.y;
        playHoverIfNeeded(quizBtn,   pointInRect(mx, my, &quizBtn->bounds),   assets->hoverSfx);
        playHoverIfNeeded(puzzleBtn, pointInRect(mx, my, &puzzleBtn->bounds), assets->hoverSfx);
    }
    else if (e->type == SDL_MOUSEBUTTONDOWN && e->button.button == SDL_BUTTON_LEFT) {
        int mx = e->button.x;
        int my = e->button.y;

        /* Clic QUIZ → changer d'écran (pas de musique) */
        if (pointInRect(mx, my, &quizBtn->bounds)) {
            *screen = SCREEN_QUIZ;
        }
        /* Clic PUZZLE → lancer la musique de suspense */
        else if (pointInRect(mx, my, &puzzleBtn->bounds)) {
            SDL_Log("PUZZLE clicked");
            if (!*quizMusicStarted && assets->quizMusic) {
                SDL_Log("Lancement musique puzzle...");
                Mix_PlayMusic(assets->quizMusic, -1);
                *quizMusicStarted = true;
            }
        }
    }
}

void handleQuizEvents(SDL_Event *e, Button *answers, size_t answerCount,
                      Assets *assets) {
    if (e->type == SDL_MOUSEMOTION) {
        int mx = e->motion.x;
        int my = e->motion.y;
        for (size_t i = 0; i < answerCount; ++i) {
            playHoverIfNeeded(&answers[i], pointInRect(mx, my, &answers[i].bounds), assets->hoverSfx);
        }
    }
    else if (e->type == SDL_MOUSEBUTTONDOWN && e->button.button == SDL_BUTTON_LEFT) {
        int mx = e->button.x;
        int my = e->button.y;
        for (size_t i = 0; i < answerCount; ++i) {
            if (pointInRect(mx, my, &answers[i].bounds)) {
                bool isCorrect = (answers[i].label && answers[i].label[0] == 'A');
                if (isCorrect) {
                    if (assets->hoverSfx) {
                        Mix_PlayChannel(-1, assets->hoverSfx, 0);
                    }
                    SDL_Log("Réponse A : CORRECT");
                } else {
                    SDL_Log("Réponse %s : incorrect", answers[i].label);
                }
            }
        }
    }
}
