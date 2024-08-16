/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-dorian.senecot
** File description:
** player.hpp
*/

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <sstream>
#include <iostream>
#include <memory>
#include <cmath>

class Player {
public:
    Player(int id, int x, int y, float cellSize, float offsetX, float offsetY, const std::string &direction, int level, const std::string &teamName);

    void setPosition(float x, float y);
    void setCellSize(float cellSize);
    void setOffsets(float offsetX, float offsetY);
    void setDirection(const std::string &direction);
    void setLevel(int level);
    const std::string getTeam() const;
    int getLevel() const;
    void draw(sf::RenderWindow &window) const;
    int getId() const;
    void setInventory(const std::array<int, 7> &inventory);
    const std::array<int, 7>& getInventory() const;
    void update(float deltaTime);
    void updateDirectionSpritePosition();
    void setTeamSprite(std::shared_ptr<sf::Texture> teamTexture);
    void startDeathAnimation();
    void startLevelUpAnimation();
    void broadcast(const std::string &message);
    void updateBroadcastEffect(float deltaTime);
    bool containsPoint(sf::Vector2f point) const;
    void setInventoryVisible(bool visible);
    bool isInventoryVisible() const;

private:
    int id;
    std::string teamName;
    int x, y;
    int level;
    float cellSize;
    float offsetX, offsetY;
    std::string direction;
    std::array<int, 7> inventory;
    sf::Sprite sprite;
    std::shared_ptr<sf::Texture> texture;
    std::vector<sf::IntRect> frames;
    int currentFrame;
    sf::Clock animationClock;
    float animationTimer;
    float timePerFrame;
    sf::Sprite directionSprite;
    std::shared_ptr<sf::Texture> directionTexture;
    float scaleAnimationTimer;
    void loadDirectionSpritesheet();
    void loadSpritesheet();
    void loadDeathSpritesheet();
    bool isDying = false;
    bool isDead = false;
    sf::Texture deathTexture;
    std::vector<sf::IntRect> deathFrames;
    int currentDeathFrame = 0;
    float deathAnimationTimer = 0.0f;
    sf::Texture levelUpTexture;
    std::vector<sf::IntRect> levelUpFrames;
    bool isLevelingUp = false;
    float levelUpAnimationTimer = 0.0f;
    int currentLevelUpFrame = 0;
    bool isBroadcasting = false;
    float broadcastEffectRadius = 0.0f;
    float broadcastSpeed = 500.0f;
    sf::CircleShape broadcastCircle;
    std::string broadcastMessage;
    sf::Text broadcastText;
    void loadLevelUpSpritesheet();
    bool displayInventory;
    sf::Text inventoryText;
};

#endif // PLAYER_HPP
