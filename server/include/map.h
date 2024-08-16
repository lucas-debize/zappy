/*
** EPITECH PROJECT, 2024
** server
** File description:
** map
*/

#ifndef MAP_H
    #define MAP_H
    #include "ressources.h"
    #include "player.h"
    #include "struct.h"

void generate_resources(map_t *map);
void print_resources(map_t *map);
void print_map(map_t *map);
void check_regenerate(server_t *server);
void check_empty_resources(map_t *map);

void add_back_egg(server_t *server, team_t *team, int egg_id);
void print_graphical(server_t *server);
#endif //MAP_H
