/*
** EPITECH PROJECT, 2023
** 2eme Année
** File description:
** helpers.cpp
*/

#include "../include/helpers.hpp"

std::vector<std::string> split(const std::string &str, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(str);
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

bool isNumber(const std::string& str)
{
    for (char const &c : str) {
        if (std::isdigit(c) == 0)
            return false;
    }
    return true;
}

bool isValidPort(int port)
{
    return port > 0 && port <= 65535;
}

int helpcmd(int ret)
{
    std::cout << "USAGE: ./zappy_gui\n";
    std::cout << "      -help       display this help\n";
    std::cout << "      -p <port>       is the port number\n";
    std::cout << "      -h <name>       is the name of the machine; localhost by default\n";
    return ret;
}
