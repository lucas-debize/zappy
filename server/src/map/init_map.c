/*
** EPITECH PROJECT, 2024
** server
** File description:
** init_map
*/

#include "server.h"

static void init_slot_resource(slot_t *slot)
{
    for (int i = 0; i < MAX_RESOURCES; i++) {
        slot->resources[i].name = resources_names[i].name;
        slot->resources[i].quantity = 0;
        slot->resources[i].type = resources_names[i].type;
    }
    slot->nb_players = 0;
    slot->nb_eggs = 0;
}

static void init_resources(map_t *map)
{
    for (int i = 0; i < MAX_RESOURCES; i++) {
        map->all_resources[i].type = resources_names[i].type;
        map->all_resources[i].quantity = 0;
        map->all_resources[i].name = resources_names[i].name;
        map->all_resources[i].density = resources_names[i].density;
    }
}

static map_t *create_map(map_t *map, int width, int height)
{
    map->width = width;
    map->height = height;
    map->slots = malloc(sizeof(slot_t *) * height);
    if (map->slots == NULL)
        return (NULL);
    for (int y = 0; y < height; y++) {
        map->slots[y] = malloc(sizeof(slot_t) * width);
        for (int x = 0; x < width; x++)
            init_slot_resource(&map->slots[y][x]);
        if (map->slots[y] == NULL)
            return (NULL);
    }
    return (map);
}

void init_map(server_t *server)
{
    map_t *map = malloc(sizeof(map_t));

    map->slots = NULL;
    map->regen_time = 0;
    server->map = create_map(map, server->params->width, server->params->height);
    if (server->map == NULL)
        print_error("Error: map creation failed");
    init_resources(map);
    generate_resources(map);
    print_debug("Map initialized", true);
}
