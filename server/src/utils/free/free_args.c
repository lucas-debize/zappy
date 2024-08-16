/*
** EPITECH PROJECT, 2024
** server
** File description:
** free_args
*/

#include "server.h"

void free_args(client_t *client)
{
    if (client->args != NULL) {
        free(client->args);
        client->args = NULL;
    }
}
