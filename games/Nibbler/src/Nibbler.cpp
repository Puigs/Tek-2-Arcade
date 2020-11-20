/*
** EPITECH PROJECT, 2020
** Nibbler.cpp
** File description:
** Nibbler
*/

#include "../include/Nibbler.hpp"

Arcad::Nibbler::Nibbler()
{
     std::ifstream file;
    std::string tmp;
    std::vector<char> tmp2;

    file.open("games/Nibbler/assets/map2.txt");
    if (file.is_open()) {
        for (size_t i = 0; std::getline(file, tmp); i++) {
            tmp.erase(std::remove(tmp.begin(), tmp.end(), '\n'), tmp.end());
            _array.push_back(tmp2);
            std::copy(tmp.begin(), tmp.end(), std::back_inserter(_array[i]));
        }
    } else 
        std::cout << "File don't open" << std::endl;

    _pos.push_back(0);
    _pos.push_back(0);
    _ppos.push_back(0);
    _ppos.push_back(0);
    for (int i = 0; i < 3; i++)
        _cpos.push_back(_pos);
    _cpos[0][0] = 17;
    _cpos[0][1] = 1;
    _cpos[1][0] = 17;
    _cpos[1][1] = 2;
    _cpos[2][0] = 17;
    _cpos[2][1] = 3;
    _npos.push_back(0);
    _npos.push_back(0);
    find_head();

    InitTab apple('.', 7, 0, "games/Nibbler/assets/apple.png");

    InitTab head('^', 7, 0, "games/Nibbler/assets/head.png");
    InitTab head_right('>', 7, 0, "games/Nibbler/assets/head2.png");
    InitTab head_bottom('v', 7, 0, "games/Nibbler/assets/head3.png");
    InitTab head_left('<', 7, 0, "games/Nibbler/assets/head4.png");
    
    InitTab body('o', 7, 0, "games/Nibbler/assets/tail.png");

    InitTab wall('#', 7, 0, "games/Nibbler/assets/wall.png");
    _arr.push_back(apple);
    _arr.push_back(head);
    _arr.push_back(head_right);
    _arr.push_back(head_left);
    _arr.push_back(head_bottom);
    _arr.push_back(body);
    _arr.push_back(wall);
}

Arcad::Nibbler::~Nibbler()
{
}

const std::vector<InitTab> &Arcad::Nibbler::getInit() const
{
    return _arr;
}

int check_move_back(Input key, Input _prec)
{
    if (key == KEY_UP && _prec == KEY_DOWN)
        return 1;
    else if (key == KEY_DOWN && _prec == KEY_UP)
        return 1;
    else if (key == KEY_LEFT && _prec == KEY_RIGHT)
        return 1;
    else if (key == KEY_RIGHT && _prec == KEY_LEFT)
        return 1;
    return 0;
}

void Arcad::Nibbler::find_head()
{
    for (; _pos[0] < _array.size(); _pos[0]++) {
        for (; _pos[1] < _array[_pos[0]].size(); _pos[1]++) {
            if (_array[_pos[0]][_pos[1]] == '^' || _array[_pos[0]][_pos[1]] == '>' \
            || _array[_pos[0]][_pos[1]] == '<' || _array[_pos[0]][_pos[1]] == 'v')
                return;
        }
        _pos[1] = 0;
    }
}

int Arcad::Nibbler::check_if_block()
{
    if (_array[_pos[0] - 1][_pos[1]] == ' ' || _array[_pos[0] - 1][_pos[1]] == '.')
        return 0;
    else if (_array[_pos[0] + 1][_pos[1]] == ' ' || _array[_pos[0] + 1][_pos[1]] == '.')
        return 0;
    else if (_array[_pos[0]][_pos[1] - 1] == ' ' || _array[_pos[0]][_pos[1] - 1] == '.')
        return 0;
    else if (_array[_pos[0]][_pos[1] + 1] == ' ' || _array[_pos[0]][_pos[1] + 1] == '.')
        return 0;
    return 1;
}

void Arcad::Nibbler::make_move()
{
    _ppos[0] = _pos[0];
    _ppos[1] = _pos[1];
    _array[_pos[0]][_pos[1]] = 'o';
    _array[_npos[0]][_npos[1]] = _dir;
    _cpos.push_back(_pos);
    _array[_cpos[0][0]][_cpos[0][1]] = ' ';
    _cpos.erase(_cpos.begin());
    _pos[0] = _npos[0];
    _pos[1] = _npos[1];
}

void Arcad::Nibbler::check_if_win()
{
    for (size_t y = 0; y < _array.size(); y++) {
        for (size_t x = 0; x < _array[y].size(); x++) {
            if (_array[y][x] == '.') {
                this->win = false;
                return;
            }
        }
    }
    this->win = true;
}

void Arcad::Nibbler::make_eat()
{
    _ppos[0] = _pos[0];
    _ppos[1] = _pos[1];
    _array[_pos[0]][_pos[1]] = 'o';
    _array[_npos[0]][_npos[1]] = _dir;
    _cpos.push_back(_pos);
    _pos[0] = _npos[0];
    _pos[1] = _npos[1];
    check_if_win();
}

void Arcad::Nibbler::check_npos()
{
    int check = 0;
    if (_array[_npos[0]][_npos[1]] == '#') {
        check = check_if_block();
        if (check == 1) {
            _life = "0";
            _key = NONE;
            return;
        }
    } else if (_array[_npos[0]][_npos[1]] == '.') {
        int s = std::stoi(_score);
        s += 100;
        _score = std::to_string(s);
        make_eat();
    } else if (_array[_npos[0]][_npos[1]] == ' ') {
        make_move();
    } else if (_array[_npos[0]][_npos[1]] == 'o') {
        _life = "0";
    }
}

void Arcad::Nibbler::find_direction()
{
    if (_array[_pos[0]][_pos[1]] == '^') {
        _dir = '^';
        _npos[0] = _pos[0] - 1;
        _npos[1] = _pos[1];
    } else if (_array[_pos[0]][_pos[1]] == '<') {
        _dir = '<';
        _npos[0] = _pos[0];
        _npos[1] = _pos[1] - 1;
    } else if (_array[_pos[0]][_pos[1]] == 'v') {
        _dir = 'v';
        _npos[0] = _pos[0] + 1;
        _npos[1] = _pos[1];
    } else if (_array[_pos[0]][_pos[1]] == '>') {
        _dir = '>';
        _npos[0] = _pos[0];
        _npos[1] = _pos[1] + 1;
    }
}

int Arcad::Nibbler::check_dir()
{
    if (_ppos[0] == _npos[0] && _ppos[1] == _npos[1])
        return 1;
    return 0;
}

void Arcad::Nibbler::init_move()
{
    if (_key == KEY_UP) {
        _dir = '^';
        _npos[0] = _pos[0] - 1;
        _npos[1] = _pos[1];
    } else if (_key == KEY_LEFT) {
        _dir = '<';
        _npos[0] = _pos[0];
        _npos[1] = _pos[1] - 1;
    } else if (_key == KEY_DOWN) {
        _dir = 'v';
        _npos[0] = _pos[0] + 1;
        _npos[1] = _pos[1];
    } else if (_key == KEY_RIGHT) {
        _dir = '>';
        _npos[0] = _pos[0];
        _npos[1] = _pos[1] + 1;
    } else if (_key == NONE) {
        find_direction();
    }
    if (check_dir() == 1)
        return;
    check_npos();
    if (_life == "0")
        return;
}

const std::vector<std::vector<char>> &Arcad::Nibbler::simulate(Input key)
{
    if (key != NONE && (check_move_back(key, _prec_input) != 0 || key == _prec_input)) {
        key = NONE;
    }
    _key = key;
    init_move();

    _prec_input = key;
    if (this->win == true)
        _life = "2";
    return _array;
}

const std::string &Arcad::Nibbler::getScore() const 
{
    return _score;
}

const std::string &Arcad::Nibbler::getLife() const
{
    return _life;
}

extern "C"
{
    std::shared_ptr<IGames>
    createInterface(void)
    {
        return std::make_shared<Arcad::Nibbler>();
    }
}