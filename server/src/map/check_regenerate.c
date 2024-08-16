/*
** EPITECH PROJECT, 2024
** server
** File description:
** check_regeneration
*/

#include "server.h"

void check_regenerate(server_t *server)
{
    long long now = current_time_in_milliseconds();

    check_empty_resources(server->map);
    if (now - server->map->regen_time >= (INTERVAL_REGEN / server->params->freq)) {
        print_debug("Regenerating resources in progress..", true);
        generate_resources(server->map);
        server->map->regen_time = now;
        print_debug("Resources regenerated", true);
        return;
    }
    print_debug("Regeneration not needed", true);
}
