/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** handle_graphic_command
*/

#include "server.h"

const graphic_command_t list_graphic_cmd[NBR_GUI_CMD] = {
        {MSZ, "msz", 1, &map_size},
        {SGT, "sgt", 1, &time_unit},
        {SST, "sst", 2, &modif_time_unit},
        {BCT, "bct", 3, &content_of_a_tile},
        {MCT, "mct", 1, &content_of_map},
        {TNA, "tna", 1, &name_teams},
        {PPO, "ppo", 2, &player_pos},
        {PLV, "plv", 2, &player_lvl},
        {PIN, "pin", 2, &player_inventory},
};

static void check_cmd_args(server_t *server, char **tab, int type)
{
    int len_tab = len_array(tab);

    if (len_tab != list_graphic_cmd[type].nbr_args) {
        print_sbp(server->fd_graphic);
        free_array(tab);
        return;
    }
    for (int i = 1; i < len_tab; i++) {
        if (my_str_isnum(tab[i]) == false) {
            print_sbp(server->fd_graphic);
            free_array(tab);
            return;
        }
    }
    list_graphic_cmd[type].func(server, tab);
    free_array(tab);
}

void handle_graphic_command(server_t *server, client_t *client)
{
    char **tab = my_str_to_word_array(client->instruction, " ");

    for (int i = 0; i < NBR_GUI_CMD; i++) {
        if (strcmp(tab[0], list_graphic_cmd[i].command) == 0) {
            check_cmd_args(server, tab, i);
            free_instruction(client);
            client->instruction = NULL;
            return;
        }
    }
    free_array(tab);
    print_suc(client->fd);
    free_instruction(client);
}
