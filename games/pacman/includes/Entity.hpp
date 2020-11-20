/*
** EPITECH PROJECT, 2020
** Pacman
** File description:
** Entity.hpp
*/

#ifndef Entity_HPP_
#define Entity_HPP_

#include "My.hpp"
#include "Map.hpp"

namespace pcm
{
    class Entity {

        public:
            Entity(size_t x, size_t y, size_t mapH, size_t mapW);
            ~Entity();

            void                setPosX         (size_t x);
            void                setPosY         (size_t y);
            void                setPos          (size_t x, size_t y);
            void                setPos          (pcm::position_t &pos);
            void                setIdx          (size_t idx);
            void                setDirection    (Input direction);
            void                setNextEntityChar   (void);
            virtual void        resetEntity     (void);
            // virtual void        resetEntity     (size_t x, size_t y, size_t mapH, size_t mapW);

            size_t              getPosX         (void)  const;
            size_t              getPosY         (void)  const;
            const position_t &  getPos          (void)  const;
            size_t              getIdx          (void)  const;
            Input               getDirection    (void)  const;
            size_t              getLastPos      (void)  const;
            char                getEntityChar   (void)  const;
        protected:
            // method
            bool                _moveUp         (pcm::Map &map);
            bool                _moveDown       (pcm::Map &map);
            bool                _moveLeft       (pcm::Map &map);
            bool                _moveRight      (pcm::Map &map);
            bool                _doNothing      (pcm::Map &map);
            // variable
            position_t          _pos;
            position_t          _startPos;
            size_t              _lastPos;
            Input               _direction;
            size_t              _mapH;
            size_t              _mapW;
            char                _entityChar;
            std::string         _statesChar;
            size_t              _idxStateChar;


            typedef bool (pcm::Entity::*ftcPtr)(pcm::Map &);
            typedef std::map<Input, ftcPtr> fctPtrMap;

            fctPtrMap           _movement;
    };
} 

#endif /* !Entity_HPP_ */
