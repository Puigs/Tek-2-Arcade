/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Info
*/

#ifndef INFO_HPP_
#define INFO_HPP_

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <dirent.h>
#include "Score.hpp"

class Info {
    public:
        Info();
        ~Info();
        const std::vector<std::string> &    getGraphNames   (void)      const;
        const std::vector<std::string> &    getGameNames    (void)      const;
        std::size_t                         getGraphIdx     (void)      const;
        std::size_t                         getGameIdx      (void)      const;
        std::size_t                         getSide         (void)      const;
        const std::vector<Score> &          getScoring      (void)      const;
        void                                setGraphIdx     (const std::size_t &graphIdx);
        void                                setGameIdx      (const std::size_t &gameIdx);
        void                                setSide         (const std::size_t &side);
        void                                setScoring      (const std::string &file);
        void                                addScore        (const Score &score);

    private:    
        std::vector<std::string>            _graphNames;
        std::vector<std::string>            _gameNames;
        std::size_t                         _graph_idx;
        std::size_t                         _game_idx;
        std::size_t                         _side;
        std::vector<Score>                  _scoring;

};

#endif /* !INFO_HPP_ */
