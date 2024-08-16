/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-dorian.senecot
** File description:
** songs.cpp
*/

#include "songs.hpp"

SongsPlayer::SongsPlayer() : playing(false) {
    if (!deathSoundBuffer.loadFromFile("ressource/songs/death.ogg")) {
        std::cerr << "Error: Could not load death sound." << std::endl;
    }
    deathSound.setBuffer(deathSoundBuffer);

    if (!levelUpSoundBuffer.loadFromFile("ressource/songs/lvlup.ogg")) {
        std::cerr << "Error: Could not load level up sound." << std::endl;
    }
    levelUpSound.setBuffer(levelUpSoundBuffer);
    if (!moveSoundBuffer.loadFromFile("ressource/songs/forward.ogg")) {
        std::cerr << "Error: Could not load move sound." << std::endl;
    }
    moveSound.setBuffer(moveSoundBuffer);
    if (!pickSoundBuffer.loadFromFile("ressource/songs/pickitem.ogg")) {
        std::cerr << "Error: Could not load move sound." << std::endl;
    }
    pickSound.setBuffer(pickSoundBuffer);
    if (!dropSoundBuffer.loadFromFile("ressource/songs/dropitem.ogg")) {
        std::cerr << "Error: Could not load move sound." << std::endl;
    }
    dropSound.setBuffer(dropSoundBuffer);
    if (!kickSoundBuffer.loadFromFile("ressource/songs/kick.ogg")) {
        std::cerr << "Error: Could not load move sound." << std::endl;
    }
    kickSound.setBuffer(kickSoundBuffer);
    if (!BroadcastSoundBuffer.loadFromFile("ressource/songs/broad.ogg")) {
        std::cerr << "Error: Could not load move sound." << std::endl;
    }
    BroadcastSound.setBuffer(BroadcastSoundBuffer);
}
