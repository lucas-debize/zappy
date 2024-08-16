/*
** EPITECH PROJECT, 2024
** server
** File description:
** content_of_map
*/

#include "server.h"

static void print_width(server_t *server, int y)
{
    char *str;

    for (int x = 0; x < server->params->width; x++) {
        str = bct_str(server, x, y);
        if (!write_to_graphic(server, str)) {
            server->fd_graphic = 0;
            return;
        }
        free(str);
    }
}

void content_of_map(server_t *server, char **tab)
{
    (void) tab;

    for (int y = 0; y < server->params->height; y++) {
        print_width(server, y);
    }
}
