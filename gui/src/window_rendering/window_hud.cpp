/*
** EPITECH PROJECT, 2023
** 2eme Année
** File description:
** window_init.cpp
*/

#include "rendering.hpp"

void draw_hud(sf::RenderWindow &window) {
    totalDeathsText.setString("Total Deaths: " + std::to_string(totalDeaths));
    totalTeamsText.setString("Total Teams: " + std::to_string(totalTeams));
    textTotalResources.setString("Total Resources: " + std::to_string(totalResources));
    textFood.setString("Food: " + std::to_string(totalFood));
    textLinemate.setString("Linemate: " + std::to_string(totalLinemate));
    textDeraumere.setString("Deraumere: " + std::to_string(totalDeraumere));
    textSibur.setString("Sibur: " + std::to_string(totalSibur));
    textMendiane.setString("Mendiane: " + std::to_string(totalMendiane));
    textPhiras.setString("Phiras: " + std::to_string(totalPhiras));
    textThystame.setString("Thystame: " + std::to_string(totalThystame));
    textInfos.setString("Informations:");
    window.draw(textTotalResources);
    window.draw(textFood);
    window.draw(textLinemate);
    window.draw(textDeraumere);
    window.draw(textSibur);
    window.draw(textMendiane);
    window.draw(textPhiras);
    window.draw(textThystame);
    window.draw(textInfos);
    window.draw(resourcesText);
    window.draw(totalDeathsText);
    window.draw(totalTeamsText);
    window.draw(buttonSprite);
    window.draw(button2Pressed ? button2PressedSprite : button2Sprite);
    window.draw(middleSprite);
    window.draw(middle2Sprite);
    if (buttonPressed) {
        window.draw(middleBanner);
        window.draw(instructions);
    }
    window.display();
}

void updateScoreboard() {
    // Tri des joueurs par niveau (croissant)
    std::sort(players.begin(), players.end(), [](const Player& a, const Player& b) {
        return a.getLevel() < b.getLevel();
    });
    // Efface les textes précédents
    playerInfoTexts.clear();

    // Affichage des 30 premiers joueurs ou moins si moins de 30 joueurs
    int count = 0;
    for (const auto& player : players) {
        if (count >= 30) break;

        sf::Text playerInfo;
        playerInfo.setFont(font);
        playerInfo.setCharacterSize(20);
        playerInfo.setFillColor(sf::Color::White);
        playerInfo.setOutlineColor(sf::Color::Black);
        playerInfo.setOutlineThickness(1.0f);

        std::string info = "Player " + player.getTeam() + "/" + std::to_string(player.getId()) + " - Level: " + std::to_string(player.getLevel()) + "\n";

        playerInfo.setString(info);
        playerInfoTexts.push_back(playerInfo);

        ++count;
    }
}

void configureGraphics() {
    middleBanner.setTexture(middleSpriteBanner);
    button2Sprite.setTexture(button2Texture);
    button2PressedSprite.setTexture(button2PressedTexture);
    middleBanner.setScale(8.0f, 6.0f);
    instructions.setFont(font);
    instructions.setString("Welcome to Zappy!\n\nRules:\n1. Collect resources.\n2. Build and upgrade.\n3. Compete with other players.\n\nCommands:\n- Move up one tile: Forward\n- Turn 90 right: Right\n- Turn 90 left: Left\n- Look around: Look\n- Inventory: Inventory\n- Broadcast text: Broadcast text\n- Fork a player: Fork \n- Eject players from this tile: Eject\n- Take object: Take object\n- Set object down: Set object\n- Start incantation: Incantation\n\nEnjoy your adventure in Zappy!");
    instructions.setCharacterSize(20);
    instructions.setFillColor(sf::Color::White);
    instructions.setOutlineColor(sf::Color(0, 0, 0));
    instructions.setOutlineThickness(1);
    instructions.setStyle(sf::Text::Bold);
    textTotalResources.setFont(font);
    textFood.setFont(font);
    textLinemate.setFont(font);
    textDeraumere.setFont(font);
    textSibur.setFont(font);
    textMendiane.setFont(font);
    textPhiras.setFont(font);
    textThystame.setFont(font);
    int characterSize = 30;
    textTotalResources.setCharacterSize(35);
    textFood.setCharacterSize(characterSize);
    textLinemate.setCharacterSize(characterSize);
    textDeraumere.setCharacterSize(characterSize);
    textSibur.setCharacterSize(characterSize);
    textMendiane.setCharacterSize(characterSize);
    textPhiras.setCharacterSize(characterSize);
    textThystame.setCharacterSize(characterSize);
    textTotalResources.setFillColor(sf::Color::White);
    textTotalResources.setOutlineColor(sf::Color(0, 0, 0));
    textTotalResources.setOutlineThickness(1.0f);
    textFood.setFillColor(sf::Color(165, 42, 42)); // Marron
    textFood.setOutlineColor(sf::Color(0, 0, 0));
    textFood.setOutlineThickness(1.0f);
    textLinemate.setFillColor(sf::Color(0, 0, 255)); // Bleu
    textLinemate.setOutlineColor(sf::Color(0, 0, 0));
    textLinemate.setOutlineThickness(1.0f);
    textDeraumere.setFillColor(sf::Color(255, 255, 0)); // Jaune
    textDeraumere.setOutlineColor(sf::Color(0, 0, 0));
    textDeraumere.setOutlineThickness(1.0f);
    textSibur.setFillColor(sf::Color(0, 255, 0)); // Vert
    textSibur.setOutlineColor(sf::Color(0, 0, 0));
    textSibur.setOutlineThickness(1.0f);
    textMendiane.setFillColor(sf::Color::Magenta); // Rose
    textMendiane.setOutlineColor(sf::Color(0, 0, 0));
    textMendiane.setOutlineThickness(1.0f);
    textPhiras.setFillColor(sf::Color(128, 0, 128)); // Violet
    textPhiras.setOutlineColor(sf::Color(0, 0, 0));
    textPhiras.setOutlineThickness(1.0f);
    textThystame.setFillColor(sf::Color(255, 0, 0)); // Rouge
    textThystame.setOutlineColor(sf::Color(0, 0, 0));
    textThystame.setOutlineThickness(1.0f);
    totalDeathsText.setFont(font);
    totalDeathsText.setCharacterSize(30);
    totalDeathsText.setFillColor(sf::Color(165, 42, 42)); // Marron
    totalDeathsText.setOutlineColor(sf::Color(0, 0, 0));
    totalDeathsText.setOutlineThickness(1.0f);
    totalTeamsText.setFont(font);
    totalTeamsText.setCharacterSize(30);
    totalTeamsText.setFillColor(sf::Color(0, 206, 209)); // Cyan
    totalTeamsText.setOutlineColor(sf::Color(0, 0, 0));
    totalTeamsText.setOutlineThickness(1.0f);
    textInfos.setFont(font);
    textInfos.setCharacterSize(35);
    textInfos.setFillColor(sf::Color::White);
    textInfos.setOutlineColor(sf::Color(0, 0, 0));
    textInfos.setOutlineThickness(1.0f);
    buttonSprite.setTexture(buttonTexture);
    buttonPressedSprite.setTexture(buttonPressedTexture);
    middleSprite.setTexture(middleSpriteTexture);
    middle2Sprite.setTexture(middle2SpriteTexture);
}

void centerMiddleSprite() {
    float buttonX = buttonSprite.getPosition().x;
    float buttonY = buttonSprite.getPosition().y;
    float buttonWidth = buttonSprite.getGlobalBounds().width;
    float buttonHeight = buttonSprite.getGlobalBounds().height;
    
    float middleWidth = middleSprite.getGlobalBounds().width;
    float middleHeight = middleSprite.getGlobalBounds().height;

    float middleX = buttonX + (buttonWidth - middleWidth) / 2;
    float middleY = buttonY + (buttonHeight - middleHeight) / 2;

    if (buttonPressed) {
        middleY += 5;
    }
    middleSprite.setPosition(middleX, middleY);
}

void centerMiddleSprite2() {
    float buttonX = button2Sprite.getPosition().x;
    float buttonY = button2Sprite.getPosition().y;
    float buttonWidth = button2Sprite.getGlobalBounds().width;
    float buttonHeight = button2Sprite.getGlobalBounds().height;
    
    float middleWidth = middle2Sprite.getGlobalBounds().width;
    float middleHeight = middle2Sprite.getGlobalBounds().height;

    float middleX = buttonX + (buttonWidth - middleWidth) / 2;
    float middleY = buttonY + (buttonHeight - middleHeight) / 2;

    if (button2Pressed) {
        middleY += 5;
    }
    middle2Sprite.setPosition(middleX, middleY);
}

void handleResize(const sf::RenderWindow &window) {
    float buttonX = window.getSize().x - buttonSprite.getGlobalBounds().width - 10;
    float buttonY = 10;
    buttonSprite.setPosition(buttonX, buttonY);
    buttonPressedSprite.setPosition(buttonX, buttonY);
    float button2Y = buttonY + buttonSprite.getGlobalBounds().height + 10;
    button2Sprite.setPosition(buttonX, button2Y);
    button2PressedSprite.setPosition(buttonX, button2Y);
    buttonSprite.setPosition(buttonX, buttonY);
    buttonPressedSprite.setPosition(buttonX, buttonY);
    centerMiddleSprite();
    centerMiddleSprite2();
    resourcesText.setPosition(buttonX - 200, buttonY + buttonSprite.getGlobalBounds().height + 100);
    textTotalResources.setPosition(buttonX - 270, buttonY + buttonSprite.getGlobalBounds().height + 150);
    textFood.setPosition(buttonX - 270, buttonY + buttonSprite.getGlobalBounds().height + 210);
    textLinemate.setPosition(buttonX - 270, buttonY + buttonSprite.getGlobalBounds().height + 240);
    textDeraumere.setPosition(buttonX - 270, buttonY + buttonSprite.getGlobalBounds().height + 270);
    textSibur.setPosition(buttonX - 270, buttonY + buttonSprite.getGlobalBounds().height + 300);
    textMendiane.setPosition(buttonX - 270, buttonY + buttonSprite.getGlobalBounds().height + 330);
    textPhiras.setPosition(buttonX - 270, buttonY + buttonSprite.getGlobalBounds().height + 360);
    textThystame.setPosition(buttonX - 270, buttonY + buttonSprite.getGlobalBounds().height + 390);
    textInfos.setPosition(buttonX - 270, buttonY + buttonSprite.getGlobalBounds().height + 570);
    totalDeathsText.setPosition(buttonX - 270, buttonY + buttonSprite.getGlobalBounds().height + 630);
    totalTeamsText.setPosition(buttonX - 270, buttonY + buttonSprite.getGlobalBounds().height + 660);
    middleBanner.setPosition((window.getSize().x - middleBanner.getLocalBounds().width * middleBanner.getScale().x) / 2.0f, -225);
    instructions.setPosition((window.getSize().x - middleBanner.getLocalBounds().width) / 2.2f, 100);
}
