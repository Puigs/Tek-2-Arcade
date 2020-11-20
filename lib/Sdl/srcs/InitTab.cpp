/*
** EPITECH PROJECT, 2020
** Arcade
** File description:
** initTab.cpp
*/

#include "../includes/InitTab.hpp"

InitTab::InitTab(char c, int iC, int oC, const std::string &str)
{
    _c = c;
    _inColor = iC;
    _outColor = oC;
    _path = str;
}

InitTab::~InitTab()
{
}

char
InitTab::getCharacter() const
{
    return this->_c;
}

int
InitTab::getInColor() const
{
    return this->_inColor;
}

int
InitTab::getOutColor() const
{
    return this->_outColor;
}

const std::string &
InitTab::getPath() const
{
    return this->_path;
}
