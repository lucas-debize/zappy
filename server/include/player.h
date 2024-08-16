/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** player
*/

#ifndef PLAYER_H
    #define PLAYER_H
    #include "ressources.h"

typedef struct player_s player_t;

typedef enum orientation_e {
    UP,
    RIGHT,
    DOWN,
    LEFT
} orientation_t;

typedef struct pos_s {
    int x;
    int y;
} pos_t;

typedef struct egg_s {
    int id;
    bool is_hatched;
    player_t *player;
    pos_t pos;
    struct egg_s *next;
} egg_t;

typedef struct team_s {
    char *team_name;
    int nb_players;
    int team_id;
    egg_t *eggs;
    int highest_level;
    int free_slots;
    int nb_eggs;
    int last_egg_id;
    int victory;
} team_t;

typedef struct player_s {
    int level;
    bool is_incanting;
    pos_t pos;
    orientation_t orientation;
    resources_t inventory[7];
    team_t *team;
    long long last_eat;
    egg_t *egg;
    int tile_x;
    int tile_y;
    int str;
} player_t;

#endif //PLAYER_H
