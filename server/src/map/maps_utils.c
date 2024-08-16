/*
** EPITECH PROJECT, 2024
** server
** File description:
** maps_utils
*/

#include "server.h"

void print_resources(map_t *map)
{
    for (int i = 0; i < MAX_RESOURCES; i++) {
        printf("%s: %d\n", map->all_resources[i].name, map->all_resources[i].quantity);
    }
}

void print_map(map_t *map)
{
    for (int i = 0; i < map->height; i++) {
        for (int j = 0; j < map->width; j++) {
            printf("Slot %d %d:\n", i, j);
            for (int k = 0; k < MAX_RESOURCES; k++) {
                printf("\t%s: %d\n", map->slots[i][j].resources[k].name, map->slots[i][j]
                .resources[k].quantity);
            }
        }
    }
}
