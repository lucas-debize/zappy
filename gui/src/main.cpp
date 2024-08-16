/*
** EPITECH PROJECT, 2024
** Epitech2
** File description:
** main
*/

#include "main.hpp"

int main(int argc, char **argv)
{
    Config config;
    if (argc == 2) {
        if (std::string(argv[1]) == "-help")
            return helpcmd(0);
    }
    if (error_handling(argc, argv, config) == 84)
        return 84;
    runGameClient(&config);
    return 0;
}
