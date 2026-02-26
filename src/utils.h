/*
 * utils.h - Fonctions utilitaires (collision, chargement texture/texte, chemins)
 */
#ifndef UTILS_H
#define UTILS_H

#include "defs.h"

/* Vérifie si un point est dans un rectangle */
bool pointInRect(int x, int y, const SDL_Rect *r);

/* Charge une image (JPG, PNG, BMP) en texture SDL */
SDL_Texture *loadTexture(SDL_Renderer *renderer, const char *path);

/* Crée une texture de texte rendu */
SDL_Texture *renderText(SDL_Renderer *renderer, TTF_Font *font, const char *text, SDL_Color color);

/* Construit un chemin absolu depuis le dossier de l'exécutable */
const char *assetPath(const char *relative);

#endif /* UTILS_H */
