/*
 * defs.h - Définitions communes (types, constantes, structures)
 * Partagé par tous les modules du projet.
 */
#ifndef DEFS_H
#define DEFS_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <SDL_image.h>
#include <stdbool.h>
#include <stdio.h>

/* Dimensions de la fenêtre */
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

/* Énumération des écrans du jeu */
typedef enum Screen {
    SCREEN_MENU,
    SCREEN_QUIZ,
    SCREEN_QUIT
} Screen;

/* Structure d'un bouton cliquable */
typedef struct Button {
    SDL_Rect bounds;
    const char *label;
    bool hovered;
} Button;

/* Structure contenant toutes les ressources */
typedef struct Assets {
    SDL_Texture *background4;
    Mix_Chunk *hoverSfx;
    Mix_Music *quizMusic;
    TTF_Font *font;
} Assets;

#endif /* DEFS_H */
