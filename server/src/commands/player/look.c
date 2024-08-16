/*
** EPITECH PROJECT, 2024
** server
** File description:
** forward
*/

#include "server.h"

void display_ressources(slot_t *slot, int i, char *result, size_t *length)
{
    if (slot->resources[i].quantity > 0) {
        for (int j = 0; j < slot->resources[i].quantity; j++)
            *length += snprintf(result + *length, 4096
                - *length, " %s", slot->resources[i].name);
    }
}

void append_tile_info(char *result, size_t *length,
    slot_t *slot, server_t *server)
{
    if (slot->nb_players > 0) {
        for (int i = 0; i < slot->nb_players; i++)
            *length += snprintf(result + *length, 4096 - *length, " player");
    }
    for (int i = 0; i < 7; i++) {
        display_ressources(slot, i, result, length);
    }
    if (slot->nb_eggs > 0 && server->params->display_egg == 1) {
        for (int i = 0; i < slot->nb_eggs; i++)
            *length += snprintf(result + *length, 4096 - *length, " egg");
    }
}

void loop(client_t *client, server_t *server, int dist, int i)
{
    int x = client->player->pos.x;
    int y = client->player->pos.y;
    int w = server->map->width;
    int h = server->map->height;

    switch (client->player->orientation) {
        case 0:
            client->player->tile_x = (x + i + w) % w;
            client->player->tile_y = (y - dist + h) % h;
            break;
        case 1:
            is_right(client, dist, i, server);
            break;
        case 2:
            is_down(client, dist, i, server);
            break;
        case 3:
            is_left(client, dist, i, server);
            break;
    }
}

void handle_look(server_t *server, client_t *client)
{
    int level = client->player->level;
    int vision_range = level;
    char result[4096] = {0};
    size_t length = 0;
    int res = 0;

    length += snprintf(result + length, 4096 - length, "[");
    for (int dist = 0; dist <= vision_range; ++dist) {
        for (int i = -dist; i <= dist; ++i) {
            res = 0;
            loop(client, server, dist, i);
            handle_slot(server, client, result, &length);
            res = test_to_display(dist, vision_range, i);
            string_end(result, &length, res);
        }
    }
    length += snprintf(result + length, 4096 - length, " ]\n");
    write(client->fd, result, length);
}
