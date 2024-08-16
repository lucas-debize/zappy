/*
** EPITECH PROJECT, 2023
** 2eme Année
** File description:
** error.hpp
*/

#ifndef ERROR_HPP
    #define ERROR_HPP

    #include <SFML/Network.hpp>
    #include <unistd.h>
    #include <cstdlib>
    #include <cstring>
    #include "config.hpp"
    #include "helpers.hpp"

int error_handling(int argc, char **argv, Config &config);
int parse_args(int argc, char **argv, Config &config);

#endif // ERROR_HPP
