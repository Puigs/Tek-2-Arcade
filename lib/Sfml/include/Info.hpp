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
#include "Score.hpp"

class Info {
    public:
        Info();
        ~Info();
        const std::vector<std::string> &getGraphNames() const;
        const std::vector<std::string> &getGameNames() const;
        std::size_t getGraphIdx() const;
        std::size_t getGameIdx() const;
        std::size_t getSide() const;
        const std::vector<Score> &getScoring() const;
        void setGraphIdx(const std::size_t &graphIdx);
        void setGameIdx(const std::size_t &gameIdx);
        void setSide(const std::size_t &side);
        void setScoring(const std::string &file);
        void addScore(const Score &score);
    
    protected:
    private:
        std::vector<std::string> _graphNames;
        std::vector<std::string> _gameNames;
        std::size_t _graph_idx;
        std::size_t _game_idx;
        std::size_t _side;
        std::vector<Score> _scoring;

};

#endif /* !INFO_HPP_ */
