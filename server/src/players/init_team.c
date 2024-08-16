/*
** EPITECH PROJECT, 2024
** myFtp
** File description:
** print_debug
*/

#include "server.h"

static void init_eggs(server_t *server, team_t *team)
{
    for (int i = 0; i < server->params->player_max_no_egg; i++) {
        add_back_egg(server, team, i);
        usleep(100);
    }
}

void init_team(server_t *server)
{
    server->nb_players = 0;
    server->nb_teams = server->params->team_max;
    for (int i = 0; i < server->nb_teams; i++) {
        server->teams[i].team_name = server->params->team_names[i];
        server->teams[i].nb_players = 0;
        init_eggs(server, &server->teams[i]);
        server->teams->last_egg_id = server->params->player_max_no_egg;
        server->teams[i].nb_eggs = server->params->player_max_no_egg;
        server->teams[i].free_slots = server->params->player_max_no_egg;
        server->teams[i].nb_eggs = server->params->player_max_no_egg;
    }
}
