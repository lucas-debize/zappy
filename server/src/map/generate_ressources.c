/*
** EPITECH PROJECT, 2024
** server
** File description:
** generate_ressources
*/

#include <math.h>
#include "server.h"

int rand_range(int min, int max) {
    return random() % (max - min + 1) + min;
}

void refill_resource(map_t *map, int type, int quantity)
{
    int size = map->width * map->height;
    int x;
    int y;

    for (int i = quantity; i < map->all_resources[type].density * size; i++) {
        x = rand_range(0, map->width - 1);
        y = rand_range(0, map->height - 1);
        map->slots[y][x].resources[type].quantity++;
        map->slots[y][x].resources[type].name = map->all_resources[type].name;
        map->all_resources[type].quantity++;
        usleep(1000);
    }
}

void generate_resources(map_t *map)
{
    print_debug("Generating resources", true);
    if (DEBUG == true)
        print_resources(map);
    print_debug("Resources generated", true);
    for (int i = 0; i < MAX_RESOURCES; i++)
        refill_resource(map, i, map->all_resources[i].quantity);
}

void check_empty_resources(map_t *map)
{
    for (int i = 0; i < MAX_RESOURCES; i++)
        if (map->all_resources[i].quantity <= 0) {
            refill_resource(map, i, map->all_resources[i].quantity);
        }
}
