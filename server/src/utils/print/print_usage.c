/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** print_usage
*/

#include "server.h"

void incorrect_params(params_t *params)
{
    int res = 0;
    if (params->port == -1) {
        fprintf(stderr, "Error: Missing -p port.\n");
        res = EXIT_FAILURE;
    }
    if (params->width == -1 || params->height == -1) {
        fprintf(stderr, "Error: Missing -x width or -y height.\n");
        res = EXIT_FAILURE;
    }
    if (params->player_max_no_egg == -1) {
        fprintf(stderr, "Error: Missing -c clientsNb.\n");
        res = EXIT_FAILURE;
    }
    if (params->team_max == 0) {
        fprintf(stderr, "Error: Missing -n name1 name2 ...\n");
        res = EXIT_FAILURE;
    }
    if (res == EXIT_FAILURE)
        exit(res);
}

void usage(const char *program_name)
{
    fprintf(stderr, "Usage: %s -p port -x width "\
    "-y height -n name1 name2 ... -c clientsNb "\
    "(-f freq --display-egg true/false "\
    "--auto-start on/off)\n", program_name);
}

void print_usage(params_t *params, const char *program_name)
{
    if (params->argc < 2) {
        usage(program_name);
        exit(EXIT_FAILURE);
    }
    if (strcmp(params->argv[1], "--help") == 0
        || strcmp(params->argv[1], "-h") == 0) {
        usage(program_name);
        exit(0);
    }
    usage(program_name);
    incorrect_params(params);
    validate_params(params);
    exit(EXIT_FAILURE);
}
