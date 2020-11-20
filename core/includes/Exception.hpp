/*
** EPITECH PROJECT, 2020
** Exception.hpp
** File description:
** Exception
*/

#ifndef EXCEPTION_HPP_
#define EXCEPTION_HPP_

#include <exception>
#include <string>

class Exception : public std::exception {
    public:
        Exception(std::string const &message);
        ~Exception();
        const char *what() const noexcept override;
    protected:
    private:
        std::string _message;
};

#endif /* !EXCEPTION_HPP_ */