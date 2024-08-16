/*
** EPITECH PROJECT, 2024
** server
** File description:
** write_logged_client
*/

#include "server.h"

void write_to_logged_client(server_t *server, int fd, char *str)
{
    client_t *tmp = server->clients;

    while (tmp) {
        if (tmp->fd == fd) {
            tmp = tmp->next;
            continue;
        }
        dprintf(tmp->fd, "%s", str);
        tmp = tmp->next;
    }
}
