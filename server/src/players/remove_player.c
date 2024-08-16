/*
** EPITECH PROJECT, 2024
** server
** File description:
** remove_player
*/

#include "server.h"

void remove_player(server_t *server, player_t *player)
{
    server->map->slots[player->pos.y][player->pos.x].nb_players--;
    player->team->nb_players--;
    player->team->free_slots++;
    player->egg->is_hatched = false;
    player->egg->player = NULL;
    player->egg->pos.x = rand() % server->params->width;
    player->egg->pos.y = rand() % server->params->height;
    free(player);
}
