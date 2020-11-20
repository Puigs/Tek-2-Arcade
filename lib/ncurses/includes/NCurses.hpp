/*
** EPITECH PROJECT, 2020
** NCurses
** File description:
** NCurses
*/

#ifndef NCURSES_HPP_
#define NCURSES_HPP_

#include "IGraphics.hpp"
#include "Info.hpp"
#include "InitTab.hpp"
#include "Score.hpp"
#include <iostream>
#include <memory>
#include <ncurses.h>
#include <malloc.h>
#include <map>

class NCurses : public IGraphics {
    public:
        NCurses();
        ~NCurses();
        void displayGame(const std::vector<std::vector<char>> &arr);
        void displayMenu(const Info &info);
        void setPreview(std::vector<std::vector<char>> &);
        void init(const std::vector<InitTab> &arr);
        virtual std::string getName();
        void setScore(const std::string &score);
        void setLife(const std::string &life);
        Input getInput();
    protected:
    private:
        void resizeOrNewGame();
        void resizeOrNewMenu();
        void printScore();
        void printLife();
        void printGame(const std::vector<std::vector<char>> &arr);
        void printGames(const Info &info);
        void printLib(const Info &info);
        void printScores(const Info &info);
        void printName(const Info &info);
        WINDOW *_scoreWin;
        WINDOW *_lifeWin;
        WINDOW *_gameWin;
        WINDOW *_gamesWin;
        WINDOW *_libWin;
        WINDOW *_scoresWin;
        WINDOW *_nameWin;
        int _winX;
        int _winY;
        int _x;
        int _y;
        size_t _pos;
        std::string _score;
        std::string _life;
        std::vector<InitTab> _initTab;
        std::map<char, int> _color;
        std::string _name;
};

#endif /* !NCURSES_HPP_ */
