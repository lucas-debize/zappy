/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-dorian.senecot
** File description:
** player_rendering.cpp
*/

#include "player.hpp"
#include "rendering.hpp"

void Player::draw(sf::RenderWindow &window) const {
    if (!isDead) {
        window.draw(sprite);
        if (!isDying) {
            window.draw(directionSprite);
        }
        if (isBroadcasting) {
            window.draw(broadcastText);
            window.draw(broadcastCircle);
        }
        if (displayInventory) {
            window.draw(inventoryText);
        }
    }
}
