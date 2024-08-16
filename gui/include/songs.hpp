/*
** EPITECH PROJECT, 2023
** 2eme Année
** File description:
** songs.hpp
*/

#ifndef SONGS_HPP
#define SONGS_HPP

#include <SFML/Audio.hpp>
#include <string>
#include <thread>
#include <memory>
#include <iostream>

class SongsPlayer {
public:
    SongsPlayer();
    ~SongsPlayer();

    void play(const std::string &filename);
    void playloop(const std::string &filename);
    void pause();
    void stop();
    void setVolume(float volume);
    void playDeathSound();
    void playLevelUpSound();
    void playMoveSound();
    void playPickSound();
    void playDropSound();
    void playKickSound();
    void playBroadcastSound();

private:
    void musicThreadFunction();

    sf::Music music;
    bool playing;
    std::unique_ptr<std::thread> musicThread;
    sf::SoundBuffer deathSoundBuffer;
    sf::SoundBuffer levelUpSoundBuffer;
    sf::SoundBuffer moveSoundBuffer;
    sf::SoundBuffer pickSoundBuffer;
    sf::SoundBuffer dropSoundBuffer;
    sf::SoundBuffer kickSoundBuffer;
    sf::SoundBuffer BroadcastSoundBuffer;
    sf::Sound deathSound;
    sf::Sound levelUpSound;
    sf::Sound moveSound;
    sf::Sound pickSound;
    sf::Sound dropSound;
    sf::Sound kickSound;
    sf::Sound BroadcastSound;
};

#endif // SONGS_HPP
