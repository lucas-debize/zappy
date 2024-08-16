/*
** EPITECH PROJECT, 2023
** 2eme Année
** File description:
** network.hpp
*/

#ifndef NETWORK_HPP
    #define NETWORK_HPP

    #include <SFML/Network.hpp>
    #include <unistd.h>
    #include <cstdlib>
    #include <cstring>
    #include "config.hpp"
    #include "helpers.hpp"
    #include "rendering.hpp"

int connectToServer(Config *config, sf::TcpSocket &socket);
int receiveData(sf::TcpSocket &socket, char *data, std::size_t &received);
int sendData(sf::TcpSocket &socket, const std::string &command);
void receiveServerData(sf::TcpSocket &socket);

#endif // NETWORK_HPP
