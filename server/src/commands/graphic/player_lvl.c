/*
** EPITECH PROJECT, 2024
** server
** File description:
** player_lvl
*/

#include "server.h"

void player_lvl(server_t *server, char **tab)
{
    int player_id = atoi(tab[1]);
    player_t *player = get_player_by_id(server, player_id);

    if (player == NULL) {
        print_sbp(server->fd_graphic);
        return;
    }
    dprintf(server->fd_graphic, "plv %d %d\n", player_id, player->level);
}
