/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Score
*/

#include "../includes/Score.hpp"

Score::Score(std::string name, std::string score)
{
    this->_name = name;
    this->_score = score;
}

Score::~Score()
{
}

const std::string &Score::getName() const
{
    return (this->_name);
}

const std::string &Score::getScore() const
{
    return (this->_score);
}

void Score::addScore(std::string filepath, std::string name, std::string score)
{
    std::ofstream file;

    if (name.find('\n') != std::string::npos)
        name.erase(name.end() - 1, name.end());
    file.open(filepath, std::ios::app);
    file << name + ":" + score << std::endl;
    file.close();
}