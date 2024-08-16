/*
** EPITECH PROJECT, 2023
** 2eme Année
** File description:
** player_inventory.cpp
*/

#include "../../include/player_handling.hpp"

void handlePlayerInventory(const std::vector<std::string> &tokens) {
    if (tokens.size() < 11) {
        std::cerr << "Error: Invalid player inventory data received." << std::endl;
        return;
    }

    int playerId = std::stoi(tokens[1]);
    int x = std::stoi(tokens[2]);
    int y = std::stoi(tokens[3]);
    std::array<int, 7> inventory;
    for (int i = 0; i < 7; ++i) {
        inventory[i] = std::stoi(tokens[4 + i]);
    }

    std::lock_guard<std::mutex> lock(playerMutex);

    auto it = std::find_if(players.begin(), players.end(), [playerId](const Player &player) {
        return player.getId() == playerId;
    });

    if (it != players.end()) {
        it->setInventory(inventory);
    } else {
        std::cerr << "Error: Player with ID " << playerId << " not found." << std::endl;
    }
}

void handleResourceDrop(const std::vector<std::string> &tokens) {
    if (tokens.size() < 3) {
        std::cerr << "Error: Invalid resource drop data received." << std::endl;
        return;
    }

    int playerId = std::stoi(tokens[1]);
    int resourceId = std::stoi(tokens[2]);

    std::lock_guard<std::mutex> lock(playerMutex);

    auto it = std::find_if(players.begin(), players.end(), [playerId](const Player &player) {
        return player.getId() == playerId;
    });

    if (it != players.end()) {
        songsPlayer.playDropSound();
    } else {
        std::cerr << "Error: Player with ID " << playerId << " not found." << std::endl;
    }
}

void handleResourceCollect(const std::vector<std::string> &tokens) {
    if (tokens.size() < 3) {
        std::cerr << "Error: Invalid resource collect data received." << std::endl;
        return;
    }

    int playerId = std::stoi(tokens[1]);
    int resourceId = std::stoi(tokens[2]);

    std::lock_guard<std::mutex> lock(playerMutex);

    auto it = std::find_if(players.begin(), players.end(), [playerId](const Player &player) {
        return player.getId() == playerId;
    });

    if (it != players.end()) {
        songsPlayer.playPickSound();
    } else {
        std::cerr << "Error: Player with ID " << playerId << " not found." << std::endl;
    }
}
