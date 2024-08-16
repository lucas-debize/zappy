/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** server
*/

#include "server.h"

int server_init(server_t *server, params_t *args)
{
    server->nbr_clients = 0;
    server->clients = NULL;
    server->readfds = (fd_set) {0};
    server->socket.fd = create_socket(server, args);
    if (server->socket.fd < 0)
        return 84;
    server->max_fd = server->socket.fd;
    server->is_running = true;
    server->last_graphic_tick = 0;
    return 0;
}
