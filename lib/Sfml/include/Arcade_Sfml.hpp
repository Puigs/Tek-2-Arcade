/*
** EPITECH PROJECT, 2020
** Epitech
** File description:
** Sfml
*/

#ifndef SFML_HPP_
#define SFML_HPP_

#include "IGraphics.hpp"
#include "InitTab.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <stdio.h>
#include <memory>
#include <iostream>

namespace Arcade {
    class A_Sfml : public IGraphics {
        public:
            A_Sfml();
            ~A_Sfml();
            void init(const std::vector<InitTab> &arr);
            void displayGame(const std::vector<std::vector<char>> &arr);
            void displayMenu(const Info &info);
            void setScore(const std::string &score);
            void setLife(const std::string &life);
            Input getInput();
            std::string getName();
            void setPreview(std::vector<std::vector<char>> &);
            void setPosition(const Info info);

        protected:
        private:
            sf::RenderWindow _window;
            std::string _score;
            std::string _life;
            std::vector<sf::Sprite> _sprite;
            std::vector<sf::Texture> _texture;
            std::vector<char> _index;
            sf::Event _event;
            std::map<char, sf::Sprite> map;
            sf::Text *_scor = new sf::Text();
            sf::Text *_lif = new sf::Text();
            sf::Font _font;
            sf::Font _font2;

            //menu
            sf::Texture _parrallax2;
            sf::Sprite _parallax;
            sf::Texture _Tarrow;
            sf::Sprite _dArrow;
            std::vector<sf::Sprite> _arrow;
            std::vector<sf::Texture> t_arrow;
            sf::Clock _clock;
            sf::Time _time;
            sf::IntRect _rect;
            float _seconds;
            std::vector<sf::Sprite> mSprite;
            std::vector<sf::Texture> mTexture;
            size_t ix_game = 0;
            size_t ix_lib = 0;
            size_t _ix_side = 0;
            std::vector<std::string> _game;
            std::vector<std::string> _lib;
            sf::Text *_name = new sf::Text();
            sf::Font _mfont;
            std::vector<sf::Text *> _nameG;
            std::vector<sf::Text *> _nameL;
            std::string input = "";
            sf::Texture _Tpseudo;
            sf::Sprite _pseudo;
            sf::Text *_pseud = new sf::Text();
            std::vector<sf::Sprite> _score2;
            std::vector<sf::Texture> t_score2;
            std::vector<sf::Text *> _scoreN;
            std::vector<Score> _sco;
            //Remplir les Text avec les noms de joueurs et le score
            std::vector<sf::Text *> _nameScore;
            sf::Text *_fill = new sf::Text();
    };
}

#endif /* !SFML_HPP_ */
