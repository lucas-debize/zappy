/*
** EPITECH PROJECT, 2023
** 2eme Année
** File description:
** helpers.hpp
*/

#ifndef HELPERS_HPP
    #define HELPERS_HPP

    #include <string>
    #include <vector>
    #include <sstream>
    #include <iostream>
    #include <cctype>

std::vector<std::string> split(const std::string &str, char delim);
bool isNumber(const std::string& str);
bool isValidPort(int port);
int helpcmd(int ret);

#endif // HELPERS_HPP
