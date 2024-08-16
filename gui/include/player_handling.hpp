/*
** EPITECH PROJECT, 2023
** 2eme Année
** File description:
** player_actions.hpp
*/

#ifndef PLAYER_ACTIONS_HPP
#define PLAYER_ACTIONS_HPP

#include <vector>
#include <string>
#include <mutex>
#include <algorithm>
#include <iostream>
#include "player.hpp"
#include "songs.hpp"
#include "rendering.hpp"
#include "team.hpp"

extern std::mutex playerMutex;
extern std::vector<Player> players;
extern SongsPlayer songsPlayer;

void handlePlayerLevel(const std::vector<std::string> &tokens);
void handlePlayerBroadcast(const std::vector<std::string> &tokens);
void handleIncantationStart(const std::vector<std::string> &tokens);
void handlePlayerDeath(const std::vector<std::string> &tokens);
void handlePlayerExpulsion(const std::vector<std::string>& tokens);
void handlePlayerInventory(const std::vector<std::string> &tokens);
void handleResourceDrop(const std::vector<std::string> &tokens);
void handleResourceCollect(const std::vector<std::string> &tokens);
std::string getDirection(int dir);
void handlePlayerPosition(const std::vector<std::string> &tokens);
void handlePlayerCreate(const std::vector<std::string>& tokens);

#endif // PLAYER_ACTIONS_HPP