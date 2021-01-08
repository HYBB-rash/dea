//
// Created by hyong on 1/5/21.
//

#include "../tip.h"
#include "../../../include/catch_error.h"
#include "../../../include/res_path.h"
#include "../../../include/cleanup.h"
#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>

const int SCREEN_WIDTH = 2280;
const int SCREEN_HEIGHT = 120;

SDL_Texture * renderText(const std::string &message, const std::string &fontFile,
                         SDL_Color color, int fontSize, SDL_Renderer *renderer) {
    TTF_Font *font = TTF_OpenFont(fontFile.c_str(), fontSize);
    if (font == nullptr) {
        logSDLError(std::cout, "TTF_RenderText");
        return nullptr;
    }

    SDL_Surface *surf = TTF_RenderText_Blended(font, message.c_str(), color);
    if (surf == nullptr) {
        TTF_CloseFont(font);
        logSDLError(std::cout, "TTF_RenderText");
        return nullptr;
    }
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surf);
    if (texture == nullptr) {
        logSDLError(std::cout, "CreateTexture");
    }

    SDL_FreeSurface(surf);
    TTF_CloseFont(font);
    return texture;
}

void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, SDL_Rect dst, SDL_Rect *clip) {
    SDL_RenderCopy(ren, tex, clip, &dst);
}

void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, SDL_Rect *clip) {
    SDL_Rect dst;
    dst.x = x;
    dst.y = y;
    if (clip != nullptr) {
        dst.w = clip->w;
        dst.h = clip->h;
    } else {
        SDL_QueryTexture(tex, nullptr, nullptr, &dst.w, &dst.h);
    }
    renderTexture(tex, ren, dst, clip);
}

void tip(){
    tip("You have been using it continuously for more than 15 minutes. Please have a rest");
}

void tip(std::string message) {
    //Start up SDL and make sure it went ok
    if (SDL_Init(SDL_INIT_VIDEO) != 0){
        logSDLError(std::cout, "SDL_Init");
        return;
    }
    //Also need to init SDL_ttf
    if (TTF_Init() != 0){
        logSDLError(std::cout, "TTF_Init");
        SDL_Quit();
        return;
    }

    //Setup our window and renderer
    SDL_Window *win = SDL_CreateWindow("tip", SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (win == nullptr){
        logSDLError(std::cout, "CreateWindow");
        TTF_Quit();
        SDL_Quit();
        return;
    }
    SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (ren == nullptr){
        logSDLError(std::cout, "CreateRenderer");
        cleanup(win);
        TTF_Quit();
        SDL_Quit();
        return;
    }

    const std::string resPath = getResourcePath("Deamon");
    SDL_Color color = {255, 255, 255, 255};
    SDL_Texture *image = renderText(
            message.c_str(),
            resPath + "sample.ttf", color, 64, ren);
    if (image == nullptr) {
        cleanup(ren, win);
        TTF_Quit();
        SDL_Quit();
        return;
    }

    int iW, iH;
    SDL_QueryTexture(image, nullptr, nullptr, &iW, &iH);
    int x = SCREEN_WIDTH / 2 - iW / 2;
    int y = SCREEN_HEIGHT / 2 - iH / 2;
    SDL_Delay(500);

    SDL_RenderClear(ren);
    renderTexture(image, ren, x, y);
    SDL_RenderPresent(ren);
    SDL_Delay(2000);

    cleanup(image, ren, win);
    TTF_Quit();
    SDL_Quit();
    return;
}