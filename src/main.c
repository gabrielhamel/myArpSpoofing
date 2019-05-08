/*
** EPITECH PROJECT, 2019
** NWP_myarpspoof_2018
** File description:
** main
*/

#include <stdio.h>
#include "my_arp_spoof.h"

int main(int ac, char **av)
{
    arg_t arg = {0};
    sock_t sock = {0};

    if (parsing(&arg, ac, av) == RETURN_FAILURE) {
        usage(av[0]);
        return (EXIT_FAILURE);
    }
    if (init_socket(&sock, &arg) == RETURN_FAILURE)
        return (EXIT_FAILURE);
    printf("%ld\n", send_arp(&sock));
    return (EXIT_SUCCESS);
}