/*
** EPITECH PROJECT, 2023
** 2eme Année
** File description:
** window_init.cpp
*/

#include "rendering.hpp"

void initializeWindow(sf::RenderWindow& window) {
    window.create(sf::VideoMode(1920, 1080), "Zappy", sf::Style::Resize | sf::Style::Close);
    window.setFramerateLimit(60);
    songsPlayer.playloop("ressource/songs/maintheme.ogg");
    songsPlayer.setVolume(30);
}

bool loadResources() {
    if (!font.loadFromFile("ressource/font/Arial.ttf")) {
        std::cerr << "Error: Could not load font." << std::endl;
        return false;
    }

    std::vector<std::pair<std::string, sf::Texture*>> textures = {
        {"ressource/sprite/Terrain/Water/Water.png", &waterTexture},
        {"ressource/sprite/Terrain/Ground/Tilemap_Flat.png", &mapTexture},
        {"ressource/sprite/Terrain/Water/Foam/Foam.png", &foamTexture},
        {"ressource/sprite/Terrain/Water/Rocks/Rocks_01.png", &rockTexture},
        {"ressource/sprite/UI/Banners/Banner_Horizontal.png", &middleSpriteBanner},
        {"ressource/sprite/Resources/Resources/M_Idle.png", &foodIdleTexture},
        {"ressource/sprite/Resources/Resources/M_Spawn.png", &foodSpawnTexture},
        {"ressource/sprite/UI/Buttons/Button_Red.png", &buttonTexture},
        {"ressource/sprite/UI/Buttons/Button_Red_Pressed.png", &buttonPressedTexture},
        {"ressource/sprite/UI/Icons/Regular_02.png", &middleSpriteTexture},
        {"ressource/sprite/UI/Buttons/Button_Blue.png", &button2Texture},
        {"ressource/sprite/UI/Buttons/Button_Blue_Pressed.png", &button2PressedTexture},
        {"ressource/sprite/UI/Icons/Regular_03.png", &middle2SpriteTexture}
    };

    for (const auto& texturePair : textures) {
        if (!texturePair.second->loadFromFile(texturePair.first)) {
            std::cerr << "Error: Could not load texture: " << texturePair.first << std::endl;
            return false;
        }
    }

    const std::string gemFiles[7] = {
        "ressource/sprite/Resources/Gems/GEM 1/GEM 1 - BLUE - Spritesheet.png",
        "ressource/sprite/Resources/Gems/GEM 1/GEM 1 - GOLD - Spritesheet.png",
        "ressource/sprite/Resources/Gems/GEM 1/GEM 1 - LIGHT GREEN - Spritesheet.png",
        "ressource/sprite/Resources/Gems/GEM 1/GEM 1 - LILAC - Spritesheet.png",
        "ressource/sprite/Resources/Gems/GEM 1/GEM 1 - PURPLE - Spritesheet.png",
        "ressource/sprite/Resources/Gems/GEM 1/GEM 1 - RED - Spritesheet.png",
        "ressource/sprite/Resources/Gems/GEM 1/GEM 1 - TURQUOISE - Spritesheet.png"
    };

    for (int i = 0; i < 7; ++i) {
        if (!gemTextures[i].loadFromFile(gemFiles[i])) {
            std::cerr << "Error: Could not load gem texture: " << gemFiles[i] << std::endl;
            return false;
        }
    }

    return true;
}

bool connectAndInitialize(Config *config, sf::TcpSocket& socket) {
    if (connectToServer(config, socket) != 0) return false;

    char data[1024];
    std::size_t received;
    if (receiveData(socket, data, received) != 0) return false;

    std::string welcomeData(data, received);
    if (welcomeData.find("WELCOME") == std::string::npos) {
        std::cerr << "Error: Server response does not contain 'WELCOME'" << std::endl;
        return false;
    }

    std::string initialCommand = "GRAPHIC\n";
    if (sendData(socket, initialCommand) != 0) return false;

    return true;
}
