/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-dorian.senecot
** File description:
** player_position.cpp
*/

#include "player.hpp"
#include "rendering.hpp"

void Player::setPosition(float x, float y) {
    this->x = x;
    this->y = y;
    sprite.setPosition((offsetX + (x - 1) * cellSize) + cellSize, (offsetY + (y - 1) * cellSize) + cellSize);
}

void Player::setDirection(const std::string &direction) {
    this->direction = direction;
    float rotation = 0.f;
    if (direction == "EAST") {
        rotation = 0.f;
    } else if (direction == "NORTH") {
        rotation = 270.f;
    } else if (direction == "WEST") {
        rotation = 180.f;
    } else if (direction == "SOUTH") {
        rotation = 90.f;
    }
    directionSprite.setRotation(rotation);
    updateDirectionSpritePosition();
}

void Player::updateDirectionSpritePosition() {
    float xOffset = 0.0f;
    float yOffset = 0.0f;

    if (direction == "EAST") {
        directionSprite.setPosition((offsetX + (x - 1) * cellSize) + cellSize * 1.8, (offsetY + (y - 1) * cellSize) + cellSize * 1.5);
    } else if (direction == "NORTH") {
        directionSprite.setPosition((offsetX + (x - 1) * cellSize) + cellSize * 1.5, (offsetY + (y - 1) * cellSize) + cellSize * 1.2);
    } else if (direction == "WEST") {
        directionSprite.setPosition((offsetX + (x - 1) * cellSize) + cellSize * 1.2, (offsetY + (y - 1) * cellSize) + cellSize * 1.5);
    } else if (direction == "SOUTH") {
        directionSprite.setPosition((offsetX + (x - 1) * cellSize) + cellSize * 1.5, (offsetY + (y - 1) * cellSize) + cellSize * 1.8);
    }
}
