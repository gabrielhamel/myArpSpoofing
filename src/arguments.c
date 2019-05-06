/*
** EPITECH PROJECT, 2019
** NWP_myarpspoof_2018
** File description:
** arguments
*/

#include <string.h>
#include <stdio.h>
#include "my_arp_spoof.h"

void usage(const char *name)
{
    printf("Usage: %s source_ip destination_ip interface " \
    "[--printBroadcast] [--printSpoof] mac\n", name);
}

static int parse_ip_iface(arg_t *arg, char **av)
{
    for (int i = 1; i < 5; i++)
        switch (i) {
            case 1:
                arg->src_ip = av[i];
                if (is_valid_ip(av[i]))
                    return (RETURN_FAILURE);
            break;
            case 2:
                arg->dest_ip = av[i];
                if (is_valid_ip(av[i]))
                    return (RETURN_FAILURE);
            break;
            case 3:
                arg->iface = av[i];
                if (is_valid_interface(av[i]))
                    return (RETURN_FAILURE);
            break;
        }
    return (RETURN_SUCCESS);
}

int parsing(arg_t *arg, int ac, char **av)
{
    if (ac < 4 || ac > 7 || parse_ip_iface(arg, av) == RETURN_FAILURE)
        return (RETURN_FAILURE);
    for (int i = 4; i < ac; i++)
        if (!strcmp(av[i], "--printBroadcast"))
            arg->print_broadcast = true;
        else if (!strcmp(av[i], "--printSpoof") && i + 1 < ac) {
            if (is_valid_mac(av[i + 1]))
                return (RETURN_FAILURE);
            arg->print_spoof = true;
            arg->mac_addr = av[++i];
        }
        else
            return (RETURN_FAILURE);
    return (RETURN_SUCCESS);
}