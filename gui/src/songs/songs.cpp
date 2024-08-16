/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-dorian.senecot
** File description:
** songs.cpp
*/

#include "songs.hpp"
#include <iostream>

SongsPlayer::~SongsPlayer() {
    stop();
}

void SongsPlayer::play(const std::string &filename) {
    if (!music.openFromFile(filename)) {
        return;
    }

    music.play();
    playing = true;
    musicThread = std::make_unique<std::thread>(&SongsPlayer::musicThreadFunction, this);
}

void SongsPlayer::playloop(const std::string &filename) {
    if (!music.openFromFile(filename)) {
        std::cerr << "Error: Could not load music file " << filename << std::endl;
        return;
    }
    music.setLoop(true);
    music.play();
}

void SongsPlayer::pause() {
    if (playing) {
        music.pause();
        playing = false;
    }
}

void SongsPlayer::stop() {
    if (playing) {
        music.stop();
        playing = false;
        if (musicThread && musicThread->joinable()) {
            musicThread->join();
        }
    }
}

void SongsPlayer::setVolume(float volume) {
    music.setVolume(volume);
}

void SongsPlayer::musicThreadFunction() {
    while (playing) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

