/*
** EPITECH PROJECT, 2024
** server
** File description:
** player_inventory
*/

#include "server.h"

void player_inventory(server_t *server, char **tab)
{
    int player_id = atoi(tab[1]);
    player_t *player = get_player_by_id(server, player_id);
    char str[100];

    if (player == NULL) {
        print_sbp(server->fd_graphic);
        return;
    }
    sprintf(str, "pin %d %d %d %d %d %d %d %d %d %d\n", player_id,
        player->pos.x, player->pos.y, player->inventory[0].quantity,
        player->inventory[1].quantity, player->inventory[2].quantity, player->inventory[3].quantity,
        player->inventory[4].quantity, player->inventory[5].quantity, player->inventory[6].quantity);
    dprintf(server->fd_graphic, "%s", str);
}
