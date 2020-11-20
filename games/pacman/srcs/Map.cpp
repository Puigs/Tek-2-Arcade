/*
** EPITECH PROJECT, 2020
** Pacman
** File description:
** Map.cpp
*/

#include "../includes/Map.hpp"

pcm::Map::Map()
{
    _h              =   0;
    _w              =   0;
    _size           =   0;
    _selectedMap    =  -1;
    _gumsCount      =   0;
    _startPlayerPos =  {0, 0, 0};
    _startGhostsPos =  {0, 0, 0};
    changeMap();
}

pcm::Map::~Map()
{
}
char
pcm::Map::operator[](size_t idx)
{
    return _map[idx];
}

char
pcm::Map::_getMapTile(const char tile, const size_t idx)
{
    if (tile == PACMAN_FULL_CHAR) {
        _startPlayerPos = {.x = idx % _w, .y = idx / _w, .idx = idx};
        return EMPTY_CHAR;
    } else if (tile == GHOST_CHAR) {
        _startGhostsPos = {.x = idx % _w, .y = idx / _w, .idx = idx};
        return EMPTY_CHAR;
    }
    if (tile == GUM_CHAR || tile == SUPERGUM_CHAR) {
        ++_gumsCount;
    }
    return tile;
}

void
pcm::Map::_initMap(const std::string filename)
{
    std::ifstream file(MAP_FOLDER_PATH + filename);
    std::string map("");
    _gumsCount = 0;

    if (file) {
        char tile;
        getline(file, map);
        file.close();
        if (_map.size())
            _map.clear();
        if (_renderMap.size())
            _renderMap.clear();
        for (size_t idx = 0, end = map.size(); idx < end;) {
            _renderMap.push_back(std::vector<char>());
            tile = _getMapTile(map[idx], idx);
            _map.push_back(tile);
            _renderMap.back().push_back(tile);
            for (++idx; idx < end && idx % _w; ++idx) {
                tile = _getMapTile(map[idx], idx);
                _map.push_back(tile);
                _renderMap.back().push_back(tile);
            }
        }
        _size = _h * _w;
    } else {
        // throw ERROR
    }
}

void
pcm::Map::changeMap(void)
{
    _selectedMap = (_selectedMap + 1) % 2;

    if (_selectedMap) {
        _h = 31;
        _w = 27;
        _initMap(MAP2);
    } else {
        _h = 31;
        _w = 27;
        _initMap(MAP1);
    }
}

void
pcm::Map::updateRenderMap(std::array<pcm::position_t, 5> &entitiesPos, char _playerChar, char _ghostChar)
{
    for (size_t idx = 0; idx != 5; ++idx) {
        _renderMap[entitiesPos[idx].y - 1][entitiesPos[idx].x] = this->getTile(entitiesPos[idx].x, entitiesPos[idx].y - 1);
        _renderMap[entitiesPos[idx].y + 1][entitiesPos[idx].x] = this->getTile(entitiesPos[idx].x, entitiesPos[idx].y + 1);
        if (entitiesPos[idx].x) {
            _renderMap[entitiesPos[idx].y][entitiesPos[idx].x - 1] = this->getTile(entitiesPos[idx].x - 1, entitiesPos[idx].y);
        }
        if (entitiesPos[idx].x != this->getW() - 1) {
            _renderMap[entitiesPos[idx].y][entitiesPos[idx].x + 1] = this->getTile(entitiesPos[idx].x + 1, entitiesPos[idx].y);
        }
    }
    _renderMap[entitiesPos.at(0).y][entitiesPos.at(0).x] = _playerChar;
    for (size_t idx = 1; idx != 5; ++idx) {
        _renderMap[entitiesPos[idx].y][entitiesPos[idx].x] = _ghostChar;
    }
}

void
pcm::Map::subGum(void)
{
    --_gumsCount;
}

// SETTER:

void
pcm::Map::setTile(size_t x, size_t y, char tile)
{
    _map[x + (y * _w)] = tile;
}

void
pcm::Map::setTile(size_t idx, char tile)
{
    _map[idx] = tile;
}

void
pcm::Map::setRenderMapTile(size_t x, size_t y, const char tile)
{
    _renderMap[y][x] = tile;
}

void
pcm::Map::setRenderMapTile(size_t idx, const char tile)
{
    _renderMap[idx / _w][idx % _w] = tile;
}

// GETTER:


const std::vector<std::vector<char>> &
pcm::Map::getRenderMap(void) const
{
    return _renderMap;
}

const pcm::position_t &
pcm::Map::getPlayerPos(void) const
{
    return _startPlayerPos;
}

const pcm::position_t &
pcm::Map::getGhostPos (void) const
{
    return _startGhostsPos;
}

char
pcm::Map::getTile(size_t x, size_t y) const
{
    return _map[(y * _w) + x];
}

char
pcm::Map::getTile(size_t idx) const
{
    return _map[idx];
}

size_t
pcm::Map::getSize(void) const
{
    return _size;
}

size_t
pcm::Map::getH(void) const
{
    return _h;
}

size_t
pcm::Map::getW(void) const
{
    return _w;
}

int
pcm::Map::getGumsNbr(void) const
{
    return _gumsCount;
}
