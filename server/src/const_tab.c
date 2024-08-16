/*
** EPITECH PROJECT, 2024
** server
** File description:
** const_tab
*/

#include "server.h"

const resources_t resources_names[MAX_RESOURCES] = {
        {"food", 0, 0.5, FOOD},
        {"linemate", 0, 0.3, LINEMATE},
        {"deraumere", 0, 0.15, DERAUMERE},
        {"sibur", 0, 0.1, SIBUR},
        {"mendiane", 0, 0.1, MENDIANE},
        {"phiras", 0, 0.08, PHIRAS},
        {"thystame", 0, 0.05, THYSTAME}
};

const command_t list_type_cmd[NBR_INSTRUCTION] = {
        {"Forward", 7, &handle_forward},
        {"Right", 7, &handle_right},
        {"Left", 7, &handle_left},
        {"Look", 7, &handle_look},
        {"Inventory", 1, &handle_inventory},
        {"Broadcast", 7, &handle_broadcast},
        {"Connect_nbr", 0, &handle_connect_nbr},
        {"Fork", 42, &handle_fork},
        {"Eject", 7, &handle_eject},
        {"Take", 7, &handle_take},
        {"Set", 7, &handle_set},
        {"Incantation", 300, &handle_incantation},
};

const char *cmd_with_arg[3] = {
        "Take",
        "Set",
        "Broadcast",
};

const Requirements reqs[LEVELS] = {
        {0, 0, 0, 0, 0, 0, 0},
        {1, 1, 0, 0, 0, 0, 0},
        {2, 1, 1, 1, 0, 0, 0},
        {2, 2, 0, 1, 0, 2, 0},
        {4, 1, 1, 2, 0, 1, 0},
        {4, 1, 2, 1, 3, 0, 0},
        {6, 1, 2, 3, 0, 1, 0},
        {6, 2, 2, 2, 2, 2, 1}
};
