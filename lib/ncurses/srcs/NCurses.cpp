/*
** EPITECH PROJECT, 2020
** NCurses
** File description:
** NCurses
*/

#include "../includes/NCurses.hpp"

NCurses::NCurses()
{
    initscr();
    keypad(stdscr, TRUE);
    curs_set(0);
    cbreak();
    noecho();
    nodelay(stdscr, TRUE);
    notimeout(stdscr, FALSE);
    start_color();
    getmaxyx(stdscr, _winY, _winX);
    init_pair(100, 3, 0);
    init_pair(101, 1, 0);
    init_pair(102, 6, 0);
    init_pair(103, 6, 7);
    _scoreWin = NULL;
    _lifeWin = NULL;
    _gameWin = NULL;
    _gamesWin = NULL;
    _libWin = NULL;
    _scoresWin = NULL;
    _nameWin = NULL;
}

void destroy_win(WINDOW *win)
{
    wborder(win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    wrefresh(win);
    delwin(win);
}

NCurses::~NCurses()
{
    if (_scoreWin != NULL)
        destroy_win(_scoreWin);
    if (_lifeWin != NULL)
        destroy_win(_lifeWin);
    if (_gameWin != NULL)
        destroy_win(_gameWin);
    if (_gamesWin != NULL)
        destroy_win(_gamesWin);
    if (_scoresWin != NULL)
        destroy_win(_scoresWin);
    if (_libWin != NULL)
        destroy_win(_libWin);
    if (_nameWin != NULL)
        destroy_win(_nameWin);
    endwin();
}

void NCurses::resizeOrNewGame()
{
    _pos = 0;
    destroy_win(_scoreWin);
    destroy_win(_lifeWin);
    destroy_win(_gameWin);
    _scoreWin = subwin(stdscr, 3, _x / 2, 0, 0);
    _lifeWin = subwin(stdscr, 3, _x / 2, 0, _x / 2);
    _gameWin = subwin(stdscr, _y - 3, 0, 3, 0);
    wclear(stdscr);
    wclear(_scoreWin);
    wclear(_lifeWin);
    wattron(_scoreWin, COLOR_PAIR(100));
    box(_scoreWin, ACS_VLINE, ACS_HLINE);
    wattroff(_scoreWin, COLOR_PAIR(100));
    wattron(_lifeWin, COLOR_PAIR(101));
    box(_lifeWin, ACS_VLINE, ACS_HLINE);
    wattroff(_lifeWin, COLOR_PAIR(101));
}

void NCurses::printScore()
{
    int x = 0;
    std::string score = "Score = " + _score;

    x = getmaxx(_scoreWin);
    wattron(_scoreWin, COLOR_PAIR(100));
    mvwprintw(_scoreWin, 1, x / 2 - score.length() / 2, score.c_str());
    wattroff(_scoreWin, COLOR_PAIR(100));
}

void NCurses::printLife()
{
    int x = 0;
    std::string life = "Life = " + _life;

    x = getmaxx(_lifeWin);
    wattron(_lifeWin, COLOR_PAIR(101));
    mvwprintw(_lifeWin, 1, x / 2 - life.length() / 2, life.c_str());
    wattroff(_lifeWin, COLOR_PAIR(101));
}

void NCurses::printGame(const std::vector<std::vector<char>> &arr)
{
    int startX = 0;
    int startY = 0;

    getmaxyx(_gameWin, startY, startX);
    if (!arr.empty()) {
        startX = startX / 2 - arr.at(0).size() / 2;
        startY = startY / 2 - arr.size() / 2;
    }

    for (std::size_t i = 0; i < arr.size(); i++) {
        for (std::size_t j = 0; j < arr.at(i).size(); j++) {
            wattron(_gameWin, COLOR_PAIR(_color[arr.at(i).at(j)]));
            mvwprintw(_gameWin, i + startY, j + startX, "%c", arr.at(i).at(j));
            wattroff(_gameWin, COLOR_PAIR(_color[arr.at(i).at(j)]));
        }
    }
}

void NCurses::displayGame(const std::vector<std::vector<char>> &arr)
{
    getmaxyx(stdscr, _y, _x);
    if (_y != _winY || _x != _winX || _scoreWin == NULL || _lifeWin == NULL || _gameWin == NULL)
        resizeOrNewGame();
    wclear(_gameWin);
    box(_gameWin, ACS_VLINE, ACS_HLINE);
    printScore();
    printLife();
    printGame(arr);
    wnoutrefresh(stdscr);
    wnoutrefresh(_scoreWin);
    wnoutrefresh(_lifeWin);
    wnoutrefresh(_gameWin);
    doupdate();
    flushinp();
}

void NCurses::resizeOrNewMenu()
{
    destroy_win(_gamesWin);
    destroy_win(_libWin);
    destroy_win(_scoresWin);
    destroy_win(_nameWin);
    _gamesWin = subwin(stdscr, _y / 2, _x / 2, 0, 0);
    _libWin = subwin(stdscr, _y / 2, _x / 2, 0, _x / 2);
    _scoresWin = subwin(stdscr, _y / 2, _x / 2, _y / 2, 0);
    _nameWin = subwin(stdscr, _y / 2, _x / 2, _y / 2, _x / 2);
    _winX = _x;
    _winY = _y;
    wclear(stdscr);
    wclear(_gamesWin);
    wclear(_libWin);
    wclear(_scoreWin);
    wclear(_nameWin);
}

void NCurses::printGames(const Info &info)
{
    std::string win = "GAMES LIBRARIES";
    std::vector<std::string> games = info.getGameNames();
    int x = 0;
    int y = 0;

    getmaxyx(_gamesWin, y, x);
    if (info.getSide() == 0) {
        wattron(_gamesWin, COLOR_PAIR(102));
        box(_gamesWin, ACS_VLINE, ACS_HLINE);
        wattroff(_gamesWin, COLOR_PAIR(102));
    } else {
        box(_gamesWin, ACS_VLINE, ACS_HLINE);
    }
    mvwprintw(_gamesWin, 1, x / 2 - win.length() / 2, "%s", win.c_str());
    for (size_t i = 0; i < games.size(); i++) {
        if (i == info.getGameIdx()) {
            wattron(_gamesWin, COLOR_PAIR(103));
            mvwprintw(_gamesWin, y / 2 - games.size() / 2 + i * 2, x / 2 - games.at(i).size() / 2, "%s", games.at(i).c_str());
            wattroff(_gamesWin, COLOR_PAIR(103));
        } else {
            mvwprintw(_gamesWin, y / 2 - games.size() / 2 + i * 2, x / 2 - games.at(i).size() / 2, "%s", games.at(i).c_str());
        }
    }
}

void NCurses::printLib(const Info &info)
{
    std::string win = "GRAPHICAL LIBRARIES";
    std::vector<std::string> libs = info.getGraphNames();
    int x = 0;
    int y = 0;

    getmaxyx(_libWin, y, x);
    if (info.getSide() == 1) {
        wattron(_libWin, COLOR_PAIR(102));
        box(_libWin, ACS_VLINE, ACS_HLINE);
        wattroff(_libWin, COLOR_PAIR(102));
    } else {
        box(_libWin, ACS_VLINE, ACS_HLINE);
    }
    mvwprintw(_libWin, 1, x / 2 - win.length() / 2, "%s", win.c_str());
    for (size_t i = 0; i < libs.size(); i++) {
        if (i == info.getGraphIdx()) {
            wattron(_libWin, COLOR_PAIR(103));
            mvwprintw(_libWin, y / 2 - libs.size() / 2 + i * 2, x / 2 - libs.at(i).size() / 2, "%s", libs.at(i).c_str());
            wattroff(_libWin, COLOR_PAIR(103));
        } else {
            mvwprintw(_libWin, y / 2 - libs.size() / 2 + i * 2, x / 2 - libs.at(i).size() / 2, "%s", libs.at(i).c_str());
        }
    }
}

void NCurses::printScores(const Info &info)
{
    std::string win = "BEST SCORES";
    std::vector<Score> scores = info.getScoring();
    int x = 0;
    int y = 0;

    getmaxyx(_scoresWin, y, x);
    if (info.getSide() == 2) {
        wattron(_scoresWin, COLOR_PAIR(102));
        box(_scoresWin, ACS_VLINE, ACS_HLINE);
        wattroff(_scoresWin, COLOR_PAIR(102));
    } else {
        box(_scoresWin, ACS_VLINE, ACS_HLINE);
    }
    mvwprintw(_scoresWin, 1, x / 2 - win.length() / 2, "%s", win.c_str());
    for (size_t i = 0; i < 5 && i < info.getScoring().size(); i++) {
        if (info.getScoring().size() < 5) {
            mvwprintw(_scoresWin, y / 2 - info.getScoring().size() / 2 + i * 2, x / 2 - info.getScoring().at(i).getScore().size() - 1, "%s", info.getScoring().at(i).getScore().c_str());
            mvwprintw(_scoresWin, y / 2 - info.getScoring().size() / 2 + i * 2, x / 2 + 1, "%s", info.getScoring().at(i).getName().c_str());
        } else {
            mvwprintw(_scoresWin, y / 2 - 5 / 2 + i * 2, x / 2 - info.getScoring().at(i).getScore().size() - 1, "%s", info.getScoring().at(i).getScore().c_str());
            mvwprintw(_scoresWin, y / 2 - 5 / 2 + i * 2, x / 2 + 1, "%s", info.getScoring().at(i).getName().c_str());
        }
    }
}

void NCurses::printName(const Info &info)
{
    std::string win = "PLAYER NAME";
    int x = 0;
    int y = 0;

    getmaxyx(_nameWin, y, x);
    if (info.getSide() == 3) {
        wattron(_nameWin, COLOR_PAIR(102));
        box(_nameWin, ACS_VLINE, ACS_HLINE);
        wattroff(_nameWin, COLOR_PAIR(102));
    } else {
        box(_nameWin, ACS_VLINE, ACS_HLINE);
    }
    mvwprintw(_nameWin, 1, x / 2 - win.length() / 2, "%s", win.c_str());
    mvwprintw(_nameWin, y / 2, x / 2 - _name.length() / 2, _name.c_str());
}

void NCurses::displayMenu(const Info &info)
{
    getmaxyx(stdscr, _y, _x);
    _pos = info.getSide();
    if (_y != _winY || _x != _winX || _scoresWin == NULL || _gamesWin == NULL || _libWin == NULL || _nameWin == NULL)
        resizeOrNewMenu();
    printGames(info);
    printLib(info);
    printScores(info);
    printName(info);
    wnoutrefresh(_gamesWin);
    wnoutrefresh(_libWin);
    wnoutrefresh(_scoresWin);
    wnoutrefresh(_nameWin);
    doupdate();
}

void setPreview(std::vector<std::vector<char>> &arr)
{
    (void)arr;
}

void NCurses::init(const std::vector<InitTab> &arr)
{
    _initTab = arr;

    for (std::size_t i = 0; i < arr.size(); i++) {
        init_pair(i, arr.at(i).getInColor(), arr.at(i).getOutColor());
        _color.insert(std::pair<char, int>(arr.at(i).getCharacter(), i));
    }
}

void NCurses::setScore(const std::string &score)
{
    _score = score;
}

void NCurses::setLife(const std::string &life)
{
    _life = life;
}

Input NCurses::getInput()
{
    int key = getch();

    switch (key)
    {
        case KEY_UP:
            return UP;
        case KEY_DOWN:
            return DOWN;
        case KEY_RIGHT:
            return RIGHT;
        case KEY_LEFT:
            return LEFT;
        case 27:
            return EXIT;
        case 97:
            if (_pos == 3)
                _name.push_back(key);
            return PREV_GAME;
        case 101:
            if (_pos == 3)
                _name.push_back(key);
            return NEXT_GAME;
        case '\n':
            return ENTER;
        case 119:
            if (_pos == 3)
                _name.push_back(key);
            return PREV_GRAPH;
        case 99:
            if (_pos == 3)
                _name.push_back(key);
            return NEXT_GRAPH;
        case ERR:
            return NONE;
        default:
            if (_pos == 3)
                _name.push_back(key);
            return NONE;
    }
}

std::string NCurses::getName()
{
    return _name;
}

extern "C"
{
    std::shared_ptr<IGraphics> createInterface()
    {
        return std::make_shared<NCurses>();
    }
}