/*
** EPITECH PROJECT, 2024
** server
** File description:
** player_pos
*/

#include "server.h"

player_t *get_player_by_id(server_t *server, int player_id)
{
    client_t *tmp = server->clients;

    while (tmp) {
        if (tmp->fd == player_id)
            return tmp->player;
        tmp = tmp->next;
    }
    return NULL;
}

void player_pos(server_t *server, char **tab)
{
    int player_id = atoi(tab[1]);
    player_t *player = get_player_by_id(server, player_id);

    if (player == NULL) {
        print_sbp(server->fd_graphic);
        return;
    }
    dprintf(server->fd_graphic, "ppo %d %d %d %d\n", player_id,
        player->pos.x, player->pos.y, player->orientation + 1);
}
