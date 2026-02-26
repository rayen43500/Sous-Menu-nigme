/*
 * utils.c - Implémentation des fonctions utilitaires
 */
#include "utils.h"

/* Buffer global pour le chemin de base (dossier de l'exécutable) */
static char g_basePath[512] = {0};

const char *assetPath(const char *relative) {
    static char full[1024];
    if (!g_basePath[0]) {
        char *bp = SDL_GetBasePath();
        if (bp) {
            SDL_strlcpy(g_basePath, bp, sizeof(g_basePath));
            SDL_free(bp);
        }
    }
    SDL_snprintf(full, sizeof(full), "%s%s", g_basePath, relative);
    return full;
}

bool pointInRect(int x, int y, const SDL_Rect *r) {
    return x >= r->x && x < r->x + r->w && y >= r->y && y < r->y + r->h;
}

SDL_Texture *loadTexture(SDL_Renderer *renderer, const char *path) {
    SDL_Surface *surface = IMG_Load(path);
    if (!surface) {
        SDL_Log("Could not load image %s: %s", path, IMG_GetError());
        return NULL;
    }
    SDL_Texture *tex = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return tex;
}

SDL_Texture *renderText(SDL_Renderer *renderer, TTF_Font *font, const char *text, SDL_Color color) {
    SDL_Surface *surface = TTF_RenderUTF8_Blended(font, text, color);
    if (!surface) {
        SDL_Log("TTF render error: %s", TTF_GetError());
        return NULL;
    }
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}
