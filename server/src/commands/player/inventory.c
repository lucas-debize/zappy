/*
** EPITECH PROJECT, 2024
** server
** File description:
** forward
*/

#include "server.h"

static void show_inventory(client_t *client, char *str)
{
    dprintf(client->fd, "%s", str);
    snprintf(str, 1024,
        "pin %d %d %d %d %d %d %d %d %d %d\n", client->fd,
        client->player->pos.x, client->player->pos.y,
    client->player->inventory[0].quantity,
        client->player->inventory[1].quantity,
        client->player->inventory[2].quantity,
    client->player->inventory[3].quantity,
        client->player->inventory[4].quantity,
        client->player->inventory[5].quantity,
    client->player->inventory[6].quantity);
}

void handle_inventory(server_t *server, client_t *client)
{
    char str[1024] = "";
    char tmp[1024] = "";

    strcat(str, "[ ");
    for (int i = 0; i < MAX_RESOURCES; i++) {
        snprintf(tmp, sizeof(tmp), "%s %d", resources_names[i].name,
            client->player->inventory[i].quantity);
        strcat(str, tmp);
        if (i != 6)
            strcat(str, ", ");
    }
    strcat(str, " ]\n");
    show_inventory(client, str);
    write_to_graphic(server, str);
}
