/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-dorian.senecot
** File description:
** player_interactions.cpp
*/

#include "player.hpp"
#include "rendering.hpp"

void Player::broadcast(const std::string &message) {
    isBroadcasting = true;
    broadcastEffectRadius = 0.0f;
    broadcastCircle.setRadius(broadcastEffectRadius);
    broadcastCircle.setOrigin(broadcastEffectRadius, broadcastEffectRadius);
    broadcastCircle.setPosition(sprite.getPosition() + sf::Vector2f(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2));
    broadcastCircle.setFillColor(sf::Color::Transparent);
    broadcastCircle.setOutlineThickness(5.0f);
    broadcastCircle.setOutlineColor(sf::Color::Green);
    broadcastText.setFont(font);
    broadcastText.setCharacterSize(
        static_cast<unsigned int>(cellSize / 2.5f)
    );
    broadcastText.setFillColor(sf::Color::White);
    broadcastText.setOutlineColor(sf::Color::Black);
    broadcastText.setOutlineThickness(1.0f);
    broadcastText.setStyle(sf::Text::Bold);
    broadcastText.setString("Player " + std::to_string(id) + ": " + message);
}

void Player::updateBroadcastEffect(float deltaTime) {
    if (isBroadcasting) {
        broadcastEffectRadius += broadcastSpeed * deltaTime;
        broadcastCircle.setRadius(broadcastEffectRadius);
        broadcastCircle.setOrigin(broadcastEffectRadius, broadcastEffectRadius);
        broadcastCircle.setPosition(sprite.getPosition() + sf::Vector2f(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2));
        broadcastText.setCharacterSize(
            static_cast<unsigned int>(cellSize / 2.5f)
        );
        broadcastText.setPosition(broadcastCircle.getPosition() - sf::Vector2f(broadcastText.getGlobalBounds().width / 2, broadcastText.getGlobalBounds().height / 2 + cellSize / 1.9f));
        if (broadcastEffectRadius > std::max(1900.0f, 1000.0f)) {
            isBroadcasting = false;
        }
    }
}

void Player::setInventoryVisible(bool visible) {
    displayInventory = visible;
}

bool Player::isInventoryVisible() const {
    return displayInventory;
}
