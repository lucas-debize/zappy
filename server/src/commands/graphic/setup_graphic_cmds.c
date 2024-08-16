/*
** EPITECH PROJECT, 2024
** server
** File description:
** setup_graphic_cmds
*/

#include "server.h"

static void send_all_exist_players(server_t *server)
{
    client_t *tmp = server->clients;

    while (tmp) {
        if (tmp->player)
            connection_new_player(server, tmp);
        tmp = tmp->next;
    }
}

void setup_graphic_cmds(server_t *server)
{
    map_size(server, NULL);
    time_unit(server, NULL);
    content_of_map(server, NULL);
    name_teams(server, NULL);
    send_all_exist_players(server);
}
