/*
** EPITECH PROJECT, 2020
** Pacman
** File description:
** Pacman.cpp
*/

#include "../includes/Player.hpp"

pcm::Player::Player(size_t x, size_t y, size_t mapH, size_t mapW) : pcm::Entity(x, y, mapH, mapW)
{
    _superPacman            =   false;
    _direction              =   NONE;
    _entityChar             =   PACMAN_FULL_CHAR;
    _statesChar             =   {PACMAN_FULL_CHAR, PACMAN_OPEN_CHAR, PACMAN_MID_CHAR};
    _idxStateChar           =   0;
}

pcm::Player::~Player()
{
}

bool
pcm::Player::checkSuperPacman(void)
{
    if (_superPacman) {
        if (getTimeElapsed(_superPacmanClock) > 10000.0) {
            _superPacman = false;
        }
    }
    return _superPacman;
}   

void
pcm::Player::setSuperPacman()
{
    _superPacman = true;
    _superPacmanClock = std::chrono::high_resolution_clock::now();
}

void
pcm::Player::move(pcm::Map &map, Input in)
{
    _lastPos = this->_pos.idx;
    if (in != KEY_DOWN && in != KEY_UP && in != KEY_LEFT && in != KEY_RIGHT)
        in = this->_direction;
    if ((this->*_movement[in])(map) == false) {
        (this->*_movement[this->_direction])(map);
    } else {
        this->_direction = in;
    }
}

bool
pcm::Player::isSuper(void) const
{
    return _superPacman;
}