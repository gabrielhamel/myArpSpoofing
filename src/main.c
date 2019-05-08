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

    #include <stdio.h>
    uint8_t mac[6] = {0};
    get_mac_addr(mac, arg.iface);
    printf("%02x:%02x:%02x:%02x:%02x:%02x\n", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
    
    return (EXIT_SUCCESS);
}