/*
** EPITECH PROJECT, 2023
** 2eme Année
** File description:
** team.hpp
*/

#ifndef TEAM_HPP
#define TEAM_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <map>
#include <memory>
#include <iostream>
#include <random>

struct Team {
    std::string name;
    std::shared_ptr<sf::Texture> texture;
};

extern std::map<std::string, Team> teams;

void loadTeamSprites();
void handleTeamNames(const std::vector<std::string>& tokens);

#endif // TEAM_HPP
