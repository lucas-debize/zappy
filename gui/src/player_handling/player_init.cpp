/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-dorian.senecot
** File description:
** player.cpp
*/

#include "player.hpp"
#include "rendering.hpp"

Player::Player(int id, int x, int y, float cellSize, float offsetX, float offsetY, const std::string &direction, int level, const std::string &teamName)
    : id(id), x(x), y(y), cellSize(cellSize), offsetX(offsetX), offsetY(offsetY), direction(direction), level(level), teamName(teamName), inventory({0, 0, 0, 0, 0, 0, 0}), currentFrame(0), texture(std::make_shared<sf::Texture>()), directionTexture(std::make_shared<sf::Texture>()) {
    loadSpritesheet();
    loadDirectionSpritesheet();
    loadDeathSpritesheet();
    loadLevelUpSpritesheet();
    setPosition(x, y);
    setDirection(direction);
    displayInventory = false;
    inventoryText.setFont(font);
    inventoryText.setCharacterSize(35);
    inventoryText.setFillColor(sf::Color::White);
    inventoryText.setOutlineColor(sf::Color::Black);
    inventoryText.setOutlineThickness(1.0f);
}

void Player::setLevel(int level) {
    this->level = level;
}

int Player::getLevel() const {
    return level;
}

int Player::getId() const {
    return id;
}

const std::string Player::getTeam() const {
    return teamName;
}

const std::array<int, 7>& Player::getInventory() const {
    return inventory;
}

void Player::setInventory(const std::array<int, 7> &inventory) {
    this->inventory = inventory;

    static const std::vector<std::string> itemNames = {
        "food", "linemate", "deraumere", "sibur", "mendiane", "phiras", "thystame"
    };

    std::ostringstream oss;
    oss << "Player " << teamName << "/" << id << " Inventory:\n";
    for (size_t i = 0; i < inventory.size(); ++i) {
        oss << "  " << itemNames[i] << ": " << inventory[i] << "\n";
    }
    oss << "\n" << "Level: " << level;
    inventoryText.setString(oss.str());
    inventoryText.setPosition(mapHeight, mapWidth);
}

void Player::setCellSize(float cellSize) {
    this->cellSize = cellSize;
    sprite.setScale(cellSize / 192, cellSize / 192);
    directionSprite.setScale(cellSize / 192, cellSize / 192);
    setPosition(x, y);
}

void Player::setOffsets(float offsetX, float offsetY) {
    this->offsetX = offsetX;
    this->offsetY = offsetY;
    setPosition(x, y);
}

void Player::setTeamSprite(std::shared_ptr<sf::Texture> teamTexture) {
    texture = teamTexture;
    sprite.setTexture(*texture);
}

bool Player::containsPoint(sf::Vector2f point) const {
    return sprite.getGlobalBounds().contains(point);
}
