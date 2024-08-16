/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-dorian.senecot
** File description:
** rendering.cpp
*/

#include "rendering.hpp"
#include "tile.hpp"
#include "helpers.hpp"
#include "../include/player_handling.hpp"
#include "songs.hpp"

int totalResources = 0;
int totalFood = 0;
int totalLinemate = 0;
int totalDeraumere = 0;
int totalSibur = 0;
int totalMendiane = 0;
int totalPhiras = 0;
int totalThystame = 0;
int totalDeaths = 0;
int totalTeams = 0;
sf::Texture middleSpriteBanner;
sf::Text instructions;
sf::Text totalTeamsText;
sf::Text resourcesText;
sf::Text totalDeathsText;
sf::Texture middleSpriteTexture;
sf::Sprite middleSprite;
sf::Texture middle2SpriteTexture;
sf::Sprite middle2Sprite;
sf::Texture buttonTexture;
sf::Sprite buttonSprite;
std::vector<Player> players;
float globalCellSize = 50.f;
float globalOffsetX = 0.f;
float globalOffsetY = 0.f;
int mapWidth = 0;
int mapHeight = 0;
float zoomLevel = 1.0f;
const float minZoomLevel = 0.5f;
const float maxZoomLevel = 10.0f;
const float zoomStep = 0.1f;
std::mutex playerMutex;
ThreadSafeQueue commandQueue;
std::atomic<bool> running(true);
bool mapInitialized = false;
std::map<std::pair<int, int>, std::array<int, 7>> tileContents;
sf::Font font;
std::mutex tileContentsMutex;
sf::Texture waterTexture;
sf::Texture mapTexture;
sf::Texture foamTexture;
sf::Texture rockTexture;
sf::Texture gemTextures[7];
sf::Texture foodIdleTexture;
sf::Texture foodSpawnTexture;
SongsPlayer songsPlayer;
sf::Texture buttonPressedTexture;
sf::Sprite buttonPressedSprite;
bool buttonPressed = false;
bool isDragging = false;
sf::Vector2i dragStartPosition;
sf::Vector2f dragStartOffset;
sf::Text textTotalResources;
sf::Text textFood;
sf::Text textLinemate;
sf::Text textDeraumere;
sf::Text textSibur;
sf::Text textMendiane;
sf::Text textPhiras;
sf::Text textThystame;
sf::Text textInfos;
sf::Sprite middleBanner;
std::vector<sf::Text> playerInfoTexts;
sf::Texture button2Texture;
sf::Texture button2PressedTexture;
sf::Sprite button2Sprite;
sf::Sprite button2PressedSprite;
bool button2Pressed = false;

void processServerCommand(const std::string &command, sf::RenderWindow &window) {
    std::vector<std::string> tokens = split(command, ' ');
    std::cout << "Tokens: ";
    for (const auto &token : tokens) {
        std::cout << token << " ";
    }
    std::cout << std::endl;

    if (tokens.empty()) {
        std::cerr << "Error: Empty command received." << std::endl;
        return;
    }

    if (tokens[0] == "msz") {
        if (tokens.size() < 3) {
            std::cerr << "Error: Invalid map size data received." << std::endl;
            return;
        }
        mapWidth = std::stoi(tokens[1]);
        mapHeight = std::stoi(tokens[2]);
        createMap(window, mapWidth, mapHeight);
    } else if (tokens[0] == "pnw") {
        handlePlayerCreate(tokens);
    } else if (tokens[0] == "ppo") {
        handlePlayerPosition(tokens);
    } else if (tokens[0] == "plv") {
        handlePlayerLevel(tokens);
    } else if (tokens[0] == "pin") {
        handlePlayerInventory(tokens);
    } else if (tokens[0] == "bct") {
        handleTileContent(tokens);
    } else if (tokens[0] == "pdi") {
        handlePlayerDeath(tokens);
    } else if (tokens[0] == "tna") {
        tokens.erase(tokens.begin());
        handleTeamNames(tokens);
        totalTeams++;
    } else if (tokens[0] == "pdr") {
        handleResourceDrop(tokens);
    } else if (tokens[0] == "pgt") {
        handleResourceCollect(tokens);
    } else if (tokens[0] == "pex") {
        handlePlayerExpulsion(tokens);
    } else if (tokens[0] == "pic") {
        handleIncantationStart(tokens);
    } else if (tokens[0] == "pbc") {
        handlePlayerBroadcast(tokens);
    } else {
        std::cerr << "Error: Unknown command received: " << tokens[0] << std::endl;
    }
}

void mapisInitialized(sf::RenderWindow &window, sf::Clock &clock) {
    float deltaTime = clock.restart().asSeconds();
    updateAnimations(deltaTime);
    for (auto& player : players) {
        player.updateBroadcastEffect(deltaTime);
        player.update(deltaTime);
    }
    window.clear();
    drawMap(window, mapWidth, mapHeight);
    {
        std::lock_guard<std::mutex> lock(playerMutex);
        for (const auto& player : players) {
            player.draw(window);
        }
    }
    draw_hud(window);
}

int runGameClient(Config *config) {
    sf::RenderWindow window;
    sf::TcpSocket socket;
    std::string command;
    sf::Clock clock;

    initializeWindow(window);
    if (!loadResources()) return 84;
    configureGraphics();
    handleResize(window);
    if (!connectAndInitialize(config, socket)) return 84;
    std::thread receiveThread(receiveServerData, std::ref(socket));
    const float targetFrameRate = 1.0f / 60.0f;
    while (window.isOpen()) {
        handleEvents(window, socket);
        while (commandQueue.pop(command)) {
            processServerCommand(command, window);
        }
        if (mapInitialized) {
            mapisInitialized(window, clock);
        }
    }
    songsPlayer.stop();
    receiveThread.join();
    return 0;
}
