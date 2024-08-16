/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** new_client
*/

#include "server.h"

static void init_client(client_t *new, int fd)
{
    new->fd = fd;
    new->stream = fdopen(fd, "rw");
    new->next = NULL;
    new->prev = NULL;
    new->instruction = NULL;
    new->nb_instruction = 0;
    new->i_read = 0;
    new->i_write = 0;
    new->is_graphic = false;
    new->current_instruction = false;
    new->instruction_time = 0;
    new->player = NULL;
    new->args = NULL;
    new->bloc_by_incantation = false;
}
static void add_back_list_client(server_t *server, int fd)
{
    client_t *new = malloc(sizeof(client_t));
    client_t *tmp = server->clients;

    if (new == NULL) {
        print_error("Error: Malloc failed.");
        return;
    }
    init_client(new, fd);
    if (new->stream == NULL) {
        print_error("Error: Fdopen failed.");
        return;
    }
    if (server->clients == NULL) {
        server->clients = new;
    } else {
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = new;
        new->prev = tmp;
    }
}

void server_new_client_handle(server_t *server)
{
    struct sockaddr_in client_addr;
    socklen_t client_addr_size = sizeof(client_addr);
    int client_fd;

    if (server->nbr_clients == MAX_CLIENT) {
        print_error("Error: Max player reached.");
        return;
    }
    client_fd = accept(server->socket.fd,
            (struct sockaddr *)&client_addr, &client_addr_size);
    if (client_fd == -1) {
        print_error("Error: Accept new client failed.");
        return;
    }
    print_debug("New client accepted.", true);
    server->nbr_clients++;
    if (client_fd > server->max_fd)
        server->max_fd = client_fd;
    add_back_list_client(server, client_fd);
    write(client_fd, "WELCOME\n", 8);
}
