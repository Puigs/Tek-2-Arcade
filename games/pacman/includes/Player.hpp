/*
** EPITECH PROJECT, 2020
** Pacman
** File description:
** Pacman header
*/

#ifndef PACMAN_HPP_
#define PACMAN_HPP_

#include "My.hpp"
#include "Entity.hpp"
#include "Map.hpp"

namespace pcm
{
    class Player : virtual public Entity {
        public:
            Player(size_t x, size_t y, size_t mapH, size_t mapW);
            ~Player();

            bool            checkSuperPacman    (void);
            void            move                (pcm::Map &map, Input e);
            // getter 
            bool            isSuper             (void)  const;
            // setter
            void            setSuperPacman      (void);
        private:
            // variable
            bool            _superPacman;
            STD_CLOCK       _superPacmanClock;

    };
}

#endif