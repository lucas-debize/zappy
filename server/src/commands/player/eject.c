/*
** EPITECH PROJECT, 2024
** server
** File description:
** forward
*/

#include "server.h"

static void other_coords(client_t *client, server_t *server, int *x, int *y)
{
    if (client->player->orientation == 2) {
        if (*y == server->map->height - 1)
            *y = 0;
        else
            (*y)++;
        client->player->str = 1;
    }
    if (client->player->orientation == 3) {
        if (*x == 0)
            *x = server->map->width - 1;
        else
            (*x)--;
        client->player->str = 7;
    }
}

static void get_new_coord(int *x, int *y, client_t *client, server_t *server)
{
    if (client->player->orientation == 0) {
        if (*y == 0)
            *y = server->map->height - 1;
        else
            (*y)--;
        client->player->str = 5;
    }
    if (client->player->orientation == 1) {
        if (*x == server->map->width - 1)
            *x = 0;
        else
            (*x)++;
        client->player->str = 3;
    }
    other_coords(client, server, x, y);
}

static void delete_eggs(server_t *server, int x, int y, int i)
{
    egg_t *current_egg = server->teams[i].eggs;
    char str[10];

    while (current_egg != NULL) {
        if (current_egg->pos.x == x && current_egg->pos.y == y) {
            snprintf(str, sizeof(str), "edi %d\n", current_egg->id);
            write_to_graphic(server, str);
            current_egg->is_hatched = true;
            server->teams[i].nb_eggs--;
        }
        current_egg = current_egg->next;
    }
}

static int change_player_coords(client_t *client,
    server_t *server, int x, int y)
{
    client_t *tmp = server->clients;
    int res = 1;

    while (tmp != NULL) {
        if (tmp->fd == client->fd) {
            tmp = tmp->next;
            continue;
        }
        if (tmp->player != NULL
        && tmp->player->pos.x == client->player->pos.x
        && tmp->player->pos.y == client->player->pos.y) {
            move_position(server, x, y, tmp);
            res = 0;
            dprintf(tmp->fd, "eject: %d\n", client->player->str);
        }
        tmp = tmp->next;
    }
    return res;
}

void handle_eject(server_t *server, client_t *client)
{
    int x = client->player->pos.x;
    int y = client->player->pos.y;
    char str[100] = "";

    server->map->slots[y][x].nb_eggs = 0;
    for (int i = 0; i != server->nb_teams; i++) {
        if (server->teams[i].nb_players == 0)
            continue;
        delete_eggs(server, x, y, i);
    }
    get_new_coord(&x, &y, client, server);
    if (change_player_coords(client, server, x, y)) {
        if (!DONT_KO_EJECT)
            print_ko(client->fd);
        return;
    }
    print_ok(client->fd);
    snprintf(str, sizeof(str), "pex %d\n", client->fd);
    write_to_graphic(server, str);
}
