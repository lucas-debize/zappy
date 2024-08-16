/*
** EPITECH PROJECT, 2024
** server
** File description:
** forward
*/

#include "server.h"

static int get_direction(int dx, int dy, int direction, player_t *receiver)
{
    if (receiver->orientation == UP) {
        if (dx == 0 && dy > 0)
            direction = 1;
        if (dx > 0 && dy > 0)
            direction = 2;
        if (dx > 0 && dy == 0)
            direction = 3;
        if (dx > 0 && dy < 0)
            direction = 4;
        if (dx == 0 && dy < 0)
            direction = 5;
        if (dx < 0 && dy < 0)
            direction = 6;
        if (dx < 0 && dy == 0)
            direction = 7;
        if (dx < 0 && dy > 0)
            direction = 8;
    }
    direction = get_right(dx, dy, direction, receiver);
    return direction;
}

static int calculate_direction(player_t *sender,
    player_t *receiver, map_t *map)
{
    int dx = receiver->pos.x - sender->pos.x;
    int dy = receiver->pos.y - sender->pos.y;
    int direction = 0;

    if (dx > map->width / 2)
        dx -= map->width;
    else if (dx < -map->width / 2)
        dx += map->width;
    if (dy > map->height / 2)
        dy -= map->height;
    else if (dy < -map->height / 2)
        dy += map->height;
    direction = get_direction(dx, dy, direction, receiver);
    return direction;
}

static int check_errors(const char *message, client_t *client)
{
    if (message == NULL) {
        print_ko(client->fd);
        free_args(client);
        return 1;
    }
    return 0;
}

static void print_all(client_t *current, int direction, char *message)
{
    char buffer[256];

    snprintf(buffer, sizeof(buffer), "message %d, %s\n",
            direction, message);
    dprintf(current->fd, "%s", buffer);
}

void handle_broadcast(server_t *server, client_t *client)
{
    int direction = 0;
    char msg[256];
    char *message = client->args;
    player_t *sender = client->player;
    client_t *current_client = server->clients;

    if (check_errors(message, client))
        return;
    while (current_client != NULL) {
        if (current_client != client && current_client->player != NULL) {
            direction = calculate_direction(sender,
            current_client->player, server->map);
            print_all(current_client, direction, message);
            snprintf(msg, sizeof(msg), "pbc %d %s\n", client->fd, message);
            write_to_graphic(server, msg);
        }
        current_client = current_client->next;
    }
    print_ok(client->fd);
    free_args(client);
}
