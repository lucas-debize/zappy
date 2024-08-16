/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-dorian.senecot
** File description:
** rendering.cpp
*/

#include "team.hpp"

std::map<std::string, Team> teams;

void loadTeamSprites() {
    std::vector<std::string> spritePaths = {
        "ressource/sprite/Factions/Knights/Troops/Warrior/Blue/Warrior_Blue.png",
        "ressource/sprite/Factions/Knights/Troops/Warrior/Red/Warrior_Red.png",
        "ressource/sprite/Factions/Knights/Troops/Warrior/Purple/Warrior_Purple.png",
        "ressource/sprite/Factions/Knights/Troops/Warrior/Yellow/Warrior_Yellow.png",
        "ressource/sprite/Factions/Knights/Troops/Archer/Blue/Archer_Blue.png",
        "ressource/sprite/Factions/Knights/Troops/Archer/Red/Archer_Red.png",
        "ressource/sprite/Factions/Knights/Troops/Archer/Purple/Archer_Purple.png",
        "ressource/sprite/Factions/Knights/Troops/Archer/Yellow/Archer_Yellow.png",
        "ressource/sprite/Factions/Knights/Troops/Pawn/Red/Pawn_Red.png",
        "ressource/sprite/Factions/Knights/Troops/Pawn/Blue/Pawn_Blue.png",
        "ressource/sprite/Factions/Knights/Troops/Pawn/Purple/Pawn_Purple.png",
        "ressource/sprite/Factions/Knights/Troops/Pawn/Yellow/Pawn_Yellow.png"
    };

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(spritePaths.begin(), spritePaths.end(), g);
    int i = 0;
    for (auto& team : teams) {
        if (i >= spritePaths.size()) {
            std::cerr << "Error: Not enough sprite paths for all teams" << std::endl;
            return;
        }
        team.second.texture = std::make_shared<sf::Texture>();
        if (!team.second.texture->loadFromFile(spritePaths[i])) {
            std::cerr << "Error: Could not load sprite for team " << team.first << std::endl;
        }
        i++;
    }
}

void handleTeamNames(const std::vector<std::string>& tokens) {
    if (tokens.empty()) return;

    for (const auto& token : tokens) {
        teams[token] = Team{token, nullptr};
    }

    loadTeamSprites();
}
