/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Info
*/

#include "../includes/Info.hpp"

Info::Info()
{
    DIR *dir;
    struct dirent *entry;
    std::string temp;
    _graph_idx = 0;
    _game_idx = 0;
    _side = 0;

    if ((dir = opendir("./lib/")) != NULL) {
        while ((entry = readdir(dir)) != NULL) {
            temp = entry->d_name;
            if (temp.find(".so") != std::string::npos) {
                temp.erase(0, temp.rfind("_") + 1);
                temp.erase(temp.find("."), std::string::npos);
                _graphNames.push_back(temp);
            }
        }
        closedir(dir);
    } else {

    }
    if ((dir = opendir("./games/")) != NULL) {
        while ((entry = readdir(dir)) != NULL) {
            temp = entry->d_name;
            if (temp.find(".so") != std::string::npos) {
                temp.erase(0, temp.rfind("_") + 1);
                temp.erase(temp.find("."), std::string::npos);
                _gameNames.push_back(temp);
            }
        }
        closedir(dir);
    } else {

    }
}

Info::~Info()
{
}

struct less_than_score
{
    inline bool operator() (const Score &score1, const Score &score2)
    {
        return (std::stoi(score1.getScore()) > std::stoi(score2.getScore()));
    }
};

void Info::addScore(const Score &score)
{
    this->_scoring.push_back(score);

    std::sort(this->_scoring.begin(), this->_scoring.end(), less_than_score());
}

const std::vector<Score> &Info::getScoring() const
{
    return this->_scoring;
}

void Info::setScoring(const std::string &file)
{
    (void)file;
}

void Info::setGraphIdx(const std::size_t &graphIdx)
{
    this->_graph_idx = graphIdx;
}

void Info::setGameIdx(const std::size_t &gameIdx)
{
    this->_game_idx = gameIdx;
}

std::size_t Info::getGraphIdx() const
{
    return this->_graph_idx;
}

std::size_t Info::getGameIdx() const
{
    return this->_game_idx;
}

std::size_t Info::getSide() const
{
    return this->_side;
}

void Info::setSide(const std::size_t &side)
{
    this->_side = side;
}

const std::vector<std::string> &Info::getGraphNames() const
{
    return this->_graphNames;
}

const std::vector<std::string> &Info::getGameNames() const
{
    return this->_gameNames;
}
