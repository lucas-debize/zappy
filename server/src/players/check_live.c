/*
** EPITECH PROJECT, 2024
** server
** File description:
** check_live
*/

#include "server.h"

long long current_time_in_milliseconds()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (long long)tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

static void print_dead(client_t *client)
{
    char str[1024] = {0};
    char tmp[1024] = {0};

    dprintf(client->fd, "dead\n");
    snprintf(str, sizeof(str), "Player %d died at lvl: %d\n", client->fd, client->player->level);
    strcat(str, "[ ");
    for (int i = 0; i < MAX_RESOURCES; i++) {
        snprintf(tmp, sizeof(tmp), "%s %d", resources_names[i].name,
                client->player->inventory[i]
                        .quantity);
        strcat(str, tmp);
        if (i != 6)
            strcat(str, ", ");
    }
    strcat(str, " ]\n");
    if (SHOW_INV_DEAD)
        printf("%s", str);
}

bool check_live(server_t *server, client_t *client) {
    long long now = current_time_in_milliseconds();
    long long diff;

    if (client->player == NULL)
        return true;
    diff = now - client->player->last_eat;
    if (diff > INTERVAL_LIVE * 1000 / server->params->freq) {
        if (client->player->inventory[FOOD].quantity > 0) {
            client->player->inventory[FOOD].quantity--;
            client->player->last_eat = now;
            return true;
        } else {
            print_dead(client);
            return false;
        }
    }
    return true;
}
