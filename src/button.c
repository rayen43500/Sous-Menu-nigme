/*
 * button.c - Implémentation du dessin et de l'interaction des boutons
 */
#include "button.h"
#include "utils.h"

void drawButton(SDL_Renderer *renderer, TTF_Font *font, const Button *btn,
                SDL_Color base, SDL_Color hover, SDL_Color textColor) {
    /* Choisir la couleur selon l'état (survolé ou non) */
    SDL_Color color = btn->hovered ? hover : base;

    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);
    SDL_RenderFillRect(renderer, &btn->bounds);

    SDL_SetRenderDrawColor(renderer, 20, 20, 20, 255);
    SDL_RenderDrawRect(renderer, &btn->bounds);

    /* Texte centré dans le bouton */
    if (font && btn->label) {
        SDL_Texture *labelTex = renderText(renderer, font, btn->label, textColor);
        if (labelTex) {
            int w = 0, h = 0;
            SDL_QueryTexture(labelTex, NULL, NULL, &w, &h);
            SDL_Rect dst = {
                btn->bounds.x + (btn->bounds.w - w) / 2,
                btn->bounds.y + (btn->bounds.h - h) / 2,
                w, h
            };
            SDL_RenderCopy(renderer, labelTex, NULL, &dst);
            SDL_DestroyTexture(labelTex);
        }
    }
}

void playHoverIfNeeded(Button *btn, bool nowHovered, Mix_Chunk *hoverSfx) {
    if (nowHovered && !btn->hovered && hoverSfx) {
        Mix_PlayChannel(-1, hoverSfx, 0);
    }
    btn->hovered = nowHovered;
}
