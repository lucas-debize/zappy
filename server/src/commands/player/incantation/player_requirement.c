/*
** EPITECH PROJECT, 2024
** server
** File description:
** player_requirement
*/

#include "server.h"

bool change_bloc(client_t *client_stock[MAX_PLAYERS],
    int max_p, int fd)
{
    long long now = current_time_in_milliseconds();

    for (int i = 0; i < max_p; i++) {
        if (client_stock[i]->fd == fd)
            continue;
        if (client_stock[i]->bloc_by_incantation == true) {
            client_stock[i]->bloc_by_incantation = false;
            client_stock[i]->instruction_time = now;
        } else {
            client_stock[i]->bloc_by_incantation = true;
            dprintf(client_stock[i]->fd, "Elevation underway\n");
        }
    }
    return true;
}

static void remove_incantation_cmd(client_t *client)
{
    if (INCANTATION_REMOVED == false)
        return;
    if (!strcmp("Incantation", list_type_cmd[client->type_instruction[client->i_read]].command)) {
        client->i_read++;
        client->nb_instruction--;
        printf("Incantation removed for the player %d\n", client->fd);
    }
}

bool player_requirement(server_t *server, client_t *client,
    Requirements req, int player_index)
{
    client_t *client_stock[MAX_PLAYERS];
    client_t *tmp = server->clients;
    int x = client->player->pos.x;
    int y = client->player->pos.y;

    while (tmp != NULL) {
        if (tmp->player == NULL
            || tmp->player->level != client->player->level) {
            tmp = tmp->next;
            continue;
        }
        if (tmp->player->pos.x == x && tmp->player->pos.y == y) {
            client_stock[player_index] = tmp;
            player_index++;
            remove_incantation_cmd(tmp);
        }
        tmp = tmp->next;
    }
    if (player_index < req.players)
        return false;
    return (change_bloc(client_stock, player_index, client->fd));
}

void check_level(client_t *tmp, int current_level)
{
    if (tmp->player->level == current_level) {
        tmp->player->level++;
        dprintf(tmp->fd, "Current level: %d\n", tmp->player->level);
    }
}

void player_elevation(client_t *client, server_t *server,
    int current_level)
{
    client_t *tmp = server->clients;
    int x = client->player->pos.x;
    int y = client->player->pos.y;

    while (tmp != NULL) {
        if (tmp->player != NULL &&
        tmp->player->pos.x == x && tmp->player->pos.y == y) {
            check_level(tmp, current_level);
        }
        tmp = tmp->next;
    }
}

void for_i_read(client_t *client)
{
    if (client->i_read == 9)
        client->i_read = 0;
    else
        client->i_read++;
}

void for_i_write(client_t *client)
{
    if (client->i_write == 9)
        client->i_write = 0;
    else
        client->i_write++;
    client->nb_instruction++;
}
