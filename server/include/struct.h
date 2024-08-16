/*
** EPITECH PROJECT, 2024
** server
** File description:
** struct
*/

#ifndef STRUCT_H
    #define STRUCT_H
    #include <stdbool.h>
    #include <netinet/in.h>

typedef struct params_s {
    char **argv;
    char *team_names[MAX_TEAM];
    int argc;
    int port;
    int width;
    int height;
    int team_max;
    int player_max_no_egg;
    int freq;
    int auto_start;
    int display_egg;
} params_t;

typedef struct socket_s {
    int fd;
    struct sockaddr_in address;
} socket_t;

typedef struct client_s {
    player_t *player;
    int fd;

    bool is_graphic;
    bool current_instruction;
    bool bloc_by_incantation;
    char *instruction;
    char *args;
    int type_instruction[MAX_INSTRUCTION];
    int i_read;
    int i_write;
    int nb_instruction;
    long long instruction_time;
    FILE *stream;
    struct client_s *next;
    struct client_s *prev;
} client_t;

typedef struct slot_s {
    resources_t resources[7];
    int nb_players;
    int nb_eggs;
    egg_t *eggs; //TODO: eject eggs / optimisation pas urgent
    client_t *client; //TODO: implement for eject and for incantation
} slot_t;

typedef struct map_s {
    int width;
    int height;
    resources_t all_resources[7];
    slot_t **slots;
    long long regen_time;
} map_t;

typedef struct server_s {
    int nbr_clients;
    int max_fd;

    int nb_players;
    int nb_teams;
    int fd_graphic;
    bool is_running;
    fd_set readfds;
    map_t *map;
    client_t *clients;
    team_t teams[MAX_TEAM];
    params_t *params;
    socket_t socket;
    long long last_graphic_tick;
    long long last_tick;
} server_t;

#endif //STRUCT_H
