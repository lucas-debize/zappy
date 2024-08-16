/*
** EPITECH PROJECT, 2024
** server
** File description:
** destroy_server
*/

#include "server.h"

void destroy_clients(server_t *server)
{
    client_t *tmp = server->clients;
    client_t *next;

    while (tmp) {
        next = tmp->next;
        free_client(server, tmp);
        tmp = next;
    }
}

void destroy_server(server_t *server)
{
    print_error("Server is destroying...");
    destroy_clients(server);
////    destroy_players(server->players);
    destroy_teams_eggs(server);
////    destroy_params(server->params);
    destroy_map(server);
    close(server->socket.fd);
}
