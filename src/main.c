/*
 * Sous-menu Énigme - Quiz/Puzzle
 * Utilise les modules utils/render/events/button/assets
 */
#include "defs.h"
#include "assets.h"
#include "render.h"
#include "events.h"
#include "button.h"

int main(int argc, char *argv[]) {
    (void)argc;
    (void)argv;

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    Assets assets = {0};

    if (!initSDL(&window, &renderer)) {
        return 1;
    }

    if (!loadAssets(renderer, &assets)) {
        SDL_Log("Continuing with placeholders where assets are missing.");
    }

    const int menuBtnW = 200;
    const int menuBtnH = 60;
    const int menuGap = 40;
    const int menuTotalW = 2 * menuBtnW + menuGap;
    const int menuStartX = (WINDOW_WIDTH - menuTotalW) / 2;
    const int menuY = 300;

    Button quizBtn = {
        { menuStartX, menuY, menuBtnW, menuBtnH },
        "QUIZ",
        false
    };
    Button puzzleBtn = {
        { menuStartX + menuBtnW + menuGap, menuY, menuBtnW, menuBtnH },
        "PUZZLE",
        false
    };

    Button answers[3];
    const int answerWidth = 140;
    const int answerHeight = 60;
    const int gap = 30;
    const int totalWidth = 3 * answerWidth + 2 * gap;
    const int startX = (WINDOW_WIDTH - totalWidth) / 2;
    const int y = 320;
    const char *labels[] = {"A", "B", "C"};

    for (int i = 0; i < 3; ++i) {
        answers[i].bounds.x = startX + i * (answerWidth + gap);
        answers[i].bounds.y = y;
        answers[i].bounds.w = answerWidth;
        answers[i].bounds.h = answerHeight;
        answers[i].label = labels[i];
        answers[i].hovered = false;
    }

    bool running = true;
    bool quizMusicStarted = false;
    Screen screen = SCREEN_MENU;

    while (running && screen != SCREEN_QUIT) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                running = false;
                break;
            }
            if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) {
                running = false;
                break;
            }

            switch (screen) {
                case SCREEN_MENU:
                    handleMenuEvents(&e, &quizBtn, &puzzleBtn, &screen, &assets, &quizMusicStarted);
                    break;
                case SCREEN_QUIZ:
                    handleQuizEvents(&e, answers, 3, &assets);
                    break;
                default:
                    break;
            }
        }

        SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
        SDL_RenderClear(renderer);

        if (screen == SCREEN_MENU) {
            renderMenu(renderer, assets.font, &assets, &quizBtn, &puzzleBtn);
        } else if (screen == SCREEN_QUIZ) {
            renderQuiz(renderer, assets.font, &assets, answers, 3);
        }

        SDL_RenderPresent(renderer);
    }

    Mix_HaltMusic();
    unloadAssets(&assets);

    if (renderer) SDL_DestroyRenderer(renderer);
    if (window) SDL_DestroyWindow(window);

    Mix_CloseAudio();
    Mix_Quit();
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();

    return 0;
}
