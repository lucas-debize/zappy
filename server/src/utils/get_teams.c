/*
** EPITECH PROJECT, 2024
** server
** File description:
** get_teams
*/

#include "server.h"

team_t *get_team(team_t *teams, char *team_name, int max_team)
{
    for (int i = 0; i < max_team; i++) {
        if (strcmp(teams[i].team_name, team_name) == 0)
            return &teams[i];
    }
    return NULL;
}
