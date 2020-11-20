/*
** EPITECH PROJECT, 2020
** Pacman
** File description:
** game.cpp
*/

#include "../includes/Pacman.hpp"

pcm::Pacman::Pacman()
{
    srand (time(NULL));
    _life       = 1;
    _score      = 0;
    _strLife    = "1";
    _strScore   = "0";
    _gameSpeed  = GAME_SPEED;
    this->_gameAssets = {
        {PACMAN_FULL_CHAR,  PACMAN_FULL_I_COLOR,    PACMAN_FULL_O_COLOR,    PACMAN_FULL_TEXT_PATH},
        {PACMAN_MID_CHAR,   PACMAN_MID_I_COLOR,     PACMAN_MID_O_COLOR,     PACMAN_MID_TEXT_PATH},
        {PACMAN_OPEN_CHAR,  PACMAN_OPEN_I_COLOR,    PACMAN_OPEN_O_COLOR,    PACMAN_OPEN_TEXT_PATH},
        {GHOST_CHAR,        GHOST_I_COLOR,          GHOST_O_COLOR,          GHOST_TEXT_PATH},
        {GUM_CHAR,          GUM_I_COLOR,            GUM_O_COLOR,            GUM_TEXT_PATH},
        {SUPERGUM_CHAR,     SUPERGUM_I_COLOR,       SUPERGUM_O_COLOR,       SUPERGUM_TEXT_PATH},
        {WALL_CHAR,         WALL_I_COLOR,           WALL_O_COLOR,           WALL_TEXT_PATH},
        {FEARED_GHOST_CHAR, FEARED_GHOST_I_COLOR,   FEARED_GHOST_O_COLOR,   FEARED_GHOST_TEXT_PATH}
    };

    _player = std::make_shared<pcm::Player>(_map.getPlayerPos().x, _map.getPlayerPos().y, _map.getH(), _map.getW());

    for (unsigned char idx = 0; idx != 4; ++idx) {
        _ghosts[idx] = std::make_shared<pcm::Ghost>(_map.getGhostPos().x, _map.getGhostPos().y, _map.getH(), _map.getW());
    }

    _entitiesPos = {
        _player->getPos(),
        _ghosts[0]->getPos(),
        _ghosts[1]->getPos(),
        _ghosts[2]->getPos(),
        _ghosts[3]->getPos()
    };

    _moveClock      = std::chrono::high_resolution_clock::now();
    _animationClock = _moveClock;
}

pcm::Pacman::~Pacman()
{
}

bool
pcm::Pacman::checkColideEntity(void)
{
    for (auto &ghost : _ghosts) {
        if (ghost->getIdx() == _player->getIdx() \
        || (_player->getIdx() == ghost->getLastPos() && ghost->getIdx() == _player->getLastPos())) {
            if (_player->isSuper() == false)
                return true;
            _addScore(200);
            ghost->resetEntity();
        }
    }
    return false;
}

bool
pcm::Pacman::applyCaseEffect(void)
{
    char actualCase = _map.getTile(_player->getIdx());

    if (checkColideEntity())
        return true;

    switch (actualCase)
    {
        case GUM_CHAR:
            _addScore(10);
            _map.setTile(_player->getIdx(), EMPTY_CHAR);
            _map.subGum();
            break;
        case SUPERGUM_CHAR:
            _addScore(50);
            _player->setSuperPacman();
            _map.setTile(_player->getIdx(), EMPTY_CHAR);
            _map.subGum();
            break;
        default:
            break;
    }
    return false;
}

void
pcm::Pacman::_addScore(int points)
{
    if (_score < 10000 && _score + points >= 10000) {
        ++_life;
        _strScore = std::to_string(_life);
    }
    _score += points;
    _strScore = std::to_string(_score);
}

void
pcm::Pacman::_loseLife(void)
{
    --_life;
    _strLife = std::to_string(_life);
}

bool
pcm::Pacman::_checkFrame(void)
{
    if (getTimeElapsed(_moveClock) > 100.0) {
        _moveClock = std::chrono::high_resolution_clock::now();
        return true;
    }
    return false;
}

const std::vector<std::vector<char>> &
pcm::Pacman::simulate(Input key)
{
    if (this->_map.getGumsNbr() == 0) {
        this->_map.changeMap();
        this->_player->resetEntity();
        for (auto &ghost : this->_ghosts)
            ghost->resetEntity();
    } else {
        this->_player->checkSuperPacman();
        if (this->applyCaseEffect()) {
            this->_loseLife();
            this->_player->resetEntity();
            return this->_map.getRenderMap();
        }
        // move entities
        if (_checkFrame()) {
            this->_player->move(this->_map, key);
            for (unsigned char idx = 0; idx < 4; ++idx) {
                _ghosts.at(idx)->move(this->_map, this->_player->getPos(), _player->isSuper());
            }
        }
        // update render map
        _entitiesPos = {
            _player->getPos(),
            _ghosts[0]->getPos(),
            _ghosts[1]->getPos(),
            _ghosts[2]->getPos(),
            _ghosts[3]->getPos()
        };
        // anime pacman
        {
            if (getTimeElapsed(_animationClock) > 100) {
                _animationClock = std::chrono::high_resolution_clock::now();
                _player->setNextEntityChar();
            }
        }
        {
            char ghostEntityChar = _ghosts[0]->getEntityChar();
            if (_player->isSuper())
                ghostEntityChar = _ghosts[0]->getFearChar();
            this->_map.updateRenderMap(_entitiesPos, _player->getEntityChar(), ghostEntityChar);
        }
    }
    return this->_map.getRenderMap();
}

const std::string &
pcm::Pacman::getScore(void) const
{
    return _strScore;
}

const std::string &
pcm::Pacman::getLife(void) const
{
    return _strLife;
}

const std::vector<InitTab> &
pcm::Pacman::getInit(void) const
{
    return _gameAssets;
}

const float &
pcm::Pacman::getSpeed(void) const
{
    return _gameSpeed;
}

extern "C"
{
    std::shared_ptr<IGames>
    createInterface(void)
    {
        return std::make_shared<pcm::Pacman>();
    }
}