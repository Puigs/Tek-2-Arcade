/*
** EPITECH PROJECT, 2020
** SDL
** File description:
** Sdl.hpp
*/

#ifndef SDL_HPP_
#define SDL_HPP_

#include "My.hpp"

namespace sdl {
    class Sdl : public IGraphics {
        public:
            Sdl();
            ~Sdl();

            // INTERFACE
            void                            displayGame         (const std::vector<std::vector<char>> &arr);
            void                            displayMenu         (const Info &info);
            void                            setPreview          (std::vector<std::vector<char>> &);
            std::string                     getName             (void);
            void                            init                (const std::vector<InitTab> &arr);
            void                            setScore            (const std::string &score);
            void                            setLife             (const std::string &life);
            Input                           getInput            (void);
        private:
            void _destructor(void);
            // method
            void                            menuInit            (void);
            void                            resizeDefaultSize   (size_t x, size_t y);
            SDL_Texture *                   _createText         (const std::string &str, SDL_Rect &, TTF_Font *font, SDL_Color &color);
            SDL_Texture *                   _createText         (const char *str, SDL_Rect &, TTF_Font *font, SDL_Color &color);
            SDL_Texture *                   _createTexture      (std::string path);

            void                            _displaySelectedLib (const Info &info);
            void                            _displaySelectedGame(const Info &info);
            void                            _displayPlayerName  (void);
            void                            _displayScore       (const Info &info);
            size_t                          _stdSideToPrs       (size_t in);
            size_t                          _prsSideToStd       (size_t in);

            // variable
            bool                            _libIsInit;
            bool                            _libIsDestroy;
            std::string                     _scoreStr;
            std::string                     _lifeStr;
            bool                            _scoreUpdate;
            bool                            _lifeUpdate;

            // Positioning values :
            size_t                          _spriteSize;
            size_t                          _mapSizeW;
            size_t                          _mapSizeH;
            size_t                          _PrintBeginX;
            size_t                          _PrintBeginY;

            int                             _lastKey;

            // SDL VAR
            // The window we'll be rendering to
            SDL_Window *                    _window;
            // The surface contained by the window
            SDL_Renderer *                  _wdScreenRenderer ;
            // Event Manager
            SDL_Event                       _event;
            // Textures Conteneur
            std::map<char, SDL_Texture *>   _gameTextureMap;

            SDL_Texture *                   _scoreTexture;
            SDL_Texture *                   _lifeTexture;
            SDL_Rect                        _scorePosition;
            SDL_Rect                        _lifePosition;
            TTF_Font *                      _font;
            SDL_Color                       _colorText;

            // MENU VALUE:

            TTF_Font *                      _menuFont;
            SDL_Texture *                   _menuBackground;
            SDL_Texture *                   _menuArrow;
            SDL_Rect                        _arrowPos;            
            //SDL_Texture *                     _title;
            std::array<SDL_Texture *, 4>    _MenuOptionTitleTextureArray;
            std::array<SDL_Rect, 4>         _MenuOptionTitlePositionArray;
            std::array<SDL_Texture *, 4>    _MenuOptionItemsArray;
            std::array<SDL_Rect, 4>         _MenuOptionItemPositionArray;
            std::string                     _playerName;

            size_t                          _sidePos;
            std::vector<std::string>        _score_with_name;

            std::string                     _keyDescription;
            std::vector<SDL_Texture *>      _menuDescriptionTextures;
            SDL_Rect                        _menuDescriptionPos;
    };
}

#endif /* !SDL_HPP_ */

