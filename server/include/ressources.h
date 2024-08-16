/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** ressources
*/

#ifndef RESSOURCES_H
    #define RESSOURCES_H

typedef enum resources_type {
    FOOD,
    LINEMATE,
    DERAUMERE,
    SIBUR,
    MENDIANE,
    PHIRAS,
    THYSTAME
} resources_type_t;

typedef struct resources_s {
    char *name;
    int quantity;
    double density;
    resources_type_t type;
} resources_t;

extern const resources_t resources_names[MAX_RESOURCES];

#endif //RESSOURCES_H
