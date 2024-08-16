/*
** EPITECH PROJECT, 2024
** server
** File description:
** forward
*/

#include "server.h"

void change_quantities(server_t *server, slot_t *slot, int i, client_t *client)
{
    slot->resources[i].quantity++;
    server->map->all_resources[i].quantity++;
    client->player->inventory[i].quantity--;
    print_ok(client->fd);
}

void handle_set(server_t *server, client_t *client)
{
    slot_t *slot = &server->map->slots[client->player->pos.y]
        [client->player->pos.x];
    char msg[10] = "";

    if (client->args == NULL)
        return (print_ko(client->fd));
    for (int i = 0; i < MAX_RESOURCES; i++) {
        if (slot->resources[i].name != NULL
        && strcmp(slot->resources[i].name, client->args) == 0
        && client->player->inventory[i].quantity > 0) {
            change_quantities(server, slot, i, client);
            snprintf(msg, sizeof(msg), "pdr %d %d\n",
                client->fd, slot->resources[i].type);
            write_to_graphic(server, msg);
            free_args(client);
            return;
        }
    }
    free_args(client);
    print_ko(client->fd);
}
