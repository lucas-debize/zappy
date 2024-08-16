/*
** EPITECH PROJECT, 2024
** server
** File description:
** destroy_map
*/

#include "server.h"

void destroy_map(server_t *server)
{
    for (int y = 0; y < server->map->height; y++)
        free(server->map->slots[y]);
    free(server->map->slots);
    free(server->map);
}
