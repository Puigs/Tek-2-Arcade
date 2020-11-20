/*
** EPITECH PROJECT, 2020
** Exception
** File description:
** Exception
*/

#include "../includes/Exception.hpp"

Exception::Exception(std::string const &message)
{
    _message = message;
}

Exception::~Exception()
{
}

const char *Exception::what() const noexcept
{
    return _message.c_str();
}