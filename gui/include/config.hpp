/*
** EPITECH PROJECT, 2023
** 2eme Année
** File description:
** config.hpp
*/

#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <string>

struct Config {
    int port;
    std::string host = "localhost";
};

#endif // CONFIG_HPP
