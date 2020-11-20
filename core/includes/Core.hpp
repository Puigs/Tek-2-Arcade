/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Core
*/

#ifndef CORE_HPP_
#define CORE_HPP_

#include "InitTab.hpp"
#include "IGame.hpp"
#include "IGraphics.hpp"
#include "DlLoader.hpp"
#include "Info.hpp"
#include "Exception.hpp"
#include <string>
#include <unistd.h>
#include <memory>

#ifndef __NCURSES_H
#undef KEY_UP
#undef KEY_DOWN
#undef KEY_LEFT
#undef KEY_RIGHT
#endif

#ifndef _INPUT_
#define _INPUT_

enum Input {
    NONE = -1,
    KEY_UP,
    KEY_DOWN,
    KEY_LEFT,
    KEY_RIGHT,
    EXIT,
    PREV_GAME,
    NEXT_GAME,
    ENTER,
    PREV_GRAPH,
    NEXT_GRAPH
};

#endif

class Core {
    public:
        Core(const std::string &path);
        ~Core();
        void MainLoop();
    protected:
    private:
        void parseScore();
        std::string _playerName;
        int gameInputs(Input inp);
        int infoLoading(Input inp);
        void gameLoop();
        Info _info;
        std::shared_ptr<IGraphics> _Graphic;
        std::shared_ptr<IGames> _Game;
};

#endif /* !CORE_HPP_ */
