/*
** EPITECH PROJECT, 2023
** 2eme Année
** File description:
** rendering.hpp
*/

#ifndef RENDERING_HPP
#define RENDERING_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <thread>
#include <condition_variable>
#include <atomic>
#include "config.hpp"
#include "player.hpp"
#include "thread.hpp"
#include "helpers.hpp"
#include "network.hpp"
#include "songs.hpp"
#include <algorithm>

extern std::vector<Player> players;
extern float globalCellSize;
extern float globalOffsetX;
extern float globalOffsetY;
extern int mapWidth;
extern int mapHeight;
extern std::mutex playerMutex;
extern ThreadSafeQueue commandQueue;
extern std::atomic<bool> running;
extern bool mapInitialized;
extern std::map<std::pair<int, int>, std::array<int, 7>> tileContents;
extern sf::Font font;
extern std::mutex tileContentsMutex;
extern sf::Texture waterTexture;
extern sf::Texture mapTexture;
extern sf::Texture foamTexture;
extern sf::Texture rockTexture;
extern sf::Texture gemTextures[7];
extern sf::Texture foodIdleTexture;
extern sf::Texture foodSpawnTexture;
extern int totalResources;
extern int totalFood;
extern int totalLinemate;
extern int totalDeraumere;
extern int totalSibur;
extern int totalMendiane;
extern int totalPhiras;
extern int totalThystame;
extern int totalDeaths;
extern int totalTeams;
extern SongsPlayer songsPlayer;
extern sf::Texture middleSpriteBanner;
extern sf::Texture buttonTexture;
extern sf::Texture buttonPressedTexture;
extern sf::Texture middleSpriteTexture;
extern sf::Sprite buttonSprite;
extern sf::Sprite buttonPressedSprite;
extern sf::Sprite middleSprite;
extern sf::Text resourcesText;
extern sf::Text textTotalResources;
extern sf::Text textFood;
extern sf::Text textLinemate;
extern sf::Text textDeraumere;
extern sf::Text textSibur;
extern sf::Text textMendiane;
extern sf::Text textPhiras;
extern sf::Text textThystame;
extern sf::Text textInfos;
extern sf::Text totalDeathsText;
extern sf::Text totalTeamsText;
extern sf::Sprite middleBanner;
extern sf::Text instructions;
extern bool buttonPressed;
extern bool isDragging;
extern sf::Vector2i dragStartPosition;
extern sf::Vector2f dragStartOffset;
extern float zoomLevel;
extern const float minZoomLevel;
extern const float maxZoomLevel;
extern const float zoomStep;
extern std::vector<sf::Text> playerInfoTexts;
extern bool showInventory;
extern std::deque<std::string> commandHistory;
extern const int maxCommandHistorySize;
extern sf::Font commandFont;
extern std::vector<sf::Text> commandTexts;
extern sf::Texture button2Texture;
extern sf::Texture button2PressedTexture;
extern sf::Sprite button2Sprite;
extern sf::Sprite button2PressedSprite;
extern bool button2Pressed;
extern sf::Texture middle2SpriteTexture;
extern sf::Sprite middle2Sprite;

void processServerCommand(const std::string &command, sf::RenderWindow &window);
void receiveServerData(sf::TcpSocket &socket);
int runGameClient(Config *config);
void initializeWindow(sf::RenderWindow& window);
bool loadResources();
bool connectAndInitialize(Config *config, sf::TcpSocket& socket);
void centerMiddleSprite();
void handleResize(const sf::RenderWindow &window);
void configureGraphics();
void handleEvents(sf::RenderWindow& window, sf::TcpSocket& socket);
void draw_hud(sf::RenderWindow &window);
void updateScoreboard();
void centerMiddleSprite2();

#endif // RENDERING_HPP
