/*
** EPITECH PROJECT, 2023
** 2eme Année
** File description:
** tile.hpp
*/

#ifndef TILE_HPP
#define TILE_HPP

#include <vector>
#include <string>
#include <array>
#include <map>
#include <mutex>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <algorithm>
#include <functional>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

void handleTileContent(const std::vector<std::string>& tokens);
void drawMap(sf::RenderWindow &window, int mapWidth, int mapHeight);
void createMap(sf::RenderWindow &window, int width, int height);
void updateAnimations(float deltaTime);

#endif // TILE_HPP
