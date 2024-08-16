/*
** EPITECH PROJECT, 2024
** server
** File description:
** forward
*/

#include "server.h"

void border_map(server_t *server, client_t *client)
{
    if (client->player->pos.x < 0)
        client->player->pos.x = client->player->pos.x + server->params->width;
    if (client->player->pos.y < 0)
        client->player->pos.y = client->player->pos.y + server->params->height;
    if (client->player->pos.x == server->params->width)
        client->player->pos.x = client->player->pos.x - server->params->width;
    if (client->player->pos.y == server->params->height)
        client->player->pos.y = client->player->pos.y - server->params->height;
    server->map->slots[client->player->pos.y]
        [client->player->pos.x].nb_players++;
}

void change_pos_forward(player_t *players)
{
    switch (players->orientation) {
        case 0:
            players->pos.y = players->pos.y - 1;
            break;
        case 1:
            players->pos.x = players->pos.x + 1;
            break;
        case 2:
            players->pos.y = players->pos.y + 1;
            break;
        case 3:
            players->pos.x = players->pos.x - 1;
            break;
    }
}

void handle_forward(server_t *server, client_t *client)
{
    player_t *players = client->player;
    char str[30] = "";

    server->map->slots[client->player->pos.y]
        [client->player->pos.x].nb_players--;
    change_pos_forward(players);
    border_map(server, client);
    print_ok(client->fd);
    sprintf(str, "ppo %d %d %d %d\n", client->fd, client->player->pos.x,
        client->player->pos.y, client->player->orientation + 1);
    write_to_graphic(server, str);
}
