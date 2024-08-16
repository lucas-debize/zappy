/*
** EPITECH PROJECT, 2023
** 2eme Année
** File description:
** player_actions.cpp
*/

#include "../../include/player_handling.hpp"

void handlePlayerLevel(const std::vector<std::string> &tokens) {
    if (tokens.size() < 3) {
        std::cerr << "Error: Invalid player level data received." << std::endl;
        return;
    }

    int playerId = std::stoi(tokens[1]);
    int level = std::stoi(tokens[2]);

    std::lock_guard<std::mutex> lock(playerMutex);

    auto it = std::find_if(players.begin(), players.end(), [playerId](const Player &player) {
        return player.getId() == playerId;
    });

    if (it != players.end()) {
        it->setLevel(level);
    } else {
        std::cerr << "Error: Player with ID " << playerId << " not found." << std::endl;
    }
}

void handlePlayerBroadcast(const std::vector<std::string> &tokens) {
    if (tokens.size() < 3) {
        std::cerr << "Error: Invalid player broadcast data received." << std::endl;
        return;
    }

    int playerId = std::stoi(tokens[1]);
    std::string message = tokens[2];

    std::lock_guard<std::mutex> lock(playerMutex);

    auto it = std::find_if(players.begin(), players.end(), [playerId](const Player &player) {
        return player.getId() == playerId;
    });

    if (it != players.end()) {
        it->broadcast(message);
        songsPlayer.playBroadcastSound();
    } else {
        std::cerr << "Error: Player with ID " << playerId << " not found." << std::endl;
    }
}

void handleIncantationStart(const std::vector<std::string> &tokens) {
    if (tokens.size() < 4) {
        std::cerr << "Error: Invalid incantation start data received." << std::endl;
        return;
    }

    int x = std::stoi(tokens[1]);
    int y = std::stoi(tokens[2]);
    int level = std::stoi(tokens[3]);

    std::vector<int> playerIds;
    for (size_t i = 4; i < tokens.size(); ++i) {
        playerIds.push_back(std::stoi(tokens[i]));
    }
    for (int playerId : playerIds) {
        std::cout << "#" << playerId << " ";
    }
    std::cout << std::endl;

    std::lock_guard<std::mutex> lock(playerMutex);  
    for (int playerId : playerIds) {
        auto it = std::find_if(players.begin(), players.end(), [playerId](const Player &player) {
            return player.getId() == playerId;
        });

        if (it != players.end()) {
            it->setLevel(level);
            songsPlayer.playLevelUpSound();
            it->startLevelUpAnimation();
        }
    }
}

void handlePlayerDeath(const std::vector<std::string> &tokens) {
    if (tokens.size() < 2) {
        std::cerr << "Error: Invalid player death data received." << std::endl;
        return;
    }

    int playerId = std::stoi(tokens[1]);

    std::lock_guard<std::mutex> lock(playerMutex);

    auto it = std::find_if(players.begin(), players.end(), [playerId](const Player &player) {
        return player.getId() == playerId;
    });

    if (it != players.end()) {
        it->startDeathAnimation();
        songsPlayer.playDeathSound();
        ++totalDeaths;
    } else {
        std::cerr << "Error: Player with ID " << playerId << " not found." << std::endl;
    }
}

void handlePlayerExpulsion(const std::vector<std::string> &tokens) {
    if (tokens.size() < 2) {
        std::cerr << "Error: Invalid player expulsion data received." << std::endl;
        return;
    }

    int playerId = std::stoi(tokens[1]);

    std::lock_guard<std::mutex> lock(playerMutex);

    auto it = std::find_if(players.begin(), players.end(), [playerId](const Player &player) {
        return player.getId() == playerId;
    });

    if (it != players.end()) {
        songsPlayer.playKickSound();
    } else {
        std::cerr << "Error: Player with ID " << playerId << " not found." << std::endl;
    }
}