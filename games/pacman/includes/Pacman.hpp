/*
** EPITECH PROJECT, 2020
** Pacman
** File description:
** Game header
*/

#ifndef GAME_HPP_
#define GAME_HPP_

#include "My.hpp"
#include "Map.hpp"
#include "Player.hpp"
#include "Ghost.hpp"
#include "IGame.hpp"

namespace pcm
{
    class Pacman : public IGames {
        public:
            enum {
                PACMAN_IDX_E,
                GHOST_IDX_E,
                GUM_IDX_E,
                SUPERGUM_IDX_E,
                SPACE_IDX_E,
                WALL_IDX_E
            };
        public:
            Pacman();
            ~Pacman();

            bool                                        applyCaseEffect (void);

            // INTERFACE FUNCTION :
            const std::vector<std::vector<char>> &          simulate            (Input key);
            const std::string &                             getScore            (void)                  const;
            const std::string &                             getLife             (void)                  const;
            const std::vector<InitTab> &                    getInit             (void)                  const;
            const float &                                   getSpeed            (void)                  const;
        private:
            void                                            _addScore           (int points);
            void                                            _loseLife           (void);
            bool                                            _checkFrame         (void);
            bool                                            checkColideEntity   (void);

            int                                             _life;
            std::string                                     _strLife;
            int                                             _score;
            std::string                                     _strScore;

            pcm::Map                                        _map;
            std::vector<InitTab>                            _gameAssets;
            std::shared_ptr<pcm::Player>                    _player;
            std::array<std::shared_ptr<pcm::Ghost>, 4>      _ghosts;
            std::array<pcm::position_t, 5>                  _entitiesPos;
            STD_CLOCK                                       _moveClock;
            STD_CLOCK                                       _animationClock;
            float                                           _gameSpeed;
    };
}


#endif /* !GAME_HPP_ */
