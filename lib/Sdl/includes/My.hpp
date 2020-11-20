/*
** EPITECH PROJECT, 2020
** SDL
** File description:
** My.hpp
*/

#ifndef MY_HPP_
#define MY_HPP_

#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <array>
#include <chrono>
#include <cmath>
#include <memory>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "IGraphics.hpp"
#include "Info.hpp"
#include "Score.hpp"


//Screen dimension constants
#define SCREEN_WIDTH                1280
#define SCREEN_HEIGHT               960
#define DEFAULT_SPRITE_SIZE         32
#define DEFAULT_MAX_SPRITE_W        (SCREEN_WIDTH - 2 * DEFAULT_SPRITE_SIZE) / DEFAULT_SPRITE_SIZE
#define DEFAULT_MAX_SPRITE_H        (SCREEN_HEIGHT - 2 * DEFAULT_SPRITE_SIZE) / DEFAULT_SPRITE_SIZE
#define DEFAULT_SCREEN_CENTER_W     SCREEN_WIDTH / 2
#define DEFAULT_SCREEN_CENTER_H     SCREEN_HEIGHT / 2
#define DEFAULT_BEGIN_W             DEFAULT_SPRITE_SIZE
#define DEFAULT_BEGIN_H             DEFAULT_SPRITE_SIZE
#define DEFAULT_SCORE_W             DEFAULT_SPRITE_SIZE
#define DEFAULT_LIFE_W              DEFAULT_SCREEN_CENTER_W + DEFAULT_SPRITE_SIZE
#define DEFAULT_TEXT_H              24
#define DEFAULT_POLICE_SIZE         24
#define getNewSpriteSize(s, n)      (((s / n) >> 3) << 3)
#define DEFAULT_POLICE_MENU_SIZE    36
#define MENU_BACKGROUND_PATH        "lib/Sdl/assets/menu_bg.png"
#define MENU_ARROW_PATH             "lib/Sdl/assets/IconSelectionMenu.png"
#define MENU_FONT_PATH              "lib/Sdl/assets/MenuFont.ttf"

#define GAME_IDX                    0
#define LIB_IDX                     1
#define SCORE_IDX                   2
#define NAME_IDX                    3

#endif /* !MY_HPP_ */   