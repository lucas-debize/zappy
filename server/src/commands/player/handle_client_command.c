/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** handle_client_command
*/

#include "server.h"

static void check_graphic(server_t *server, client_t *client)
{
    if (server->fd_graphic != 0) {
        print_ko(client->fd);
        return;
    }
    client->is_graphic = true;
    server->fd_graphic = client->fd;
    setup_graphic_cmds(server);
    server->last_graphic_tick = time(NULL);
}

void check_team_name(server_t *server, client_t *client)
{
    team_t *team = get_team(server->teams,
        client->instruction, server->nb_teams);

    if (strcmp(client->instruction, "GRAPHIC") == 0) {
        check_graphic(server, client);
        return;
    }
    if (team == NULL) {
        print_ko(client->fd);
        return;
    }
    if (create_player(server, client, team)) {
        print_ko(client->fd);
        return;
    }
    dprintf(client->fd, "%d\n%d %d\n", team->free_slots,
        server->params->width, server->params->height);
    connection_new_player(server, client);
}

int handle_client_command(server_t *server, client_t *client)
{
    size_t len;
    char *tmp = NULL;

    client->instruction = NULL;
    if (getline(&client->instruction, &len, client->stream) < 0) {
        print_debug("Client disconnected", true);
        remove_client(server, client);
        server->nbr_clients--;
        return 0;
    }
    tmp = strndup(client->instruction, strcspn(client->instruction, "\n"));
    free_instruction(client);
    client->instruction = tmp;
    if (client->is_graphic) {
        handle_graphic_command(server, client);
        return 1;
    }
    if (client->player == NULL) {
        check_team_name(server, client);
        free_instruction(client);
        return 1;
    }
    handle_command(server, client);
    free_instruction(client);
    return 1;
}
