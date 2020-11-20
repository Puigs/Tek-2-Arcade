/*
** EPITECH PROJECT, 2020
** Pacman
** File description:
** Entity.cpp
*/

#include "../includes/Entity.hpp"

pcm::Entity::Entity(size_t x, size_t y, size_t mapH, size_t mapW)
{
    _pos                    =   {.x = x, .y = y, .idx = x + (mapW * y)};
    _startPos               =   {.x = x, .y = y, .idx = x + (mapW * y)};
    _mapH                   =   mapH;
    _mapW                   =   mapW;
    _direction              =   NONE;
    _lastPos                =   _pos.idx;
    _entityChar             =   0;
    _idxStateChar           =   0;

    _movement[KEY_UP]       =   &pcm::Entity::_moveUp;
    _movement[KEY_DOWN]     =   &pcm::Entity::_moveDown;
    _movement[KEY_LEFT]     =   &pcm::Entity::_moveLeft;
    _movement[KEY_RIGHT]    =   &pcm::Entity::_moveRight;
    _movement[NONE]         =   &pcm::Entity::_doNothing;
}

pcm::Entity::~Entity()
{
}

void
pcm::Entity::setPosX(size_t x)
{
    _pos.idx += (x - _pos.x);
    _pos.x = x;
}

void
pcm::Entity::setPosY(size_t y)
{
    if (_pos.y < y)
        _pos.idx += _mapW;
    else if (_pos.y > y)
        _pos.idx -= _mapW;
    _pos.y = y;
}

void
pcm::Entity::setPos(size_t x, size_t y)
{
    setPosX(x);
    setPosY(y);
}

void
pcm::Entity::setPos(pcm::position_t &pos)
{
    setPosX(pos.x);
    setPosY(pos.y);
    setIdx(pos.idx);
}

void
pcm::Entity::setIdx(size_t idx)
{
    _pos.idx = idx;
    _pos.y = idx / _mapW;
    _pos.x = idx % _mapW;
}

void
pcm::Entity::setDirection(Input direction)
{
    _direction = direction;
}

void
pcm::Entity::setNextEntityChar(void)
{
    _idxStateChar   = (_idxStateChar + 1) % _statesChar.size();
    _entityChar     = _statesChar.at(_idxStateChar);
}

void
pcm::Entity::resetEntity(void)
{
    this->setPos(this->_startPos);
    this->_lastPos = this->_startPos.idx;
    _direction = (rand() % 2) ? KEY_LEFT : KEY_RIGHT;
}

size_t
pcm::Entity::getPosX(void) const
{
    return _pos.x;
}

size_t
pcm::Entity::getPosY(void) const
{
    return _pos.y;
}

const pcm::position_t &
pcm::Entity::getPos(void) const
{
    return _pos;
}

size_t
pcm::Entity::getIdx(void) const
{
    return _pos.idx;
}

Input
pcm::Entity::getDirection(void) const
{
    return _direction;
}

size_t
pcm::Entity::getLastPos(void) const
{
    return _lastPos;
}

char
pcm::Entity::getEntityChar(void) const
{
    return _entityChar;
}

bool
pcm::Entity::_moveUp(pcm::Map &map)
{
    if ((this->getIdx() - _mapW < map.getSize()) && map.getTile(_pos.idx - _mapW) != WALL_CHAR) {
        this->setIdx(_pos.idx - _mapW);
        return true;
    }
    return false;
}

bool
pcm::Entity::_moveDown(pcm::Map &map)
{
    if ((this->getIdx() + _mapW < map.getSize()) && map.getTile(_pos.idx + _mapW) != WALL_CHAR) {
        this->setIdx(_pos.idx + _mapW);
        return true;
    }
    return false;
}

bool
pcm::Entity::_moveLeft(pcm::Map &map)
{
    size_t newIdxPos = _pos.x ? _pos.idx - 1 : _pos.idx + _mapW - 1;

    if (newIdxPos + 1 != _pos.idx)
        map.setRenderMapTile(_pos.idx, EMPTY_CHAR);
    if (map.getTile(newIdxPos) != WALL_CHAR) {
        this->setIdx(newIdxPos);
        return true;
    }
    return false;
}

bool
pcm::Entity::_moveRight(pcm::Map &map)
{
    size_t newIdxPos = (_pos.x == _mapW - 1) ? _pos.idx - _mapW + 1 : _pos.idx + 1;

    if (newIdxPos - 1 != _pos.idx)
        map.setRenderMapTile(_pos.idx, EMPTY_CHAR);
    if (map.getTile(newIdxPos) != WALL_CHAR) {
        this->setIdx(newIdxPos);
        return true;
    }
    return false;
}

bool
pcm::Entity::_doNothing(pcm::Map &map)
{
    map.getSize();
    return true;
}