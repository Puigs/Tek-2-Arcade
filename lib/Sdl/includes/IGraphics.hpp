/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** IGraphics
*/

#ifndef IGRAPHICS_HPP_
#define IGRAPHICS_HPP_

#include <vector>
#include <string>
#include "InitTab.hpp"
#include "Info.hpp"



#ifndef _INPUT_
#define _INPUT_

enum Input {
    NONE = -1,
    UP,
    DOWN,
    LEFT,
    RIGHT,
    EXIT,
    PREV_GAME,
    NEXT_GAME,
    ENTER,
    PREV_GRAPH,
    NEXT_GRAPH
};

#endif

class IGraphics {
    public:
        virtual ~IGraphics() = default;
        virtual void displayGame(const std::vector<std::vector<char>> &arr) = 0;
        virtual void displayMenu(const Info &info) = 0;
        void setPreview(std::vector<std::vector<char>> &);
        virtual std::string getName() = 0;
        virtual void init(const std::vector<InitTab> &arr) = 0;
        virtual void setScore(const std::string &score) = 0;
        virtual void setLife(const std::string &life) = 0;
        virtual Input getInput() = 0;

    protected:
    private:
};

#endif /* !IGRAPHICS_HPP_ */
