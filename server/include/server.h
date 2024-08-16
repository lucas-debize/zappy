/*
** EPITECH PROJECT, 2024
** zappy base server header
** File description:
** server.h
*/

#ifndef SERVER_H
    #define SERVER_H

// ----------------- configuration -----------------
    #define ERROR_EXIT_PROGRAM 0
    #define DEBUG 0
    #define FD_DEBUG 2
    #define FD_ERROR 2

    #define DONT_KO_EJECT 0 // 1 to not KO player when ejected
    #define INTERVAL_REGEN 20
    #define INTERVAL_LIVE 126

    #define MAX_PLAYERS 1020
    #define MAX_CLIENT 1020
    #define MAX_TEAM 10
    #define MAX_RESOURCES 7

    #define NBR_INSTRUCTION 12
    #define NBR_GUI_CMD 9
    #define MAX_INSTRUCTION 10

    #define SERVER_TICK 4000 // 1 second
    #define FPS 60

    #define SHOW_LEVEL_UPDATES 0 // 1 to show level updates in console
    #define MIN_SHOW_LEVEL_UPDATES 3

    #define SHOW_INV_DEAD 0 // 1 to show inventory when player dies
    #define INCANTATION_REMOVED 0 // 1 to remove incantation command for other players

// ----------------- includes -----------------
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <unistd.h>
    #include <getopt.h>
    #include <stdbool.h>
    #include <map.h>
    #include <player.h>
    #include <ressources.h>
    #include <time.h>
    #include <netinet/in.h>
    #include <sys/socket.h>
    #include <sys/select.h>
    #include <sys/time.h>
    #include <signal.h>
    #include "commands.h"
    #include "struct.h"

    #ifdef __APPLE__
        #define SIGNAL_CAST (sig_t)
    #else
        #define SIGNAL_CAST (__sighandler_t)
    #endif

void destroy_server(server_t *server);

// ------------------ MAP FUNCTIONS ------------------
void init_map(server_t *server);
void destroy_map(server_t *server);

// ----------------- SERVER FUNCTIONS -----------------
void parse_args(params_t *params);
void validate_params(const params_t *params);
void long_option(params_t *params);
void auto_start_option(params_t *params);
void n_option(params_t *params, int *team_names_index);
void server_new_client_handle(server_t *server);
int create_socket(server_t *server, params_t *args_t);
void start_server(server_t *server);
int server_init(server_t *server, params_t *args);
void remove_client(server_t *server, client_t *client);
void server_handle_clients(server_t *server);
void check_end(server_t *server);

// ----------------- UTILS FUNCTIONS -----------------
void print_error(const char *error);
void print_debug(const char *debug, bool enter);
void print_usage(params_t *params, const char *program_name);
int len_array(char **array);
void print_ko(int fd);
void print_ok(int fd);
void write_to_logged_client(server_t *server, int fd, char *str);
void print_suc(int fd);
void print_sbp(int fd);
char **my_str_to_word_array(char const *str, char *delim);
void free_array(char **array);
int my_str_isnum(char const *str);
void free_args(client_t *client);
void free_instruction(client_t *client);
long long current_time_in_milliseconds();

// ----------------- player /teams -----------------
void init_team(server_t *server);
team_t *get_team(team_t *teams, char *team_name, int max_team);
int create_player(server_t *server, client_t *client, team_t *team);
bool check_live(server_t *server, client_t *client);
void remove_player(server_t *server, player_t *player);
void free_client(server_t *server, client_t *client);
void destroy_teams_eggs(server_t *server);

// ----------------- commands ----------------------
int handle_client_command(server_t *server, client_t *client);
void handle_command(server_t *server, client_t *client);
void handle_graphic_command(server_t *server, client_t *client);

#endif // SERVER_H
