/*
** EPITECH PROJECT, 2020
** Epitech
** File description:
** A_Sfml
*/

#include "../include/Arcade_Sfml.hpp"

Arcade::A_Sfml::A_Sfml()
{
    _window.create(sf::VideoMode(1280, 960), "SFML");
    _window.setFramerateLimit(60);
    _window.setKeyRepeatEnabled(true);

    if (!_parrallax2.loadFromFile("lib/Sfml/assets/parralax2.png"))
        printf("Problème charge menu");
    _parallax.setTexture(_parrallax2);
    if (!_Tarrow.loadFromFile("lib/Sfml/assets/dArrow.png"))
        printf("Problème charge arrow");
    _dArrow.setTexture(_Tarrow);

    sf::IntRect tmp(0, 0, 1280, 960);
    _rect = tmp;
    
    if (!_font.loadFromFile("lib/Sfml/assets/BohemianTypewriter.ttf")) {
        printf("Problème font");
    }
    if (!_font2.loadFromFile("lib/Sfml/assets/BohemianTypewriter.ttf")) {
        printf("Problème font");
    }
    if (!_mfont.loadFromFile("lib/Sfml/assets/BohemianTypewriter.ttf")) {
        printf("Problème font");
    }

    _name->setPosition(1280/2-100, 32);
    _name->setFont(_font);
    _name->setFillColor(sf::Color(128, 128, 0));
    _name->setCharacterSize(50);
    _name->setString("Arcade");

    for (size_t i = 0; i < 10; i++) {
        sf::Texture tmp;
        mTexture.push_back(tmp);
        if (!mTexture[i].loadFromFile("lib/Sfml/assets/button2.png"))
            printf("Problème\n");
    }
    for (size_t i = 0; i < mTexture.size(); i++) {
        sf::Sprite tmp2;
        mSprite.push_back(tmp2);
        mSprite[i].setTexture(mTexture[i]);
    }

    for (size_t i = 0; i < 4; i++) {
        sf::Texture tmp;
        t_arrow.push_back(tmp);
        if (!t_arrow[i].loadFromFile("lib/Sfml/assets/arrow.png"))
            printf("Problème\n");
    }
    for (size_t i = 0; i < t_arrow.size(); i++) {
        sf::Sprite tmp2;
        _arrow.push_back(tmp2);
        _arrow[i].setTexture(t_arrow[i]);
    }
     _arrow[0].setPosition(100, 200 + 150);
     _arrow[1].setPosition(550, 200 + 150);
     if (!_Tpseudo.loadFromFile("lib/Sfml/assets/button2.png"))
            printf("Problèmeaaaaa\n");
    _pseudo.setTexture(_Tpseudo);
    _pseudo.setPosition(950, 150);

    _pseud->setPosition(960, 160);
    _pseud->setFont(_font);
    _pseud->setFillColor(sf::Color(128, 128, 0));
    _pseud->setCharacterSize(50);

    _fill->setPosition(100, 175);
    _fill->setString("Veuillez remplir votre Pseudo pour avant de lancer le jeu :");
    _fill->setFont(_font);
    _fill->setFillColor(sf::Color(128, 128, 0));
    _fill->setCharacterSize(25);

    for (size_t i = 0; i < 3; i++) {
        sf::Texture tmp;
        t_score2.push_back(tmp);
        if (!t_score2[i].loadFromFile("lib/Sfml/assets/button2.png"))
            printf("Problème\n");
    }
    for (size_t i = 0; i < t_score2.size(); i++) {
        sf::Sprite tmp2;
        _score2.push_back(tmp2);
        _score2[i].setTexture(t_score2[i]);
    }
    for (size_t i = 0; i < 3; i++) {
        sf::Text *tmp = new sf::Text();
        _nameScore.push_back(tmp);
        _nameScore[i]->setPosition(270 * (i + 1), 710);
        _nameScore[i]->setFont(_font);
        _nameScore[i]->setFillColor(sf::Color(0, 128, 0));
        _nameScore[i]->setCharacterSize(30);
    }
}

Arcade::A_Sfml::~A_Sfml()
{
    _window.close();
}

void Arcade::A_Sfml::init(const std::vector<InitTab> &arr)
{
    _sprite.clear();
    _texture.clear();
    map.clear();
    _index.clear();
    _ix_side = 0;
    for (size_t i = 0; i < arr.size(); i++) {
        sf::Texture tmp;
        _index.push_back(arr[i].getCharacter());
        _texture.push_back(tmp);
        if (!_texture[i].loadFromFile(arr[i].getPath()))
            printf("Problème\n");
    }
    for (size_t i = 0; i < _texture.size(); i++) {
        sf::Sprite tmp2;
        _sprite.push_back(tmp2);
        _sprite[i].setTexture(_texture[i]);
    }
    for (size_t i = 0; i < arr.size(); i++) {
        map[_index[i]] = _sprite[i];
    }
    
    _scor->setPosition(32 * 10, 32);
    _scor->setFont(_font);
    _scor->setFillColor(sf::Color(128, 128, 0));
    _scor->setCharacterSize(45);

    _lif->setPosition(32 * 25, 32);
    _lif->setFont(_font2);
    _lif->setCharacterSize(45);
    _lif->setFillColor(sf::Color(128, 128, 0));
}

void Arcade::A_Sfml::setPreview(std::vector<std::vector<char>> &)
{

}

void Arcade::A_Sfml::displayGame(const std::vector<std::vector<char>> &arr)
{
    _scor->setString("Score: " + _score);
    _lif->setString("Life: " + _life);
    int size = 32;
    int space = 1;

    if ((arr.size() + 4) * size > 1080) {
        for (;(arr.size() + 8) * size > 1080; size -= 2);
        for (size_t i = 0; i < _index.size(); i++) {
            map[_index[i]].setScale(0.8, 0.8);
        }
    }
    for (; (arr[5].size()) + space < 640; space++);
    space = space / 2;
    _window.clear();
    _window.draw(*_scor);
    _window.draw(*_lif);
    for (size_t y = 0; y < arr.size(); y++) {
        for (size_t x = 0; x < arr[y].size(); x++) {
            map[arr[y][x]].setPosition(space + (x * size), (y+4) * size);
            _window.draw(map[arr[y][x]]);
        }
    }
    _window.display();
}

void Arcade::A_Sfml::setPosition(const Info info)
{
    size_t i = 0;

    for (; i < _game.size(); i++) {
        mSprite[i].setPosition(250, 200 + 120 * (i + 1));
    }
    for (size_t x = 0; x < _lib.size(); i++, x++) {
        mSprite[i].setPosition(700, 200 + 120 * (x + 1));
    }
    ix_game = info.getGameIdx();
    ix_lib = info.getGraphIdx();
    _ix_side = info.getSide();

    if (_ix_side == 0) {
        _dArrow.setPosition(325, 225);
        _arrow[0].setPosition(100, 200 + 120 * (ix_game + 1));
    } else if (_ix_side == 1) {
        _dArrow.setPosition(760, 225);
        _arrow[1].setPosition(550, 200 + 120 * (ix_lib + 1));
    } else if (_ix_side == 3) {
        _dArrow.setPosition(1010, 50);
    }

    for (size_t i = 0; i < _game.size(); i++) {
        sf::Text *tmp = new sf::Text();
        _nameG.push_back(tmp);
        _nameG[i]->setString(_game[i]);
        _nameG[i]->setPosition(300, 220 + 120 * (i + 1));
        _nameG[i]->setFont(_font);
        _nameG[i]->setFillColor(sf::Color(0, 128, 0));
        _nameG[i]->setCharacterSize(30);
    }
    for (size_t i = 0; i < _lib.size(); i++) {
        sf::Text *tmp = new sf::Text();
        _nameL.push_back(tmp);
        _nameL[i]->setString(_lib[i]);
        _nameL[i]->setPosition(750, 220 + 120 * (i + 1));
        _nameL[i]->setFont(_font);
        _nameL[i]->setFillColor(sf::Color(0, 128, 0));
        _nameL[i]->setCharacterSize(30);
    }
    for (size_t i = 0; i < 3; i++) {
        _score2[i].setPosition(250 * (i + 1), 750);
    }
    _sco = info.getScoring();
    for (size_t i = 0; i < _sco.size() && i < 3; i++) {
        sf::Text *tmp = new sf::Text();
        _scoreN.push_back(tmp);
        _scoreN[i]->setString(_sco[i].getName() + " " + _sco[i].getScore());
        _scoreN[i]->setPosition(270 * (i + 1), 775);
        _scoreN[i]->setFont(_font);
        _scoreN[i]->setFillColor(sf::Color(0, 128, 128));
        _scoreN[i]->setCharacterSize(25);
    }
}

void Arcade::A_Sfml::displayMenu(const Info &info)
{
    if (_rect.left == 1280)
        _rect.left = 0;
    else
        _rect.left += 5;
    _parallax.setTextureRect(_rect);

    _game = info.getGameNames();
    _lib = info.getGraphNames();

    setPosition(info);
    _pseud->setString(input);

    _window.clear();
    _window.draw(_parallax);
    _window.draw(*_name);
    _window.draw(_dArrow);
    for (size_t i = 0; i < _game.size() && i < _lib.size(); i++)
        _window.draw(_arrow[i]);
    for (size_t i = 0; i < _game.size() + _lib.size(); i++) {
        _window.draw(mSprite[i]);
    }
    for (size_t i = 0; i < _game.size(); i++)
        _window.draw(*_nameG[i]);
    for (size_t i = 0; i < _lib.size(); i++)
        _window.draw(*_nameL[i]);
    for (size_t i = 0; i < _score2.size(); i++)
        _window.draw(_score2[i]);
    for (size_t i = 0; i < _scoreN.size(); i++)
        _window.draw(*_scoreN[i]);
    _window.draw(_pseudo);
    _window.draw(*_pseud);
    _window.draw(*_fill);
    _window.display();
}

void Arcade::A_Sfml::setScore(const std::string &score)
{
    _score = score;
}

void Arcade::A_Sfml::setLife(const std::string &life)
{
    _life = life;
}

Input Arcade::A_Sfml::getInput()
{
    Input ret = Input::NONE;

    while (_window.pollEvent(_event))
    {
        // Close window: exit
        if (_event.type == sf::Event::Closed) {
            _window.close();
        }
        if (!_window.isOpen())
            return Input::EXIT;
        if (_ix_side == 3 && _event.key.code == sf::Keyboard::BackSpace) {
            if (!input.empty())
                input.pop_back();
        } else if (_ix_side == 3 && _event.type == sf::Event::TextEntered) {
            if (_event.text.unicode < 128) {
                input += static_cast<char>(_event.text.unicode);
        }
        }
        if (_event.type == sf::Event::KeyPressed) {
            if (_event.key.code == sf::Keyboard::Left) {
                ret = Input::LEFT;
            } else if (_event.key.code == sf::Keyboard::Right) {
                ret = Input::RIGHT;
            } else if (_event.key.code == sf::Keyboard::Up) {
                ret = Input::UP;
            } else if (_event.key.code == sf::Keyboard::Down) {
                ret = Input::DOWN;
            } else if (_event.key.code == sf::Keyboard::A) {
                ret = Input::PREV_GAME;
            } else if (_event.key.code == sf::Keyboard::E) {
                ret = Input::NEXT_GAME;
            } else if (_event.key.code == sf::Keyboard::W) {
                ret = Input::PREV_GRAPH;
            } else if (_event.key.code == sf::Keyboard::C) {
                ret = Input::NEXT_GRAPH;
            } else if (_event.key.code == sf::Keyboard::Enter) {
                ret = Input::ENTER;
            } else if (_event.key.code == sf::Keyboard::Escape)
                ret = Input::EXIT;
             else
                ret = Input::NONE;
        }
    }
    return ret;
}

std::string Arcade::A_Sfml::getName()
{
    if (!input.empty())
        input.pop_back();
    return input;
}

extern "C"
{
    std::shared_ptr<IGraphics> createInterface()
    {
        return std::make_shared<Arcade::A_Sfml>();
    }
}