/*
** EPITECH PROJECT, 2024
** server
** File description:
** free_args
*/

#include "server.h"

void free_instruction(client_t *client)
{
    if (client->instruction != NULL) {
        free(client->instruction);
        client->instruction = NULL;
    }
}
