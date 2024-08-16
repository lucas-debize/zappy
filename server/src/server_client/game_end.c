/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** new_client
*/

#include "server.h"

void end_game(server_t *server, char *name)
{
    client_t *tmp = server->clients;

    while (tmp != NULL) {
        dprintf(tmp->fd, "Game end\nWinning team is: %s!\n", name);
        tmp = tmp->next;
    }
    server->is_running = false;
}

void check_end(server_t *server)
{
    client_t *tmp = server->clients;

    while (tmp != NULL) {
        if (tmp->player != NULL && tmp->player->level >= 8)
            tmp->player->team->victory += 1;
        tmp = tmp->next;
    }
    for (int i = 0; i < server->nb_teams; i++) {
        if (server->teams[i].nb_players > 0 && server->teams[i].victory >= 6) {
            end_game(server, server->teams[i].team_name);
            return;
        }
        server->teams[i].victory = 0;
    }
}
