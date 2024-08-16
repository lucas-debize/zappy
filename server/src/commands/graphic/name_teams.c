/*
** EPITECH PROJECT, 2024
** server
** File description:
** name_teams
*/

#include "server.h"

void name_teams(server_t *server, char **tab)
{
    (void) tab;
    for (int i = 0; i < server->params->team_max; i++) {
        dprintf(server->fd_graphic, "tna %s\n", server->params->team_names[i]);
    }
}
