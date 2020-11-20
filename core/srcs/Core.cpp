/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Core
*/

#include "../includes/Core.hpp"

Core::Core(const std::string &path)
{
    _info = Info();
    try {
        DlLoader<std::shared_ptr<IGraphics>> *libLoader = new DlLoader<std::shared_ptr<IGraphics>>(path);
        _Graphic = libLoader->getInstance("createInterface");
        _Game = nullptr;
        for (size_t i = 0; i < _info.getGraphNames().size(); i++) {
            if (path.find(_info.getGraphNames().at(i)) != std::string::npos)
                _info.setGraphIdx(i);
        }
    } catch (Exception e) {
        std::cerr << e.what() << std::endl;
        exit(84);
    }
}

Core::~Core()
{
}

int Core::infoLoading(Input inp)
{
    switch (inp)
    {
    case KEY_RIGHT:
        if (_info.getSide() == 3)
            _info.setSide(0);
        else
            _info.setSide(_info.getSide() + 1);
        break;
    case KEY_LEFT:
        if (_info.getSide() == 0)
            _info.setSide(3);
        else
            _info.setSide(_info.getSide() - 1);
        break;
    case KEY_DOWN:
        if (_info.getSide() == 1) {
            if (_info.getGraphIdx() == _info.getGraphNames().size() - 1)
                _info.setGraphIdx(0);
            else
                _info.setGraphIdx(_info.getGraphIdx() + 1);
        } else if (_info.getSide() == 0) {
            if (_info.getGameIdx() == _info.getGameNames().size() - 1)
                _info.setGameIdx(0);
            else
                _info.setGameIdx(_info.getGameIdx() + 1);
        }
        break;
    case KEY_UP:
        if (_info.getSide() == 1) {
            if (_info.getGraphIdx() == 0)
                _info.setGraphIdx(_info.getGraphNames().size() - 1);
            else
                _info.setGraphIdx(_info.getGraphIdx() - 1);
        } else if (_info.getSide() == 0) {
            if (_info.getGameIdx() == 0)
                _info.setGameIdx(_info.getGameNames().size() - 1);
            else
                _info.setGameIdx(_info.getGameIdx() - 1);
        }
        break;
    case ENTER:
        _playerName = _Graphic->getName();
        if (_playerName.empty() != true) {
            _Graphic.reset();
            gameLoop();
        }
        break;
    case EXIT:
        return 1;
        break;
    default:
        break;
    }
    return 0;
}

int Core::gameInputs(Input inp)
{
    DlLoader<std::shared_ptr<IGraphics>> *libLoader;
    DlLoader<std::shared_ptr<IGames>> *gamesLoader;

    switch (inp)
    {
    case PREV_GAME:
        if (_info.getGameIdx() == 0)
            _info.setGameIdx(_info.getGameNames().size() - 1);
        else
            _info.setGameIdx(_info.getGameIdx() - 1);
        gamesLoader = new DlLoader<std::shared_ptr<IGames>>("games/lib_arcade_" + _info.getGameNames().at(_info.getGameIdx()) + ".so");
        _Game.reset();
        _Game = gamesLoader->getInstance("createInterface");
        _Graphic->init(_Game->getInit());
        break;
    case NEXT_GAME:
        if (_info.getGameIdx() == _info.getGameNames().size() - 1)
            _info.setGameIdx(0);
        else
            _info.setGameIdx(_info.getGameIdx() + 1);
        gamesLoader = new DlLoader<std::shared_ptr<IGames>>("games/lib_arcade_" + _info.getGameNames().at(_info.getGameIdx()) + ".so");
        _Game.reset();
        _Game = gamesLoader->getInstance("createInterface");
        _Graphic->init(_Game->getInit());
        break;
    case PREV_GRAPH:
        if (_info.getGraphIdx() == 0)
            _info.setGraphIdx(_info.getGraphNames().size() - 1);
        else
            _info.setGraphIdx(_info.getGraphIdx() - 1);
        libLoader = new DlLoader<std::shared_ptr<IGraphics>>("lib/lib_arcade_" + _info.getGraphNames().at(_info.getGraphIdx()) + ".so");
        _Graphic.reset();
        _Graphic = libLoader->getInstance("createInterface");
        _Graphic->init(_Game->getInit());
        break;
    case NEXT_GRAPH:
        if (_info.getGraphIdx() == _info.getGraphNames().size() - 1)
            _info.setGraphIdx(0);
        else
            _info.setGraphIdx(_info.getGraphIdx() + 1);
        libLoader = new DlLoader<std::shared_ptr<IGraphics>>("lib/lib_arcade_" + _info.getGraphNames().at(_info.getGraphIdx()) + ".so");
        _Graphic.reset();
        _Graphic = libLoader->getInstance("createInterface");
        _Graphic->init(_Game->getInit());
        break;
    case EXIT:
        _Game.reset();
        return 1;
    case ENTER:
        gamesLoader = new DlLoader<std::shared_ptr<IGames>>("games/lib_arcade_" + _info.getGameNames().at(_info.getGameIdx()) + ".so");
        _Game.reset();
        _Game = gamesLoader->getInstance("createInterface");
        break;
    default:
        break;
    }
    return 0;
}

void Core::gameLoop()
{
    std::vector<std::vector<char>> map;
    std::vector<InitTab> _gameAssets;
    Input input;
    DlLoader<std::shared_ptr<IGraphics>> *libLoader = new DlLoader<std::shared_ptr<IGraphics>>("lib/lib_arcade_" + _info.getGraphNames().at(_info.getGraphIdx()) + ".so");
    DlLoader<std::shared_ptr<IGames>> *gamesLoader = new DlLoader<std::shared_ptr<IGames>>("games/lib_arcade_" + _info.getGameNames().at(_info.getGameIdx()) + ".so");
    _Game = gamesLoader->getInstance("createInterface");
    _Graphic = libLoader->getInstance("createInterface");
    _gameAssets = _Game->getInit();
    _Graphic->init(_gameAssets);
    while (1) {
        usleep(300000);
        input = _Graphic->getInput();
        if (gameInputs(input) == 1)
            return;
        map = _Game->simulate(input);
        _Graphic->setLife(_Game->getLife());
        if (std::stoi(_Game->getLife()) == 0 || std::stoi(_Game->getLife()) == 2) {
            Score::addScore("games/" + _info.getGameNames().at(_info.getGameIdx()) + ".txt", _playerName, _Game->getScore());
            _info.addScore(Score(_playerName, _Game->getScore()));
            return;
        }
        _Graphic->setScore(_Game->getScore());
        _Graphic->displayGame(map);
    }
}

void Core::parseScore()
{
    std::string line;
    std::string name;
    std::ifstream file("games/" + _info.getGameNames().at(_info.getGameIdx()) + ".txt");

    while (std::getline(file, line)) {
        name = line.substr(0, line.find(":"));
        _info.addScore(Score(name, line.erase(0, line.find(":") + 1)));
    }
}

void Core::MainLoop()
{
    parseScore();
    while (1) {
        usleep(20000);
        if (infoLoading(_Graphic->getInput()) == 1)
            return;
        _Graphic->displayMenu(_info);
    }
}