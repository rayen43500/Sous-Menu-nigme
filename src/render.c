/*
 * render.c - Implémentation du rendu des écrans
 */
#include "render.h"
#include "button.h"
#include "utils.h"

void renderBackground(SDL_Renderer *renderer, SDL_Texture *background) {
    if (background) {
        SDL_RenderCopy(renderer, background, NULL, NULL);
    } else {
        /* Fond vert de secours si aucune image chargée */
        SDL_SetRenderDrawColor(renderer, 34, 139, 34, 255);
        SDL_RenderClear(renderer);
    }
}

void renderMenu(SDL_Renderer *renderer, TTF_Font *font, Assets *assets,
                Button *quizBtn, Button *puzzleBtn) {
    renderBackground(renderer, assets->background4);

    SDL_Color btnBase  = {180, 200, 230, 255};
    SDL_Color btnHover = {220, 235, 255, 255};
    SDL_Color textCol  = { 15,  20,  30, 255};

    drawButton(renderer, font, quizBtn,   btnBase, btnHover, textCol);
    drawButton(renderer, font, puzzleBtn, btnBase, btnHover, textCol);
}

void renderQuiz(SDL_Renderer *renderer, TTF_Font *font, Assets *assets,
                Button *answers, size_t answerCount) {
    renderBackground(renderer, assets->background4);

    SDL_Color white   = {240, 240, 240, 255};
    SDL_Color accent  = {180, 210, 255, 255};
    SDL_Color textCol = { 15,  20,  30, 255};

    /* Titre "QUIZ" centré en haut */
    SDL_Texture *titleTex = renderText(renderer, font, "QUIZ", white);
    if (titleTex) {
        int w = 0, h = 0;
        SDL_QueryTexture(titleTex, NULL, NULL, &w, &h);
        SDL_Rect dst = { (WINDOW_WIDTH - w) / 2, 30, w, h };
        SDL_RenderCopy(renderer, titleTex, NULL, &dst);
        SDL_DestroyTexture(titleTex);
    }

    /* Bande de la question */
    SDL_Rect questionBox = {100, 120, WINDOW_WIDTH - 200, 120};
    SDL_SetRenderDrawColor(renderer, 50, 60, 80, 255);
    SDL_RenderFillRect(renderer, &questionBox);
    SDL_SetRenderDrawColor(renderer, 220, 230, 255, 255);
    SDL_RenderDrawRect(renderer, &questionBox);

    SDL_Texture *questionTex = renderText(renderer, font, "Quelle porte s'ouvre ?", accent);
    if (questionTex) {
        int w = 0, h = 0;
        SDL_QueryTexture(questionTex, NULL, NULL, &w, &h);
        SDL_Rect dst = {
            questionBox.x + (questionBox.w - w) / 2,
            questionBox.y + (questionBox.h - h) / 2,
            w, h
        };
        SDL_RenderCopy(renderer, questionTex, NULL, &dst);
        SDL_DestroyTexture(questionTex);
    }

    /* Boutons de réponse A, B, C */
    SDL_Color btnBase  = {190, 205, 230, 255};
    SDL_Color btnHover = {225, 240, 255, 255};
    for (size_t i = 0; i < answerCount; ++i) {
        drawButton(renderer, font, &answers[i], btnBase, btnHover, textCol);
    }

    /* Textes descriptifs sous chaque réponse */
    const char *optionTexts[] = {"Option A", "Option B", "Option C"};
    for (size_t i = 0; i < answerCount && i < 3; ++i) {
        SDL_Texture *optTex = renderText(renderer, font, optionTexts[i], white);
        if (optTex) {
            int w = 0, h = 0;
            SDL_QueryTexture(optTex, NULL, NULL, &w, &h);
            SDL_Rect dst = {
                answers[i].bounds.x + (answers[i].bounds.w - w) / 2,
                answers[i].bounds.y + answers[i].bounds.h + 10,
                w, h
            };
            SDL_RenderCopy(renderer, optTex, NULL, &dst);
            SDL_DestroyTexture(optTex);
        }
    }
}
