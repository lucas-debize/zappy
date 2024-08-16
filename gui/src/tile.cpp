/*
** EPITECH PROJECT, 2023
** 2eme Année
** File description:
** tile.cpp
*/

#include "tile.hpp"
#include "rendering.hpp"

extern float globalCellSize;
extern float globalOffsetX;
extern float globalOffsetY;
extern int mapWidth;
extern int mapHeight;
extern std::map<std::pair<int, int>, std::array<int, 7>> tileContents;
extern sf::Font font;
extern std::mutex tileContentsMutex;
extern std::vector<Player> players;
extern std::mutex playerMutex;
extern bool mapInitialized;
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

int foamFrame = 0;
const int foamFrameCount = 8;
const float foamAnimationSpeed = 0.1f;

const int gemFrameCount = 10;
const float gemAnimationSpeed = 0.1f;

const int foodSpawnFrameCount = 7;
const float foodSpawnAnimationSpeed = 0.1f;

struct Rock {
    sf::Vector2f position;
    int frame;
    float animationTime;
};

struct GemAnimation {
    int frame;
    float animationTime;
};

struct FoodAnimation {
    int frame;
    float animationTime;
    bool spawning;
};

std::vector<Rock> rocks;
std::map<std::pair<int, int>, std::array<GemAnimation, 6>> gemAnimations;
std::map<std::pair<int, int>, FoodAnimation> foodAnimations;

void updateResourceTotals() {
    totalResources = 0;
    totalFood = 0;
    totalLinemate = 0;
    totalDeraumere = 0;
    totalSibur = 0;
    totalMendiane = 0;
    totalPhiras = 0;
    totalThystame = 0;

    std::lock_guard<std::mutex> lock(tileContentsMutex);
    for (const auto& [coords, resources] : tileContents) {
        totalResources += std::accumulate(resources.begin(), resources.end(), 0);
        totalFood += resources[0];
        totalLinemate += resources[1];
        totalDeraumere += resources[2];
        totalSibur += resources[3];
        totalMendiane += resources[4];
        totalPhiras += resources[5];
        totalThystame += resources[6];
    }
}

void handleTileContent(const std::vector<std::string>& tokens) {
    if (tokens.size() < 10) {
        std::cerr << "Error: Invalid tile content data received." << std::endl;
        return;
    }

    int x = std::stoi(tokens[1]);
    int y = std::stoi(tokens[2]);
    std::array<int, 7> resources;
    for (int i = 0; i < 7; ++i) {
        resources[i] = std::stoi(tokens[3 + i]);
    }

    {
        std::lock_guard<std::mutex> lock(tileContentsMutex);
        tileContents[{x, y}] = resources;

        if (gemAnimations.find({x, y}) == gemAnimations.end()) {
            std::array<GemAnimation, 6> animations;
            for (int i = 0; i < 6; ++i) {
                animations[i] = {0, 0.f};
            }
            gemAnimations[{x, y}] = animations;
        }

        if (foodAnimations.find({x, y}) == foodAnimations.end()) {
            foodAnimations[{x, y}] = {0, 0.f, true};
        }
    }

    std::cout << "Tile (" << x << ", " << y << ") contents: ";
    for (const auto& res : resources) {
        std::cout << res << " ";
    }
    std::cout << std::endl;

    updateResourceTotals();
}

void updateAnimations(float deltaTime) {
    static float foamTimeAccumulator = 0.f;
    foamTimeAccumulator += deltaTime;
    if (foamTimeAccumulator >= foamAnimationSpeed) {
        foamTimeAccumulator = 0.f;
        foamFrame = (foamFrame + 1) % foamFrameCount;
    }

    for (auto &rock : rocks) {
        rock.animationTime += deltaTime;
        if (rock.animationTime >= 0.1f) {
            rock.animationTime = 0.f;
            rock.frame = (rock.frame + 1) % 8;
        }
    }

    std::lock_guard<std::mutex> lock(tileContentsMutex);
    for (auto& pair : gemAnimations) {
        for (int i = 0; i < 6; ++i) {
            pair.second[i].animationTime += deltaTime;
            if (pair.second[i].animationTime >= gemAnimationSpeed) {
                pair.second[i].animationTime = 0.f;
                pair.second[i].frame = (pair.second[i].frame + 1) % gemFrameCount;
            }
        }
    }

    for (auto& pair : foodAnimations) {
        pair.second.animationTime += deltaTime;
        if (pair.second.spawning) {
            if (pair.second.animationTime >= foodSpawnAnimationSpeed) {
                pair.second.animationTime = 0.f;
                pair.second.frame = (pair.second.frame + 1) % foodSpawnFrameCount;
                if (pair.second.frame == foodSpawnFrameCount - 1) {
                    pair.second.spawning = false;
                    pair.second.frame = 0;
                }
            }
        }
    }
}

void drawMap(sf::RenderWindow &window, int mapWidth, int mapHeight) {
    sf::RectangleShape cell(sf::Vector2f(globalCellSize, globalCellSize));
    cell.setFillColor(sf::Color::Transparent);
    cell.setOutlineColor(sf::Color::Black);
    cell.setOutlineThickness(1.f);

    sf::Sprite waterSprite;
    waterSprite.setTexture(waterTexture);
    waterSprite.setScale(globalCellSize / 64.f, globalCellSize / 64.f);

    sf::Sprite mapSprite;
    mapSprite.setTexture(mapTexture);
    mapSprite.setScale(globalCellSize / 64.f, globalCellSize / 64.f);

    sf::Sprite foamSprite;
    foamSprite.setTexture(foamTexture);
    foamSprite.setScale(globalCellSize / 64.f, globalCellSize / 64.f);

    sf::Sprite rockSprite;
    rockSprite.setTexture(rockTexture);
    rockSprite.setScale(globalCellSize / 64.f, globalCellSize / 64.f);

    sf::Sprite gemSprites[6];
    for (int i = 0; i < 6; ++i) {
        gemSprites[i].setTexture(gemTextures[i]);
        gemSprites[i].setScale(globalCellSize / 128.f, globalCellSize / 128.f);
    }

    sf::Sprite foodSprite;
    foodSprite.setScale(globalCellSize / 300.f, globalCellSize / 300.f);

    for (int y = 0; y < 1080 / globalCellSize; ++y) {
        for (int x = 0; x < 1920 / globalCellSize; ++x) {
            waterSprite.setPosition(x * globalCellSize, y * globalCellSize);
            window.draw(waterSprite);
        }
    }

    for (int y = 0; y < mapHeight; ++y) {
        for (int x = 0; x < mapWidth; ++x) {
            if (x == 0 || x == mapWidth - 1 || y == 0 || y == mapHeight - 1) {
                foamSprite.setTextureRect(sf::IntRect(foamFrame * 192, 0, 192, 192));
                foamSprite.setPosition(globalOffsetX + (x - 1) * globalCellSize, globalOffsetY + (y - 1) * globalCellSize);
                window.draw(foamSprite);
            }
        }
    }

    for (const auto &rock : rocks) {
        rockSprite.setPosition(rock.position);
        rockSprite.setTextureRect(sf::IntRect(rock.frame * 128, 0, 128, 128));
        window.draw(rockSprite);
    }

    for (int y = 0; y < mapHeight; ++y) {
        for (int x = 0; x < mapWidth; ++x) {
            if (x == 0 && y == 0) {
                // Top-left corner
                mapSprite.setTextureRect(sf::IntRect(0, 0, 64, 64));
            } else if (x == mapWidth - 1 && y == 0) {
                // Top-right corner
                mapSprite.setTextureRect(sf::IntRect(128, 0, 64, 64));
            } else if (x == 0 && y == mapHeight - 1) {
                // Bottom-left corner
                mapSprite.setTextureRect(sf::IntRect(0, 128, 64, 64));
            } else if (x == mapWidth - 1 && y == mapHeight - 1) {
                // Bottom-right corner
                mapSprite.setTextureRect(sf::IntRect(128, 128, 64, 64));
            } else if (y == 0) {
                // Top edge
                mapSprite.setTextureRect(sf::IntRect(64, 0, 64, 64));
            } else if (y == mapHeight - 1) {
                // Bottom edge
                mapSprite.setTextureRect(sf::IntRect(64, 128, 64, 64));
            } else if (x == 0) {
                // Left edge
                mapSprite.setTextureRect(sf::IntRect(0, 64, 64, 64));
            } else if (x == mapWidth - 1) {
                // Right edge
                mapSprite.setTextureRect(sf::IntRect(128, 64, 64, 64));
            } else {
                // Center
                mapSprite.setTextureRect(sf::IntRect(64, 64, 64, 64));
            }

            cell.setPosition(globalOffsetX + x * globalCellSize, globalOffsetY + y * globalCellSize);
            window.draw(cell);

            mapSprite.setPosition(globalOffsetX + x * globalCellSize, globalOffsetY + y * globalCellSize);
            window.draw(mapSprite);

            std::array<int, 7> resources;
            {
                std::lock_guard<std::mutex> lock(tileContentsMutex);
                auto it = tileContents.find({x, y});
                if (it != tileContents.end()) {
                    resources = it->second;
                } else {
                    continue;
                }
            }

            int foodIndex = 0;
            for (int count = 0; count < resources[0]; ++count) {
                int offsetX = foodIndex % 3;
                int offsetY = foodIndex / 3;

                const auto& foodAnimation = foodAnimations[{x, y}];
                if (foodAnimation.spawning) {
                    foodSprite.setTexture(foodSpawnTexture);
                    foodSprite.setTextureRect(sf::IntRect(foodAnimation.frame * 128, 0, 128, 128));
                } else {
                    foodSprite.setTexture(foodIdleTexture);
                    foodSprite.setTextureRect(sf::IntRect(0, 0, 128, 128));
                }
                foodSprite.setPosition(
                    globalOffsetX + x * globalCellSize + offsetX * (globalCellSize / 3),
                    globalOffsetY + y * globalCellSize + offsetY * (globalCellSize / 3)
                );
                window.draw(foodSprite);
                ++foodIndex;
            }

            int gemIndex = 0;
            for (int i = 1; i < 7; ++i) {
                const auto& gemAnimation = gemAnimations[{x, y}][i - 1];
                for (int count = 0; count < resources[i]; ++count) {
                    int offsetX = gemIndex % 3;
                    int offsetY = gemIndex / 3;

                    gemSprites[i - 1].setPosition(
                        globalOffsetX + x * globalCellSize + offsetX * (globalCellSize / 3), 
                        globalOffsetY + y * globalCellSize + offsetY * (globalCellSize / 3)
                    );
                    gemSprites[i - 1].setTextureRect(sf::IntRect(gemAnimation.frame * 18, 0, 18, 30));
                    window.draw(gemSprites[i - 1]);
                    ++gemIndex;
                }
            }
        }
    }
}

void createMap(sf::RenderWindow &window, int width, int height) {
    mapWidth = width;
    mapHeight = height;

    window.create(sf::VideoMode(1920, 1080), "Zappy", sf::Style::Resize | sf::Style::Close);

    float cellSizeX = 1920.0f / mapWidth;
    float cellSizeY = 1080.0f / mapHeight;
    globalCellSize = std::min(cellSizeX, cellSizeY);

    globalOffsetX = (1920 - (mapWidth * globalCellSize)) / 2.0f;
    globalOffsetY = (1080 - (mapHeight * globalCellSize)) / 2.0f;

    std::srand(static_cast<unsigned>(std::time(nullptr)));
    for (int i = 0; i < 20; ++i) {
        Rock rock;
        rock.position = sf::Vector2f(std::rand() % 1920, std::rand() % 1080);
        rock.frame = std::rand() % 8;
        rock.animationTime = 0.f;
        rocks.push_back(rock);
    }

    window.clear();
    drawMap(window, mapWidth, mapHeight);

    {
        std::lock_guard<std::mutex> lock(playerMutex);
        for (auto& player : players) {
            player.setCellSize(globalCellSize);
            player.setOffsets(globalOffsetX, globalOffsetY);
        }
    }

    window.display();
    mapInitialized = true;
}
