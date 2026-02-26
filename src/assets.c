/*
 * assets.c - Chargement et libération des ressources + init SDL
 */
#include "assets.h"
#include "utils.h"

bool initSDL(SDL_Window **window, SDL_Renderer **renderer) {
    bool ttfInit = false;
    bool mixOpen = false;
    bool mixInit = false;
    bool imgInit = false;

    *window = NULL;
    *renderer = NULL;

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        SDL_Log("SDL init error: %s", SDL_GetError());
        return false;
    }

    if (TTF_Init() < 0) {
        SDL_Log("TTF init error: %s", TTF_GetError());
        goto fail;
    }
    ttfInit = true;

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        SDL_Log("SDL_mixer error: %s", Mix_GetError());
        goto fail;
    }
    mixOpen = true;

    int mixFlags = Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG);
    if (!(mixFlags & MIX_INIT_MP3)) {
        SDL_Log("Warning: MP3 support not available: %s", Mix_GetError());
    } else {
        mixInit = true;
    }

    int imgFlags = IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
    if (!(imgFlags & IMG_INIT_JPG)) {
        SDL_Log("Warning: JPG support not available: %s", IMG_GetError());
    } else {
        imgInit = true;
    }

    *window = SDL_CreateWindow(
        "Sous Menu Enigme",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        SDL_WINDOW_SHOWN
    );
    if (!*window) {
        SDL_Log("Window error: %s", SDL_GetError());
        goto fail;
    }

    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!*renderer) {
        SDL_Log("Renderer error: %s", SDL_GetError());
        goto fail;
    }

    SDL_SetRenderDrawBlendMode(*renderer, SDL_BLENDMODE_BLEND);
    return true;

fail:
    if (*renderer) {
        SDL_DestroyRenderer(*renderer);
        *renderer = NULL;
    }
    if (*window) {
        SDL_DestroyWindow(*window);
        *window = NULL;
    }
    if (imgInit) IMG_Quit();
    if (mixInit) Mix_Quit();
    if (mixOpen) Mix_CloseAudio();
    if (ttfInit) TTF_Quit();
    SDL_Quit();
    return false;
}

bool loadAssets(SDL_Renderer *renderer, Assets *assets) {
    *assets = (Assets){0};

    assets->background4 = loadTexture(renderer, assetPath("src/assets/background.jpg"));
    if (!assets->background4) {
        SDL_Log("Background missing ou invalide: le fond vert sera utilisé.");
    }

    assets->hoverSfx = Mix_LoadWAV(assetPath("src/assets/hover.wav"));
    if (!assets->hoverSfx) {
        SDL_Log("Hover sound missing: ajoutez hover.wav dans assets/");
    }

    assets->quizMusic = Mix_LoadMUS(assetPath("src/assets/sonican-quiz-background.mp3"));
    if (!assets->quizMusic) {
        SDL_Log("sonican-quiz-background.mp3 non trouvé, essai quiz_music.ogg...");
        assets->quizMusic = Mix_LoadMUS(assetPath("src/assets/quiz_music.ogg"));
    }
    if (!assets->quizMusic) {
        assets->quizMusic = Mix_LoadMUS(assetPath("src/assets/quiz_music.mp3"));
    }
    if (!assets->quizMusic) {
        assets->quizMusic = Mix_LoadMUS(assetPath("src/assets/quiz_music.wav"));
    }
    if (!assets->quizMusic) {
        SDL_Log("Quiz music missing: ajoutez sonican-quiz-background.mp3 dans assets/");
    }

    assets->font = TTF_OpenFont(assetPath("src/assets/Roboto-Regular.ttf"), 28);
    if (!assets->font) {
        SDL_Log("Font assets manquante, essai Arial Windows...");
        assets->font = TTF_OpenFont("C:/Windows/Fonts/arial.ttf", 28);
    }
    if (!assets->font) {
        SDL_Log("ERREUR: Aucune police trouvée! Ajoutez Roboto-Regular.ttf dans assets/");
        return false;
    }

    return true;
}

void unloadAssets(Assets *assets) {
    if (assets->background4) SDL_DestroyTexture(assets->background4);
    if (assets->hoverSfx) Mix_FreeChunk(assets->hoverSfx);
    if (assets->quizMusic) Mix_FreeMusic(assets->quizMusic);
    if (assets->font) TTF_CloseFont(assets->font);
}
