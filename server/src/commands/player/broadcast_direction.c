/*
** EPITECH PROJECT, 2024
** server
** File description:
** forward
*/

#include "server.h"

int get_left(int dx, int dy, int direction, player_t *receiver)
{
    if (receiver->orientation == LEFT) {
        if (dx > 0 && dy == 0)
            direction = 1;
        if (dx > 0 && dy < 0)
            direction = 2;
        if (dx == 0 && dy < 0)
            direction = 3;
        if (dx < 0 && dy < 0)
            direction = 4;
        if (dx < 0 && dy == 0)
            direction = 5;
        if (dx < 0 && dy > 0)
            direction = 6;
        if (dx == 0 && dy > 0)
            direction = 7;
        if (dx > 0 && dy > 0)
            direction = 8;
    }
    return direction;
}

int get_down(int dx, int dy, int direction, player_t *receiver)
{
    if (receiver->orientation == DOWN) {
        if (dx == 0 && dy < 0)
            direction = 1;
        if (dx > 0 && dy < 0)
            direction = 2;
        if (dx > 0 && dy == 0)
            direction = 3;
        if (dx > 0 && dy > 0)
            direction = 4;
        if (dx == 0 && dy > 0)
            direction = 5;
        if (dx < 0 && dy > 0)
            direction = 6;
        if (dx < 0 && dy == 0)
            direction = 7;
        if (dx < 0 && dy < 0)
            direction = 8;
    }
    direction = get_left(dx, dy, direction, receiver);
    return direction;
}

int get_right(int dx, int dy, int direction, player_t *receiver)
{
    if (receiver->orientation == RIGHT) {
        if (dx < 0 && dy == 0)
            direction = 1;
        if (dx < 0 && dy > 0)
            direction = 2;
        if (dx == 0 && dy > 0)
            direction = 3;
        if (dx > 0 && dy > 0)
            direction = 4;
        if (dx > 0 && dy == 0)
            direction = 5;
        if (dx > 0 && dy < 0)
            direction = 6;
        if (dx == 0 && dy < 0)
            direction = 7;
        if (dx < 0 && dy < 0)
            direction = 8;
    }
    direction = get_down(dx, dy, direction, receiver);
    return direction;
}
