/*
** EPITECH PROJECT, 2024
** myFtp
** File description:
** print_debug
*/

#include "server.h"

static void create_inventory(player_t *players)
{
    for (int i = 0; i < MAX_RESOURCES; i++) {
        players->inventory[i].quantity = resources_names[i].quantity;
        players->inventory[i].name = resources_names[i].name;
    }
}

static int add_to_team(server_t *server, team_t *teams, player_t *player)
{
    egg_t *egg = teams->eggs;
    if (server->nb_players >= MAX_PLAYERS)
        return -1;
    if (teams->free_slots == 0)
        return -1;
    teams->nb_players++;
    teams->free_slots--;
    while (egg) {
        if (egg->is_hatched == false) {
            egg->player = player;
            egg->is_hatched = true;
            player->pos.x = egg->pos.x;
            player->pos.y = egg->pos.y;
            player->egg = egg;
            return 0;
        }
        egg = egg->next;
    }
    return 0;
}

static void init_player(player_t *player, team_t *team)
{
    long long now = current_time_in_milliseconds();

    player->orientation = rand() % 4;
    player->level = 1;
    create_inventory(player);
    player->inventory[0].quantity = 10;
    player->team = team;
    player->last_eat = now;
}

int create_player(server_t *server, client_t *client, team_t *team)
{
    player_t *player = malloc(sizeof(player_t));

    memset(player, 0, sizeof(player_t));
    if (player == NULL)
        return 1;
    memset(player->inventory, 0, sizeof(player->inventory));
    init_player(player, team);
    if (add_to_team(server, team, player) == -1) {
        free(player);
        return 1;
    }
    server->map->slots[player->pos.y][player->pos.x].nb_players++;
    server->map->slots[player->pos.y][player->pos.x].nb_eggs--;
    server->nb_players++;
    client->player = player;
    return 0;
}
