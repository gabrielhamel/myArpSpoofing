/*
** EPITECH PROJECT, 2019
** NWP_myarpspoof_2018
** File description:
** main
*/

#include "my_arp_spoof.h"

int main(int ac, char **av)
{
    arg_t arg = {0};

    if (parsing(&arg, ac, av) == -1) {
        usage(av[0]);
        return (EXIT_FAILURE);
    }
    return (EXIT_SUCCESS);
}