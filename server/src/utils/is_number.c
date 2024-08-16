/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** is_number
*/

#include "server.h"

int my_str_isnum(char const *str)
{
    int len = strlen(str);
    int count = 0;

    for (int i = 0; (str[i] >= 48 && str[i] <= 57) && i < len; i++)
        count += 1;

    if (count == len) {
        return (1);
    }
    return (0);
}
