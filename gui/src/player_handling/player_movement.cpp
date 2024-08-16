/*
** EPITECH PROJECT, 2023
** 2eme Année
** File description:
** player_movement.cpp
*/

#include "../../include/player_handling.hpp"

std::string getDirection(int dir) {
    switch (dir) {
        case 1: return "NORTH";
        case 2: return "EAST";
        case 3: return "SOUTH";
        case 4: return "WEST";
        default: return "UNKNOWN";
    }
}

void handlePlayerPosition(const std::vector<std::string> &tokens) {
    if (tokens.size() < 5) {
        std::cerr << "Error: Invalid player position data received." << std::endl;
        return;
    }

    int playerId = std::stoi(tokens[1]);
    int x = std::stoi(tokens[2]);
    int y = std::stoi(tokens[3]);
    int dir = std::stoi(tokens[4]);

    std::string direction = getDirection(dir);

    std::lock_guard<std::mutex> lock(playerMutex);

    auto it = std::find_if(players.begin(), players.end(), [playerId](const Player &player) {
        return player.getId() == playerId;
    });

    if (it != players.end()) {
        it->setPosition(x, y);
        it->setDirection(direction);
        songsPlayer.playMoveSound();
    } else {
        players.emplace_back(playerId, x, y, globalCellSize, globalOffsetX, globalOffsetY, direction, 1, "");
    }
}

void handlePlayerCreate(const std::vector<std::string>& tokens) {
    if (tokens.size() < 7) {
        std::cerr << "Error: Invalid player creation data received." << std::endl;
        return;
    }

    int playerId = std::stoi(tokens[1]);
    int x = std::stoi(tokens[2]);
    int y = std::stoi(tokens[3]);
    int dir = std::stoi(tokens[4]);
    int level = std::stoi(tokens[5]);
    std::string teamName = tokens[6];

    std::string direction = getDirection(dir);

    std::lock_guard<std::mutex> lock(playerMutex);

    auto it = std::find_if(players.begin(), players.end(), [playerId](const Player& player) {
        return player.getId() == playerId;
    });

    if (it != players.end()) {
        it->setPosition(x, y);
        it->setDirection(direction);
        it->setLevel(level);
    } else {
        Player newPlayer(playerId, x, y, globalCellSize, globalOffsetX, globalOffsetY, direction, level, teamName);

        auto teamIt = teams.find(teamName);
        if (teamIt != teams.end()) {
            newPlayer.setTeamSprite(teamIt->second.texture);
        } else {
            std::cerr << "Error: Team not found for player creation: " << teamName << std::endl;
        }

        players.emplace_back(std::move(newPlayer));
    }
}
