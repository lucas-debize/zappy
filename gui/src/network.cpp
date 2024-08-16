/*
** EPITECH PROJECT, 2023
** 2eme Année
** File description:
** network.cpp
*/

#include "../include/network.hpp"

int connectToServer(Config *config, sf::TcpSocket &socket)
{
    if (socket.connect(config->host, config->port) != sf::Socket::Done) {
        std::cerr << "Error connecting to the server" << std::endl;
        return 84;
    }
    return 0;
}

void receiveServerData(sf::TcpSocket &socket) {
    char buffer[1024];
    std::size_t received;
    while (running) {
        if (socket.receive(buffer, sizeof(buffer), received) == sf::Socket::Done) {
            std::string serverData(buffer, received);
            std::istringstream iss(serverData);
            std::string line;
            while (std::getline(iss, line)) {
                commandQueue.push(line);
            }
        }
    }
}

int receiveData(sf::TcpSocket &socket, char *data, std::size_t &received)
{
    if (socket.receive(data, sizeof(data), received) != sf::Socket::Done) {
        std::cerr << "Error receiving data" << std::endl;
        return 84;
    }
    return 0;
}

int sendData(sf::TcpSocket &socket, const std::string &command)
{
    if (socket.send(command.c_str(), command.size()) != sf::Socket::Done) {
        std::cerr << "Error sending command" << std::endl;
        return 84;
    }
    return 0;
}
