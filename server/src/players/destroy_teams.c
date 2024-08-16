/*
** EPITECH PROJECT, 2024
** server
** File description:
** destroy_teams
*/

#include "server.h"

static void destroy_eggs(egg_t *egg)
{
    egg_t *tmp = egg;
    egg_t *next;

    while (tmp) {
        next = tmp->next;
        free(tmp);
        tmp = next;
    }
}

void destroy_teams_eggs(server_t *server)
{
    for (int i = 0; i < server->nb_teams; i++)
        destroy_eggs(server->teams[i].eggs);
}
