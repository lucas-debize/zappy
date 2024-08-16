/*
** EPITECH PROJECT, 2023
** 2eme Année
** File description:
** main.c
*/

#include "server.h"

void auto_start_option(params_t *params)
{
    if (strcmp(optarg, "on") == 0) {
        params->auto_start = 1;
    } else if (strcmp(optarg, "off") == 0) {
        params->auto_start = 0;
    } else {
        print_usage(params, params->argv[0]);
    }
}

void long_option(params_t *params)
{
    if (strcmp(optarg, "true") == 0) {
        params->display_egg = 1;
    } else if (strcmp(optarg, "false") == 0) {
        params->display_egg = 0;
    } else {
        print_usage(params, params->argv[0]);
    }
}

void n_option(params_t *params, int *team_names_index)
{
    while (optind < params->argc && params->argv[optind][0] != '-') {
        if (*team_names_index >= MAX_TEAM) {
            fprintf(stderr, "Error: Value -n must "\
            "have %d teams maximum.\n", MAX_TEAM);
            exit(EXIT_FAILURE);
        }
        params->team_names[*team_names_index] = params->argv[optind];
        (*team_names_index)++;
        optind++;
    }
    params->team_max = *team_names_index;
    for (int i = *team_names_index; i < MAX_TEAM; i++) {
        params->team_names[i] = "";
    }
}
