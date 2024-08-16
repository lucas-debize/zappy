/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** remove_client
*/

#include "server.h"

void free_client(server_t *server, client_t *client)
{
    char str[10];

    if (client->player != NULL) {
        remove_player(server, client->player);
        sprintf(str, "pdi %d\n", client->fd);
        write_to_graphic(server, str);
    }
    free_args(client);
    if (client->stream != NULL)
        fclose(client->stream);
    free_instruction(client);
    close(client->fd);
    free(client);
}

void remove_client(server_t *server, client_t *client)
{
    if (client->is_graphic)
        server->fd_graphic = 0;
    if (client->next == NULL && client->prev == NULL) {
        free_client(server, client);
        server->clients = NULL;
        return;
    }
    if (client->prev == NULL) {
        server->clients = server->clients->next;
        free_client(server, client);
        server->clients->prev = NULL;
        return;
    }
    if (client->next == NULL) {
        client->prev->next = NULL;
        free_client(server, client);
        return;
    }
    client->prev->next = client->next;
    client->next->prev = client->prev;
    free_client(server, client);
}
