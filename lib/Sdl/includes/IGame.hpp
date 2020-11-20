/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** IGames
*/

#ifndef IGAMES_HPP_
#define IGAMES_HPP_

#include <vector>
#include <string>
#include "InitTab.hpp"
#include "Core.hpp"

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

class IGames {
    public:
        virtual ~IGames() = default;
        virtual const std::vector<std::vector<char>> &simulate(Input key) = 0;
        virtual const std::string &getScore() const = 0;
        virtual const std::string &getLife() const = 0;
        virtual const std::vector<InitTab> &getInit() const = 0;
        virtual const float &getSpeed(void) const = 0;

    protected:
    private:
};

#endif /* !IGAMES_HPP_ */
