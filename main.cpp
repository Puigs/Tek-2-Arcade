/*
** EPITECH PROJECT, 2020
** main.cpp
** File description:
** main
*/

#include "core/includes/Core.hpp"
#include <iostream>

void printHelp(void)
{
    std::cout << "HOW TO USE" << std::endl;
    std::cout << "    ./arcade ./library/path\n" << std::endl;
}

int main(int ac, char **av)
{
    if (ac != 2) {
        printHelp();
        return 84;
    } else {
        Core *core = new Core(av[1]);
        core->MainLoop();
        delete core;
        return 0;
    }
}