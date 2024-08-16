/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** content_of_tile
*/

#include "server.h"

char *bct_str(server_t *server, int x, int y)
{
    char *str = malloc(sizeof(char) * 50);

    sprintf(str, "bct %d %d %d %d %d %d %d %d %d\n", x, y, server->map->slots[y][x].resources[FOOD].quantity,
        server->map->slots[y][x].resources[LINEMATE].quantity, server->map->slots[y][x].resources[DERAUMERE].quantity,
        server->map->slots[y][x].resources[SIBUR].quantity, server->map->slots[y][x].resources[MENDIANE].quantity,
        server->map->slots[y][x].resources[PHIRAS].quantity, server->map->slots[y][x].resources[THYSTAME].quantity);
    return str;
}

void content_of_a_tile(server_t *server, char **tab)
{
    int x = atoi(tab[1]);
    int y = atoi(tab[2]);
    char *str;

    if (x >= server->params->width || y >= server->params->height) {
        print_sbp(server->fd_graphic);
        return;
    }
    str = bct_str(server, x, y);
    write_to_graphic(server, str);
    free(str);
}
