/*
** EPITECH PROJECT, 2023
** 2eme Année
** File description:
** window_init.cpp
*/

#include "rendering.hpp"

bool showInventory;

void handleClosedEvent(sf::RenderWindow& window) {
    running = false;
    songsPlayer.stop();
    window.close();
}

void handleMouseWheelScrolledEvent(const sf::Event::MouseWheelScrollEvent& event) {
    float oldZoomLevel = zoomLevel;
    float delta = event.delta;
    if (delta > 0) {
        zoomLevel += delta * zoomStep;
        if (zoomLevel > maxZoomLevel) zoomLevel = maxZoomLevel;
    } else if (delta < 0) {
        zoomLevel += delta * zoomStep;
        if (zoomLevel < minZoomLevel) zoomLevel = minZoomLevel;
    }
    float zoomFactor = zoomLevel / oldZoomLevel;
    globalOffsetX *= zoomFactor;
    globalOffsetY *= zoomFactor;
    globalCellSize = 50.0f * zoomLevel;
    std::lock_guard<std::mutex> lock(playerMutex);
    for (auto& player : players) {
        player.setCellSize(globalCellSize);
        player.setOffsets(globalOffsetX, globalOffsetY);
    }
}

void handleMouseButtonPressedEvent(const sf::RenderWindow& window, const sf::Event::MouseButtonEvent& event, sf::TcpSocket& socket) {
    if (event.button == sf::Mouse::Left) {
        isDragging = true;
        dragStartPosition = sf::Mouse::getPosition(window);
        dragStartOffset = {globalOffsetX, globalOffsetY};

        if (buttonSprite.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
            buttonPressed = !buttonPressed;
            centerMiddleSprite();
            if (buttonPressed) {
                buttonSprite.setTexture(buttonPressedTexture);
            } else {
                buttonSprite.setTexture(buttonTexture);
            }
        } else if (button2Sprite.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
            button2Pressed = !button2Pressed;
            centerMiddleSprite2();
            if (button2Pressed) {
                button2Sprite.setTexture(button2PressedTexture);
                songsPlayer.setVolume(0);
            } else {
                button2Sprite.setTexture(button2Texture);
                songsPlayer.setVolume(100);
            }
        } else {
            std::lock_guard<std::mutex> lock(playerMutex);
            for (auto& player : players) {
                if (player.containsPoint(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                    showInventory = !player.isInventoryVisible();
                    player.setInventoryVisible(showInventory);
                    if (showInventory) {
                        std::string command = "pin " + std::to_string(player.getId()) + "\n";
                        sendData(socket, command);
                    }
                } else {
                    showInventory = false;
                    player.setInventoryVisible(false);
                }
            }
        }
    }
}

void handleMouseButtonReleasedEvent(const sf::Event::MouseButtonEvent& event) {
    if (event.button == sf::Mouse::Left) {
        isDragging = false;
    }
}

void handleMouseMovedEvent(const sf::RenderWindow& window, const sf::Event::MouseMoveEvent& event) {
    if (isDragging) {
        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
        sf::Vector2i delta = mousePosition - dragStartPosition;
        globalOffsetX = dragStartOffset.x + delta.x;
        globalOffsetY = dragStartOffset.y + delta.y;

        std::lock_guard<std::mutex> lock(playerMutex);
        for (auto& player : players) {
            player.setOffsets(globalOffsetX, globalOffsetY);
        }
    }
}

void handleEvents(sf::RenderWindow& window, sf::TcpSocket& socket) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            handleClosedEvent(window);
        } else if (event.type == sf::Event::MouseWheelScrolled) {
            handleMouseWheelScrolledEvent(event.mouseWheelScroll);
        } else if (event.type == sf::Event::MouseButtonPressed) {
            handleMouseButtonPressedEvent(window, event.mouseButton, socket);
        } else if (event.type == sf::Event::MouseButtonReleased) {
            handleMouseButtonReleasedEvent(event.mouseButton);
        } else if (event.type == sf::Event::MouseMoved) {
            handleMouseMovedEvent(window, event.mouseMove);
        }
    }
}
