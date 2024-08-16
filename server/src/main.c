/*
** EPITECH PROJECT, 2023
** 2eme Année
** File description:
** main.c
*/

#include "server.h"

void other_validate_params(const params_t *params, int *res)
{
    if (params->freq < 2 || params->freq > 10000) {
        fprintf(stderr, "Error: Value -f must be between 2 and 10000.\n");
        *res = EXIT_FAILURE;
    }
    if (params->team_max < 1 || params->team_max > MAX_TEAM) {
        fprintf(stderr, "Error: Number of teams must be between 1 and %d.\n",
            MAX_TEAM);
        *res = EXIT_FAILURE;
    }
}

void validate_params(const params_t *params)
{
    int res = 0;

    if (params->port < 1024 || params->port > 65535) {
        fprintf(stderr, "Error: Value -p must be between 1024 and 65535.\n");
        res = EXIT_FAILURE;
    }
    if (params->width < 10 || params->width > 30
        || params->height < 10 || params->height > 30) {
        fprintf(stderr, "Error: Value -x and -y must be between 10 and 30.\n");
        res = EXIT_FAILURE;
    }
    if (params->player_max_no_egg < 1 || params->player_max_no_egg > 200) {
        fprintf(stderr, "Error: Value -c must be between 1 and 200.\n");
        res = EXIT_FAILURE;
    }
    other_validate_params(params, &res);
    if (res == EXIT_FAILURE)
        exit(res);
}

static void display_ascii_art(void)
{
    printf("  _____________________________________________________________________________________\n");
    printf(" |                                                                                    |\n");
    printf(" |   __  __               _          _            _____                               |\n");
    printf(" |  |  \\/  |             | |        ( )          |___  /                              |\n");
    printf(" |  | .  . |  ___  _   _ | |_   ___ |/  ___         / /   __ _  _ __   _ __   _   _   |\n");
    printf(" |  | |\\/| | / _ \\| | | || __| / _ \\   / __|       / /   / _` || '_ \\ | '_ \\ | | | |  |\n");
    printf(" |  | |  | ||  __/| |_| || |_ |  __/   \\__ \\     ./ /___| (_| || |_) || |_) || |_| |  |\n");
    printf(" |  \\_|  |_/ \\___| \\__,_| \\__| \\___|   |___/     \\_____/ \\__,_|| .__/ | .__/  \\__, |  |\n");
    printf(" |                                                             | |    | |      __/ |  |\n");
    printf(" |                                                             |_|    |_|     |___/   |\n");
    printf(" |____________________________________________________________________________________|\n");
    printf("\n\n");
    printf(" ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___\n");
    printf("(___(___(___(___(___(___(___(___(___(___(___(___(___(___(___(___(___(___(___(___(___(___(___)\n");
    printf("\n\n");
}

static void display_info(const params_t *params)
{
    display_ascii_art();
    printf("---------- Server General Infos ----------\n\n");
    printf("Port = %d\n", params->port);
    printf("Width = %d\n", params->width);
    printf("Height = %d\n", params->height);
    printf("Clients_nb = %d\n", params->player_max_no_egg);
    printf("Frequency: %d\n", params->freq);
    printf("Display egg: [%s]\n\n", params->display_egg ? "true" : "false");
    printf("-------------- Team Infos ---------------- \n\n");
    printf("Teams [%d]:\n\n", params->team_max);
    for (int i = 0; i < params->team_max; i++) {
        printf("name : [%s]\n", params->team_names[i]);
        printf("nb_mature_eggs : [%d]\n\n", params->player_max_no_egg);
    }
    printf("\n ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___\n");
    printf("(___(___(___(___(___(___(___(___(___(___(___(___(___(___(___(___(___(___(___(___(___(___(___)\n");
    printf("\n\n");
}

static void random_seed(void)
{
    struct timespec ts;
    if (clock_gettime(CLOCK_MONOTONIC, &ts) == -1) {
        perror("clock_gettime");
        exit(EXIT_FAILURE);
    }
    srand(ts.tv_nsec);
}

int main(int argc, char **argv)
{
    server_t server = {0};
    params_t params = {0};
    memset(&params, 0, sizeof(params_t));

    params.argc = argc;
    params.argv = argv;
    random_seed();
    if (argc <= 2)
        print_usage(&params, argv[0]);
    parse_args(&params);
    server.params = &params;
    validate_params(&params);
    init_map(&server);
    init_team(&server);
    display_info(&params);
    server_init(&server, &params);
    start_server(&server);
    destroy_server(&server);
    return 0;
}
