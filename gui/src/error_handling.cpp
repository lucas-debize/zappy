/*
** EPITECH PROJECT, 2023
** 2eme Année
** File description:
** error_handling.cpp
*/

#include "../include/error_handling.hpp"

int error_handling(int argc, char **argv, Config &config)
{
    if (argc != 5 && argc != 3)
        return helpcmd(84);
    if (parse_args(argc, argv, config) == 84)
        return helpcmd(84);
    return 0;
}

int parse_args(int argc, char **argv, Config &config)
{
   int opt;

   while ((opt = getopt(argc, argv, "p:h:")) != -1) {
       switch (opt) {
           case 'p':
               if (!isNumber(optarg)) {
                   std::cerr << "Error: Port number must be an integer.\n";
                   return 84;
               }
               config.port = std::stoi(optarg);
               if (!isValidPort(config.port)) {
                   std::cerr << "Error: Port number must be between 1 and 65535.\n";
                   return 84;
               }
               break;
           case 'h':
               config.host = optarg;
               break;
           default:
               std::cerr << "Error: Unknown option.\n";
               return 84;
       }
   }
   return 0;
}