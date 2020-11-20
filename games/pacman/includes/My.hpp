/*
** EPITECH PROJECT, 2020
** Pacman
** File description:
** My.hpp
*/

#ifndef MY_HPP_
#define MY_HPP_

#include <string>   
#include <array>
#include <vector>
#include <map>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <chrono>
#include <ctime>
#include <thread>
#include <time.h>
#include <cmath>
#include <memory>

#include "IGame.hpp"

#define PACMAN_FULL_CHAR        'O'
#define PACMAN_OPEN_CHAR        'C'
#define PACMAN_MID_CHAR         'G'
#define GHOST_CHAR              '&'
#define GUM_CHAR                '.'
#define SUPERGUM_CHAR           '*'
#define EMPTY_CHAR              ' '
#define WALL_CHAR               '#'
#define FEARED_GHOST_CHAR       '$'

#define PACMAN_FULL_I_COLOR     3   // COLOR_YELLOW
#define PACMAN_FULL_O_COLOR     0   // COLOR_BLACK
#define PACMAN_OPEN_I_COLOR     3   // COLOR_YELLOW
#define PACMAN_OPEN_O_COLOR     0   // COLOR_BLACK
#define PACMAN_MID_I_COLOR      3   // COLOR_YELLOW
#define PACMAN_MID_O_COLOR      0   // COLOR_BLACK
#define GHOST_I_COLOR           1   // COLOR_RED
#define GHOST_O_COLOR           0   // COLOR_BLACK
#define GUM_I_COLOR             7   // COLOR_WHITE
#define GUM_O_COLOR             0   // COLOR_BLACK
#define SUPERGUM_I_COLOR        7   // COLOR_WHITE
#define SUPERGUM_O_COLOR        0   // COLOR_BLACK
#define SPACE_I_COLOR           0   // COLOR_BLACK
#define SPACE_O_COLOR           0   // COLOR_BLACK
#define WALL_I_COLOR            4   // COLOR_BLUE
#define WALL_O_COLOR            4   // COLOR_BLUE
#define FEARED_GHOST_I_COLOR    4   // COLOR_BLUE
#define FEARED_GHOST_O_COLOR    7   // COLOR_WHITE

#define PACMAN_FULL_TEXT_PATH   "./games/pacman/assets/fullPacman.png"
#define PACMAN_OPEN_TEXT_PATH   "./games/pacman/assets/FullOpenPacman.png"
#define PACMAN_MID_TEXT_PATH    "./games/pacman/assets/MidOpenPacman.png"
#define PACMAN_TEXT_PATH        "./games/pacman/assets/fullPacman.png"
#define GHOST_TEXT_PATH         "./games/pacman/assets/ghost.png"
#define GUM_TEXT_PATH           "./games/pacman/assets/gum.png"
#define SUPERGUM_TEXT_PATH      "./games/pacman/assets/supergum.png"
#define SPACE_TEXT_PATH         "./games/pacman/"
#define WALL_TEXT_PATH          "./games/pacman/assets/wall.png"
#define FEARED_GHOST_TEXT_PATH  "./games/pacman/assets/fearGhost.png"

#define MAP_FOLDER_PATH         "./games/pacman/assets/maps/"
#define MAP1                    "map1.conf"
#define MAP2                    "map2.conf"

#define DIR_NONE               -1
#define DIR_UP                  1
#define DIR_DOWN                2
#define DIR_LEFT                4
#define DIR_RIGHT               8
#define DIR_NO_SET              0

#define GAME_SPEED              0.4f

#define reverseDirTer(d) (d == KEY_LEFT) ? KEY_RIGHT : KEY_LEFT;
#define reverseDirBis(d) (d == KEY_DOWN) ? KEY_UP : reverseDirTer(d)
#define reverseDir(d) (d == KEY_UP) ? KEY_DOWN : reverseDirBis(d)

#define backDirTer(d) (d == KEY_LEFT) ? DIR_RIGHT : DIR_LEFT
#define backDirBis(d) (d == KEY_DOWN) ? DIR_UP : backDirTer(d)
#define backDir(d) (d == KEY_UP) ? DIR_DOWN : backDirBis(d)

#define getDirTer(d) (d == DIR_LEFT) ? KEY_LEFT : KEY_RIGHT
#define getDirBis(d) (d == DIR_DOWN) ? KEY_DOWN : getDirTer(d)
#define getDir(d) (d == DIR_UP) ? KEY_UP : getDirBis(d)

#define getPossibilityTer(d) (d == KEY_LEFT) ? DIR_LEFT : DIR_RIGHT
#define getPossibilityBis(d) (d == KEY_DOWN) ? DIR_DOWN : getPossibilityTer(d)
#define getPossibility(d) (d == KEY_UP) ? DIR_UP : getPossibilityBis(d)

#define STD_CLOCK std::chrono::_V2::high_resolution_clock::time_point
#define getTimeElapsed(t) std::chrono::duration<double, std::milli>(std::chrono::high_resolution_clock::now() - t).count()

namespace pcm
{
    class Position
    {
        public:
            size_t  x;
            size_t  y;
            size_t  idx;
    };
    typedef Position position_t;

}

#endif /* !MY_HPP_ */
