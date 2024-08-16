/*
** EPITECH PROJECT, 2024
** myFtp
** File description:
** print_debug
*/

#include "server.h"

static void check_fork(server_t *server, client_t *client)
{
    char msg[10];

    if (strcmp(client->instruction, "Fork") == 0) {
        snprintf(msg, sizeof(msg), "pfk %d\n", client->fd);
        write_to_graphic(server, msg);
    }
}

static void check_incantation(server_t *server, client_t *client, int i)
{
    char msg[20] = {0};

    if (strcmp(client->instruction, "Incantation") == 0) {
        snprintf(msg, sizeof(msg), "pic %d %d %d %d\n", client->player->pos.x,
        client->player->pos.y, client->player->level, client->fd);
        write_to_graphic(server, msg);
        list_type_cmd[i].func(server, client);
    }
}

static void read_newline(server_t *server, client_t *client)
{
    long long current_time = current_time_in_milliseconds();

    print_debug("Handling command..", true);
    for (int i = 0; i < NBR_INSTRUCTION; i++) {
        if (strcmp(client->instruction, list_type_cmd[i].command) == 0) {
            check_fork(server, client);
            check_incantation(server, client, i);
            client->type_instruction[client->i_write] = i;
            for_i_write(client);
            if (client->current_instruction == false) {
                client->instruction_time = current_time;
                return;
            }
            print_debug("Command handled\n", true);
            return;
        }
    }
    print_ko(client->fd);
    printf("Unknown command [%s]\n", client->instruction);
    print_debug("Command not found\n", true);
}

void execute_command(server_t *server, client_t *client)
{
    long long current_time = current_time_in_milliseconds();
    int i = client->type_instruction[client->i_read];
    int time_needed = list_type_cmd[i].unit_time / server->params->freq;

    if (client->bloc_by_incantation == true)
        return;
    if (current_time - client->instruction_time < time_needed * 1000) {
        print_debug("Command not executed, too soon", true);
        return;
    }
    list_type_cmd[i].func(server, client);
    print_debug("Command ", false);
    print_debug(list_type_cmd[i].command, false);
    print_debug(" Executed", true);
    for_i_read(client);
    client->nb_instruction--;
    client->current_instruction = false;
    if (client->nb_instruction == 0)
        return;
    client->instruction_time = current_time;
}

static bool check_args_tab(client_t *client, char **tab)
{
    for (int i = 0; i < 3; i++) {
        if (strcmp(tab[0], cmd_with_arg[i]) == 0) {
            client->args = strdup(tab[1]);
            return false;
        }
    }
    print_ko(client->fd);
    print_error("Unknown command with argument");
    return true;
}

static int ten_instruction(client_t *client, char **tab)
{
    free(client->instruction);
    client->instruction = strdup(tab[0]);
    if (client->nb_instruction > 9) {
        printf("Player [%d] has too many instructions\n", client->fd);
        print_debug("Too many instructions", true);
        print_ko(client->fd);
        free_args(client);
        free_array(tab);
        return 1;
    }
    print_debug("Handling newline..", true);
    return 0;
}

void handle_command(server_t *server, client_t *client)
{
    char **tab = my_str_to_word_array(client->instruction, " ");
    int len_tab = len_array(tab);

    if (len_tab > 2) {
        print_ko(client->fd);
        free_array(tab);
        return;
    }
    if (len_tab == 2)
        if (check_args_tab(client, tab)) {
            free_array(tab);
            return;
        }
    if (ten_instruction(client, tab))
        return;
    read_newline(server, client);
    print_debug("Command read", true);
    free_array(tab);
}
