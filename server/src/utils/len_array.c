/*
** EPITECH PROJECT, 2024
** server
** File description:
** len_array
*/

#include "server.h"

int len_array(char **array)
{
    int i = 0;
    for (; array[i]; i++);
    return i;
}
