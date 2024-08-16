/*
** EPITECH PROJECT, 2024
** server
** File description:
** add_back_egg
*/

#include "server.h"

static void init_new_egg(int w, int h, int id, egg_t *new)
{
    new->id = id;
    new->pos.x = rand() % w;
    new->pos.y = rand() % h;
    new->is_hatched = false;
    new->player = NULL;
    new->next = NULL;
}

void add_back_egg(server_t *server, team_t *team, int egg_id)
{
    egg_t *tmp = team->eggs;
    egg_t *new = malloc(sizeof(egg_t));

    if (!new) {
        print_error("Malloc failed.");
        return;
    }
    init_new_egg(server->params->width, server->params->height, egg_id, new);
    server->map->slots[new->pos.y][new->pos.x].nb_eggs++;
    if (!tmp) {
        team->eggs = new;
        return;
    }
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new;
}
