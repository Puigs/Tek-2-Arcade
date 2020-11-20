/*
** EPITECH PROJECT, 2020
** Pacman
** File description:
** Ghost header
*/

#ifndef GHOST_HPP_
#define GHOST_HPP_

#include "My.hpp"
#include "Entity.hpp"
#include "Map.hpp"

namespace pcm
{
    class Ghost : virtual public Entity {
        public:
            Ghost(size_t x, size_t y, size_t mapH, size_t mapW);
            ~Ghost();

            void            move                    (pcm::Map &map, const pcm::position_t &pacmanLocation, bool isSuper);
            void            freeze                  (void);
            void            resetEntity             (void) override;
            char            getFearChar             (void) const;
        private:
            // method
            bool            _checkFreeze            (pcm::Map &map);
            bool            _checkObstacleInLine    (const pcm::Map &map, size_t ghostIdx, size_t targetIdx);
            size_t          _checkPathNbr           (pcm::Map &map, unsigned int &possibilities);
            bool            _CheckVision            (pcm::Map &map, const unsigned int direction, const size_t pacmanPosition);
            bool            _watchLane              (pcm::Map &map, const pcm::position_t &pacmanLocation);


            void            _moveStraight           (pcm::Map &map, unsigned int possibilities);
            bool            _chooseLane             (unsigned int possibilities);
            // variable
            bool            _freeze;
            char            _fearChar;
            // clock
            STD_CLOCK     _freezeClock;
    };
}

#endif /* !GHOST_HPP_ */