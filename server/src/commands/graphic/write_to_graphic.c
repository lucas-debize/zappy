/*
** EPITECH PROJECT, 2024
** server
** File description:
** write_to_graphic
*/

#include "server.h"
#include <errno.h>
#include <sys/stat.h>

int is_fd_valid(int fd) {
    struct stat sb;
    if (fstat(fd, &sb) == -1) {
        printf("fstat failed : [%s]\n", strerror(errno));
        return 0;
    } else {
        return 1;
    }
}

int write_to_graphic(server_t *server, char *msg)
{
    if (server->fd_graphic == 0)
        return false;
    if (!is_fd_valid(server->fd_graphic)) {
        server->fd_graphic = 0;
        return false;
    }
    if (write(server->fd_graphic, msg, strlen(msg)) == -1) {
        server->fd_graphic = 0;
        return false;
    }
    return true;
}
