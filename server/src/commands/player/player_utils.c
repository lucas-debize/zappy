/*
** EPITECH PROJECT, 2024
** server
** File description:
** forward
*/

#include "server.h"

void string_end(char *result, size_t *length, int res)
{
    if (res == 1)
        *length += snprintf(result + *length, 4096 - *length, ",");
}

void move_position(server_t *server, int x, int y, client_t *tmp)
{
    server->map->slots[tmp->player->pos.y]
    [tmp->player->pos.x].nb_players--;
    server->map->slots[y][x].nb_players++;
    tmp->player->pos.x = x;
    tmp->player->pos.y = y;
}
