/*
** EPITECH PROJECT, 2020
** Pacman
** File description:
** Ghost.cpp
*/

#include "../includes/Ghost.hpp"

pcm::Ghost::Ghost(size_t x, size_t y, size_t mapH, size_t mapW) : pcm::Entity(x, y, mapH, mapW)
{
    _freeze         =   true;
    _freezeClock    =   std::chrono::high_resolution_clock::now();
    _direction      =   (rand() % 2) ? KEY_LEFT : KEY_RIGHT;
    _entityChar     =   GHOST_CHAR;
    _fearChar       =   FEARED_GHOST_CHAR;
    _statesChar     =   {GHOST_CHAR};
}

pcm::Ghost::~Ghost()
{
}

unsigned int translateDir(Input in)
{
    static unsigned int arr[4] = {DIR_UP, DIR_DOWN, DIR_LEFT, DIR_RIGHT};
    return arr[in];
}

unsigned int translateDir(unsigned int in)
{
    static unsigned int arr[4] = {DIR_UP, DIR_DOWN, DIR_LEFT, DIR_RIGHT};
    return arr[in];
}

bool
pcm::Ghost::_checkObstacleInLine(const pcm::Map &map, size_t ghostIdx, size_t targetIdx)
{
    if (ghostIdx / _mapW == targetIdx / _mapW) {
        if (ghostIdx > targetIdx) {
            for (--ghostIdx, ++targetIdx; ghostIdx > targetIdx; --ghostIdx, ++targetIdx) {
                if (map.getTile(ghostIdx) == WALL_CHAR || map.getTile(targetIdx) == WALL_CHAR)
                    return true;
            }
        } else {
            for (++ghostIdx, --targetIdx; ghostIdx < targetIdx; ++ghostIdx, --targetIdx) {
                if (map.getTile(ghostIdx) == WALL_CHAR || map.getTile(targetIdx) == WALL_CHAR)
                    return true;
            }
        }
    } else {
        if (ghostIdx > targetIdx) {
            for (ghostIdx -= _mapW, targetIdx += _mapW; ghostIdx > targetIdx; ghostIdx -= _mapW, targetIdx += _mapW) {
                if (map.getTile(ghostIdx) == WALL_CHAR || map.getTile(targetIdx) == WALL_CHAR)
                    return true;
            }
        } else {
            for (ghostIdx += _mapW, targetIdx -= _mapW; ghostIdx < targetIdx; ghostIdx += _mapW, targetIdx -= _mapW) {
                if (map.getTile(ghostIdx) == WALL_CHAR || map.getTile(targetIdx) == WALL_CHAR)
                    return true;
            }
        }
    }
    return false;
}

size_t
pcm::Ghost::_checkPathNbr(pcm::Map &map, unsigned int &possibilities)
{
    size_t count = 0;

    if (map.getTile(_pos.x, _pos.y - 1) != WALL_CHAR) {
        ++count;
        possibilities += DIR_UP;
    }
    if (map.getTile(_pos.x, _pos.y + 1) != WALL_CHAR) {
        ++count;
        possibilities += DIR_DOWN;
    }
    if (map.getTile(_pos.x - 1, _pos.y) != WALL_CHAR) {
        ++count;
        possibilities += DIR_LEFT;
    }
    if (map.getTile(_pos.x + 1, _pos.y) != WALL_CHAR) {
        ++count;
        possibilities += DIR_RIGHT;
    }

    return count;
}

bool
pcm::Ghost::_CheckVision(pcm::Map &map, const unsigned int direction, const size_t pacmanPosition)
{
    size_t idx;
    switch (direction)
    {
    case DIR_UP :
        idx = _pos.idx - _mapW;

        while (idx < map.getSize() && map[idx] != WALL_CHAR) {
            if (idx == pacmanPosition)
                return true;
            idx -= _mapW;
        }
        break;

    case DIR_DOWN :
        idx = _pos.idx + _mapW;;

        while (idx < map.getSize() && map[idx] != WALL_CHAR) {
            if (idx == pacmanPosition)
                return true;
            idx += _mapW;
        }
        break;

    case DIR_LEFT :
        idx = _pos.idx - 1;

        do {
            if (idx == pacmanPosition)
                return true;
            --idx;
        } while (idx % _mapW && map[idx] != WALL_CHAR);
        break;

    case DIR_RIGHT :
        idx = _pos.idx + 1;

        do {
            if (idx == pacmanPosition)
                return true;
            ++idx;
        } while ((idx % _mapW) != _mapW - 1 && map[idx] != WALL_CHAR);
        break;

    default:
        break;
    }
    return false;
}

bool
pcm::Ghost::_watchLane(pcm::Map &map, const pcm::position_t &pacmanLocation)
{
    if (_pos.y == pacmanLocation.y) {
        if (_pos.x > pacmanLocation.x) {
            if (_CheckVision(map, DIR_LEFT, pacmanLocation.idx)) {
                _direction = getDir(DIR_LEFT);
                return true;
            }
        } else {
            if (_CheckVision(map, DIR_RIGHT, pacmanLocation.idx)) {
                _direction = getDir(DIR_RIGHT);
                return true;
            }
        }
    } else if (_pos.x == pacmanLocation.x) {
        if (_pos.y > pacmanLocation.y) {
            if (_CheckVision(map, DIR_DOWN, pacmanLocation.idx)) {
                _direction = getDir(DIR_DOWN);
                return true;
            }
        } else {
            if (_CheckVision(map, DIR_UP, pacmanLocation.idx)) {
                _direction = getDir(DIR_UP);
                return true;
            }
        }
    }
    return false;
}

void pcm::Ghost::_moveStraight(pcm::Map &map, unsigned int possibilities)
{
    if ((this->*_movement[_direction])(map))
        return;
    possibilities -= backDir(_direction);
    for (unsigned int idx = 1; idx < 9; idx *= 2) {
        if (idx == possibilities) {
            _direction = getDir(idx);
            (this->*_movement[_direction])(map);
            return;
        }
    }
}

bool pcm::Ghost::_chooseLane(unsigned int possibilities)
{
    unsigned int choice = rand() % 4;

    possibilities -= backDir(_direction);
    while ((translateDir(choice) & possibilities) == 0) {
        choice = (choice + 1) % 4;
    }
    _direction = getDir(translateDir(choice));
    return true;
}

void
pcm::Ghost::move(pcm::Map &map, const pcm::position_t &pacmanLocation, bool isSuper)
{
    if (_checkFreeze(map))
        return;
    unsigned int possibilities = DIR_NO_SET;
    size_t nbrPossibilities = _checkPathNbr(map, possibilities);

    _lastPos = this->_pos.idx;
    if (nbrPossibilities < 3) {
        _moveStraight(map, possibilities);
    } else {
        if (_watchLane(map, pacmanLocation)) {
           if (isSuper) {
               _chooseLane(possibilities);
           }
        } else {
            _chooseLane(possibilities);
        }
        (this->*_movement[_direction])(map);
    }
}

void
pcm::Ghost::freeze(void)
{
    _freeze = true;
    _freezeClock = std::chrono::high_resolution_clock::now();
}

void
pcm::Ghost::resetEntity(void)
{
    this->setPos(this->_startPos);
    _direction = (rand() % 2) ? KEY_LEFT : KEY_RIGHT;

    this->freeze();
}

char
pcm::Ghost::getFearChar(void) const
{
    return _fearChar;
}

bool
pcm::Ghost::_checkFreeze(pcm::Map &map)
{
    if (_freeze) {
        if (getTimeElapsed(_freezeClock) > 6000.0) {
            _freeze = false;
            map.setRenderMapTile(_pos.idx, EMPTY_CHAR);
            this->setIdx(_pos.idx - (2 * _mapW));
        }
    }
    return _freeze;
}