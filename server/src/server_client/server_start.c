/*
** EPITECH PROJECT, 2024
** server
** File description:
** server_start
*/

#include "server.h"

static void set_fd(server_t *server)
{
    client_t *tmp = server->clients;

    FD_ZERO(&server->readfds);
    FD_SET(server->socket.fd, &server->readfds);
    while (tmp) {
        FD_SET(tmp->fd, &server->readfds);
        if (tmp->fd > server->max_fd)
            server->max_fd = tmp->fd;
        tmp = tmp->next;
    }
}

static void sigint_handler(int sig)
{
    (void)sig;
    print_debug("SIGINT received, stopping server...", true);
    printf("Server is stopping...\n");
}

static int check_time(server_t *server)
{
    long long int now = current_time_in_milliseconds();

    if (now - server->last_tick >= SERVER_TICK / server->params->freq) {
        server->last_tick = now;
    } else {
        return false;
    }
    return true;
}

void start_server(server_t *server)
{
    struct timeval tv = {0, 0};
    signal(SIGINT, SIGNAL_CAST sigint_handler);
    signal(SIGPIPE, SIG_IGN);

    print_debug("Listening for connections...", true);
    while (server->is_running) {
        tv.tv_usec = SERVER_TICK / server->params->freq;
        set_fd(server);
        if (select(server->max_fd + 1,
            &server->readfds, NULL, NULL, &tv) < 0) {
            break;
        }
        print_graphical(server);
        if (!check_time(server))
            continue;
        check_regenerate(server);
        if (FD_ISSET(server->socket.fd, &server->readfds)) {
            print_debug("Accepting new client connexion...", true);
            server_new_client_handle(server);
        }
        server_handle_clients(server);
//        check_end(server);
    }
    print_debug("Server stopped.", true);
}
