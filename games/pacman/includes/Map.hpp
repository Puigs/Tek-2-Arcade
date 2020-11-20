/*
** EPITECH PROJECT, 2020
** Pacman
** File description:
** Map header
*/

#ifndef MAP_HPP_
#define MAP_HPP_

#include "My.hpp"

#define MAPS_NBR 2;

namespace pcm
{
    class Map {
        public:
            Map();
            ~Map();
            char                                    operator[](size_t idx);


            void                                    changeMap       (void);
            void                                    updateRenderMap (std::array<pcm::position_t, 5> &pos, char _playerChar, char _ghostChar);
            void                                    subGum          (void);
            // setter
            void                                    setTile         (size_t x, size_t y, char tile);
            void                                    setTile         (size_t idx, char tile);
            void                                    setRenderMapTile(size_t x, size_t y, char tile);
            void                                    setRenderMapTile(size_t idx, char tile);
            // getter
            const std::vector<std::vector<char>> &  getRenderMap    (void)              const;
            const pcm::position_t &                 getPlayerPos    (void)              const;
            const pcm::position_t &                 getGhostPos     (void)              const;
            char                                    getTile         (size_t x, size_t y)const;
            char                                    getTile         (size_t idx)        const;
            size_t                                  getSize         (void)              const;
            size_t                                  getH            (void)              const;
            size_t                                  getW            (void)              const;
            int                                     getGumsNbr      (void)              const;
        private:
            // method:
            void                                    _initMap        (const std::string filename);
            char                                    _getMapTile     (const char tile, const size_t idx);
            // variable :
            std::string                             _map;
            std::vector<std::vector<char>>          _renderMap;
            pcm::position_t                         _startPlayerPos;
            pcm::position_t                         _startGhostsPos;
            size_t                                  _h;
            size_t                                  _w;
            size_t                                  _size;
            size_t                                  _selectedMap;
            int                                     _gumsCount;
    };
}
#endif /* !MAP_HPP_ */