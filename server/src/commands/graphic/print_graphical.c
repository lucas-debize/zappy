/*
** EPITECH PROJECT, 2024
** server
** File description:
** print_graphical
*/

#include "server.h"

void print_graphical(server_t *server)
{
    long long now = current_time_in_milliseconds();

    if (now - server->last_graphic_tick < (60 / FPS * 1000)) {
        return;
    }
    if (server->fd_graphic == 0) {
        return;
    }
    content_of_map(server, NULL);
    server->last_graphic_tick = now;
}
