/*
** EPITECH PROJECT, 2024
** server
** File description:
** forward
*/

#include "server.h"

static int check_nbr_eggs(server_t *server)
{
    int total_eggs = 0;

    for (int i = 0; i < server->nb_teams; i++) {
        total_eggs += server->teams[i].nb_eggs;
    }
    if (total_eggs == MAX_PLAYERS)
        return 1;
    return 0;
}

void handle_fork(server_t *server, client_t *client)
{
    char msg[100] = "";

    if (check_nbr_eggs(server)) {
        print_ko(client->fd);
        return;
    }
    add_back_egg(server, client->player->team,
        client->player->team->last_egg_id + 1);
    server->map->slots[client->player->pos.y][client->player->pos.x].nb_eggs++;
    client->player->team->last_egg_id++;
    client->player->team->nb_eggs++;
    client->player->team->free_slots++;
    print_ok(client->fd);
    snprintf(msg, sizeof(msg), "enw %d %d %d %d\n",
        client->player->team->last_egg_id,
        client->fd, client->player->pos.x, client->player->pos.y);
    if (server->params->display_egg)
        write_to_graphic(server, msg);
}
