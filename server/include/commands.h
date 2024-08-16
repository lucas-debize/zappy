/*
** EPITECH PROJECT, 2024
** server
** File description:
** commands
*/

#ifndef COMMANDS_H
    #define COMMANDS_H
    #include "struct.h"
    #include "player.h"
    #include "server.h"

enum command_type {
    MSZ,
    SGT,
    SST,
    BCT,
    MCT,
    TNA,
    PPO,
    PLV,
    PIN
};

// ----------------- COMMAND FOR INCANTATION -----------------------

    #define LEVELS 8

typedef struct {
    int players;
    int linemate;
    int deraumere;
    int sibur;
    int mendiane;
    int phiras;
    int thystame;
} Requirements;

extern const Requirements reqs[LEVELS];

bool player_requirement(server_t *server, client_t *client,
    Requirements req, int player_index);

// ----------------- COMMAND FOR PLAYER -----------------------
typedef struct command_s {
    char *command;
    int unit_time;
    void (*func)(server_t *server, client_t *client);
} command_t;

typedef struct graphic_command_s {
    enum command_type type;
    char *command;
    int nbr_args;
    void (*func)(server_t *server, char **tab);
} graphic_command_t;

//----------------- player ----------------------------
void handle_forward(server_t *server, client_t *client);
void handle_right(server_t *server, client_t *client);
void handle_left(server_t *server, client_t *client);
void handle_inventory(server_t *server, client_t *client);
void handle_connect_nbr(server_t *server, client_t *client);
void handle_fork(server_t *server, client_t *client);
void handle_take(server_t *server, client_t *client);
void handle_set(server_t *server, client_t *client);
void handle_look(server_t *server, client_t *client);
void handle_eject(server_t *server, client_t *client);
void handle_incantation(server_t *server, client_t *client);
void handle_broadcast(server_t *server, client_t *client);
int get_right(int dx, int dy, int direction, player_t *receiver);
void execute_command(server_t *server, client_t *client);
void player_elevation(client_t *client, server_t *server,
    int current_level);
void for_i_read(client_t *client);
void for_i_write(client_t *client);
void handle_slot(server_t *server, client_t *client,
    char *result, size_t *length);
int test_to_display(int dist, int vision_range, int i);
void string_end(char *result, size_t *length, int res);
void is_left(client_t *client, int dist, int i, server_t *server);
void is_down(client_t *client, int dist, int i, server_t *server);
void is_right(client_t *client, int dist, int i, server_t *server);
void append_tile_info(char *result, size_t *length,
    slot_t *slot, server_t *server);
void move_position(server_t *server, int x, int y, client_t *tmp);

//------------------- graphic -------------------------
void map_size(server_t *server, char **tab);
void time_unit(server_t *server, char **tab);
void modif_time_unit(server_t *server, char **tab);
void content_of_a_tile(server_t *server, char **tab);
void name_teams(server_t *server, char **tab);
void player_pos(server_t *server, char **tab);
void player_lvl(server_t *server, char **tab);
void player_inventory(server_t *server, char **tab);
void content_of_map(server_t *server, char **tab);
void setup_graphic_cmds(server_t *server);
void connection_new_player(server_t *server, client_t *client);


//------------------- utils graphic ----------------------
int write_to_graphic(server_t *server, char *msg);
player_t *get_player_by_id(server_t *server, int player_id);
char *bct_str(server_t *server, int x, int y);

extern const command_t list_type_cmd[NBR_INSTRUCTION];
extern const char *cmd_with_arg[3];

#endif //COMMANDS_H
