//
// Created by hyong on 1/5/21.
//

#ifndef DEAMON_TIP_H
#define DEAMON_TIP_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

void tip();
void tip(std::string message);
SDL_Texture * renderText(const std::string &message, const std::string &fontFile,
                         SDL_Color color, int fontSize, SDL_Renderer *renderer);
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, SDL_Rect dst, SDL_Rect *clip = nullptr);
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, SDL_Rect *clip = nullptr);
#endif //DEAMON_TIP_H
