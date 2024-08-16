/*
** EPITECH PROJECT, 2024
** server
** File description:
** forward
*/

#include "server.h"

void handle_slot(server_t *server, client_t *client,
    char *result, size_t *length)
{
    slot_t *current_slot = &server->map->slots[client->player->tile_y]
        [client->player->tile_x];

    append_tile_info(result, length, current_slot, server);
}

int test_to_display(int dist, int vision_range, int i)
{
    if (dist != vision_range || i != dist)
        return 1;
    return 0;
}

void is_right(client_t *client, int dist, int i, server_t *server)
{
    client->player->tile_x = (client->player->pos.x
        + dist + server->map->width) % server->map->width;
    client->player->tile_y = (client->player->pos.y
        + i + server->map->height) % server->map->height;
}

void is_left(client_t *client, int dist, int i, server_t *server)
{
    client->player->tile_x = (client->player->pos.x
        - dist + server->map->width) % server->map->width;
    client->player->tile_y = (client->player->pos.y
        - i + server->map->height) % server->map->height;
}

void is_down(client_t *client, int dist, int i, server_t *server)
{
    client->player->tile_x = (client->player->pos.x
        - i + server->map->width) % server->map->width;
    client->player->tile_y = (client->player->pos.y
        + dist + server->map->height) % server->map->height;
}
