/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-dorian.senecot
** File description:
** songs.cpp
*/

#include "songs.hpp"

void SongsPlayer::playDeathSound() {
    deathSound.play();
}

void SongsPlayer::playLevelUpSound() {
    levelUpSound.play();
}

void SongsPlayer::playMoveSound() {
    moveSound.play();
}

void SongsPlayer::playDropSound() {
    dropSound.play();
}

void SongsPlayer::playPickSound() {
    pickSound.play();
}

void SongsPlayer::playKickSound() {
    kickSound.play();
    kickSound.setVolume(25);
}

void SongsPlayer::playBroadcastSound() {
    BroadcastSound.play();
    BroadcastSound.setVolume(25);
}
