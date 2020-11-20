/*
** EPITECH PROJECT, 2020
** Score.hpp
** File description:
** Score
*/

#ifndef SCORE_HPP_
#define SCORE_HPP_

#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>

class Score {
    public:
        Score(std::string name, std::string score = 0);
        ~Score();
        const std::string &getName() const;
        const std::string &getScore() const;
        static void addScore(std::string filepath, std::string name, std::string score);
    protected:
    private:
        std::string _name;
        std::string _score;
};

#endif /* !SCORE_HPP_ */
