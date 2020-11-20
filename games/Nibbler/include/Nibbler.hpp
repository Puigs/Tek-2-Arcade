/*
** EPITECH PROJECT, 2020
** Nibbler.hpp
** File description:
** Nibbler
*/

#ifndef NIBBLER_HPP_
#define NIBBLER_HPP_

#include <iostream>
#include <fstream>
#include "IGame.hpp"
#include <string>
#include <memory>
#include <algorithm>


namespace Arcad {
    class Nibbler : public IGames {
        public:
            Nibbler();
            ~Nibbler();
            const std::vector<std::vector<char>> &simulate(Input key);
            const std::string &getScore() const;
            const std::string &getLife() const;
            const std::vector<InitTab> &getInit() const;
            const float &getSpeed(void) const;
            void find_head();
            void init_move();
            void check_npos();
            int check_if_block();
            void make_move();
            void make_eat();
            void find_direction();
            int check_dir();
            void check_if_win();

        protected:
        private:
            std::string _score = "0";
            std::string _life = "1";
            std::vector<InitTab> _arr;
            std::vector<std::vector<char>> _array;
            Input _prec_input = NONE;
            Input _key;
            int _level = 1;
            std::vector<size_t> _pos;
            std::vector<size_t> _npos;
            std::vector<size_t> _ppos;
            std::vector<std::vector<size_t>> _cpos;
            char _dir;
            bool win = false;
    };
}

#endif /* !NIBBLER_HPP_ */
