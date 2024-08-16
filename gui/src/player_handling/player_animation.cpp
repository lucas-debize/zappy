/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-dorian.senecot
** File description:
** player_animation.cpp
*/

#include "player.hpp"
#include "rendering.hpp"

void Player::loadDeathSpritesheet() {
    if (!deathTexture.loadFromFile("ressource/sprite/Factions/Knights/Troops/Dead/Dead.png")) {
        std::cerr << "Error: Could not load death texture." << std::endl;
    } else {
        for (int i = 0; i < 7; ++i) {
            deathFrames.push_back(sf::IntRect(i * 128, 0, 128, 128));
        }
        for (int i = 0; i < 8; ++i) {
            deathFrames.push_back(sf::IntRect(i * 128, 128, 128, 128));
        }
    }
}

void Player::loadSpritesheet() {
    for (int i = 0; i < 6; ++i) {
        frames.push_back(sf::IntRect(i * 192, 0, 192, 192));
    }
    sprite.setTextureRect(frames[0]);
    sprite.setScale(cellSize / 192, cellSize / 192);
}

void Player::loadDirectionSpritesheet() {
    if (!directionTexture->loadFromFile("ressource/sprite/direction.png")) {
        std::cerr << "Error: Could not load direction spritesheet." << std::endl;
    }
    directionSprite.setTexture(*directionTexture);
    
    float directionScaleFactor = 0.1f;
    directionSprite.setScale((cellSize / 192) * directionScaleFactor, (cellSize / 192) * directionScaleFactor);
    directionSprite.setOrigin(directionTexture->getSize().x / 2, directionTexture->getSize().y / 2);
}

void Player::loadLevelUpSpritesheet() {
    if (!levelUpTexture.loadFromFile("ressource/sprite/Effects/Explosion/Explosions.png")) {
        std::cerr << "Error: Could not load level up texture." << std::endl;
    } else {
        for (int i = 0; i < 10; ++i) {
            levelUpFrames.push_back(sf::IntRect(i * 192, 0, 192, 192));
        }
    }
}

void Player::update(float deltaTime) {
    if (isDying) {
        deathAnimationTimer += deltaTime;
        const float deathFrameTime = 0.1f;

        if (deathAnimationTimer >= deathFrameTime) {
            deathAnimationTimer -= deathFrameTime;
            currentDeathFrame++;

            if (currentDeathFrame < deathFrames.size()) {
                sprite.setTextureRect(deathFrames[currentDeathFrame]);
            } else {
                isDead = true;
                isDying = false;
            }
        }
    } else if (isLevelingUp) {
        levelUpAnimationTimer += deltaTime;
        const float levelUpFrameTime = 0.1f;

        if (levelUpAnimationTimer >= levelUpFrameTime) {
            levelUpAnimationTimer -= levelUpFrameTime;
            currentLevelUpFrame++;

            if (currentLevelUpFrame < levelUpFrames.size()) {
                sprite.setTextureRect(levelUpFrames[currentLevelUpFrame]);
            } else {
                isLevelingUp = false;
                sprite.setTexture(*texture);
                sprite.setTextureRect(frames[currentFrame]);
                sprite.setScale(cellSize / 192, cellSize / 192);
            }
        }
    } else {
        animationTimer += deltaTime;
        const float newTimePerFrame = 0.1f;

        if (animationTimer >= newTimePerFrame) {
            animationTimer -= newTimePerFrame;
            currentFrame = (currentFrame + 1) % frames.size();
            sprite.setTextureRect(frames[currentFrame]);
        } else {
            animationTimer += (newTimePerFrame - timePerFrame);
        }

        timePerFrame = newTimePerFrame;
        scaleAnimationTimer += deltaTime;
        float scaleFactor = 0.1f + 0.02f * std::sin(scaleAnimationTimer * 2.0f);
        directionSprite.setScale((cellSize / 192) * scaleFactor, (cellSize / 192) * scaleFactor);
        updateDirectionSpritePosition();
    }
}

void Player::startDeathAnimation() {
    if (!isDying && !isDead) {
        isDying = true;
        currentDeathFrame = 0;
        deathAnimationTimer = 0.0f;
        sprite.setTexture(deathTexture);
        sprite.setTextureRect(deathFrames[0]);
        sprite.setScale(cellSize / 128, cellSize / 128);
    }
}

void Player::startLevelUpAnimation() {
    if (!isLevelingUp) {
        isLevelingUp = true;
        currentLevelUpFrame = 0;
        levelUpAnimationTimer = 0.0f;
        sprite.setTexture(levelUpTexture);
        sprite.setTextureRect(levelUpFrames[0]);
        sprite.setScale(cellSize / 192, cellSize / 192);
    }
}
