/*
** EPITECH PROJECT, 2023
** 2eme Année
** File description:
** main.c
*/

#include "server.h"

void handle_long_option(params_t *params, struct option *long_options,
    int long_index)
{
    if (strcmp(long_options[long_index].name, "auto-start") == 0) {
        auto_start_option(params);
    }
    if (strcmp(long_options[long_index].name, "display-egg") == 0) {
        long_option(params);
    }
}

void process_option(params_t *params, int opt)
{
    switch (opt) {
        case 'p':
            params->port = atoi(optarg);
            break;
        case 'x':
            params->width = atoi(optarg);
            break;
        case 'y':
            params->height = atoi(optarg);
            break;
        case 'c':
            params->player_max_no_egg = atoi(optarg);
            break;
        case 'f':
            params->freq = atoi(optarg);
            break;
    }
}

void handle_short_option(params_t *params, int opt,
    int *team_names_index)
{
    if (opt == 'n') {
        optind--;
        n_option(params, team_names_index);
    } else {
        process_option(params, opt);
    }
}

void handle_args(params_t *params)
{
    int opt;
    int team_names_index = 0;
    int long_index = 0;
    static struct option long_options[] = {
        {"auto-start", required_argument, 0, 0},
        {"display-egg", required_argument, 0, 0}, {0, 0, 0, 0}
    };

    opt = getopt_long(params->argc, params->argv,
        "p:x:y:n:c:f:", long_options, &long_index);
    while (opt != -1) {
        if (opt == 0) {
            handle_long_option(params, long_options, long_index);
        } else {
            handle_short_option(params, opt, &team_names_index);
        }
        opt = getopt_long(params->argc, params->argv,
            "p:x:y:n:c:f:", long_options, &long_index);
    }
}

void parse_args(params_t *params)
{
    params->freq = 100;
    params->port = -1;
    params->width = -1;
    params->height = -1;
    params->team_max = 0;
    params->player_max_no_egg = -1;
    handle_args(params);
    if (params->port <= 0 || params->width <= 0 || params->height <= 0 ||
        params->team_max == 0 || params->player_max_no_egg <= 0
            || params->freq <= 0) {
        print_usage(params, params->argv[0]);
    }
}
