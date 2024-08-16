/*
** EPITECH PROJECT, 2024
** server
** File description:
** forward
*/

#include "server.h"

bool check_requirements(server_t *server, player_t *player, Requirements req)
{
    if (server->map->slots[player->pos.y]
        [player->pos.x].resources[1].quantity < req.linemate
    || server->map->slots[player->pos.y]
        [player->pos.x].resources[2].quantity < req.deraumere
    || server->map->slots[player->pos.y]
        [player->pos.x].resources[3].quantity < req.sibur
    || server->map->slots[player->pos.y]
        [player->pos.x].resources[4].quantity < req.mendiane
    || server->map->slots[player->pos.y]
        [player->pos.x].resources[5].quantity < req.phiras
    || server->map->slots[player->pos.y]
        [player->pos.x].resources[6].quantity < req.thystame) {
        return false;
    }
    return true;
}

static void perform_elevation(server_t *server, player_t *player,
    Requirements req)
{
    server->map->slots[player->pos.y]
        [player->pos.x].resources[1].quantity -= req.linemate;
    server->map->slots[player->pos.y]
        [player->pos.x].resources[2].quantity -= req.deraumere;
    server->map->slots[player->pos.y]
        [player->pos.x].resources[3].quantity -= req.sibur;
    server->map->slots[player->pos.y]
        [player->pos.x].resources[4].quantity -= req.mendiane;
    server->map->slots[player->pos.y]
        [player->pos.x].resources[5].quantity -= req.phiras;
    server->map->slots[player->pos.y]
        [player->pos.x].resources[6].quantity -= req.thystame;
}

void is_elevating(server_t *server, client_t *client, Requirements req)
{
    if (client->player->is_incanting) {
        client->player->is_incanting = false;
        perform_elevation(server, client->player, req);
        player_elevation(client, server, client->player->level);
        if (SHOW_LEVEL_UPDATES && client->player->level >= MIN_SHOW_LEVEL_UPDATES)
            printf("Player %d is now level %d\n", client->fd,
                client->player->level);
    } else {
        client->player->is_incanting = true;
        dprintf(client->fd, "Elevation underway\n");
    }
}

void handle_incantation(server_t *server, client_t *client)
{
    Requirements req = reqs[client->player->level];
    int player_index = 0;
    char str[1024] = {0};

    if (check_requirements(server, client->player, req)
        && player_requirement(server, client,
            req, player_index)) {
        is_elevating(server, client, req);
    } else {
        if (!client->player->is_incanting) {
            for_i_read(client);
            client->nb_instruction--;
            client->current_instruction = time(NULL);
        }
        print_ko(client->fd);
    }
    snprintf(str, sizeof(str), "plv %d %d\n",
        client->fd, client->player->level);
    write_to_graphic(server, str);
}
