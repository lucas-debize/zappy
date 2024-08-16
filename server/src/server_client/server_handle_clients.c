/*
** EPITECH PROJECT, 2024
** server
** File description:
** server_handle_client
*/

#include "server.h"

static void handling_command(client_t *tmp, server_t *server)
{
    if (FD_ISSET(tmp->fd, &server->readfds)) {
        print_debug("Handling client command...", true);
        if (!handle_client_command(server, tmp))
            return;
        print_debug("Client command handled.", true);
    }
    if (server->clients == NULL)
        return;
    if (tmp->nb_instruction > 0) {
        print_debug("Executing command..", true);
        execute_command(server, tmp);
        print_debug("Command executed", true);
    }
}

void server_handle_clients(server_t *server)
{
    client_t *tmp = server->clients;
    client_t *tmp_next = NULL;

    print_debug("Checking clients...", true);
    while (tmp) {
        tmp_next = tmp->next;
        if (check_live(server, tmp))
            handling_command(tmp, server);
        else {
            remove_client(server, tmp);
            server->nbr_clients--;
        }
        if (server->clients == NULL)
            break;
        tmp = tmp_next;
    }
    print_debug("All clients handled.", true);
    print_debug("Waiting for new events...", true);
}
