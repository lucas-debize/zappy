/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** creat_socket
*/

#include "server.h"

int create_socket(server_t *server, params_t *args_t)
{
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    server->socket.address.sin_family = AF_INET;
    server->socket.address.sin_port = htons(args_t->port);
    server->socket.address.sin_addr.s_addr = INADDR_ANY;
    if (sock == -1)
        print_error("Error: socket creation failed.");
    print_debug("Socket successfully created.", true);
    if (bind(sock, (struct sockaddr *)&server->socket.address,
        sizeof(server->socket.address)) == -1) {
        print_error("Error: bind failed.");
        return -1;
    }
    print_debug("Socket successfully bind to address.", true);
    if (listen(sock, MAX_PLAYERS) == -1)
        print_error("Error: listen failed.");
    print_debug("Queue successfully initialized.", true);
    return sock;
}
