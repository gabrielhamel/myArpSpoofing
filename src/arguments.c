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

static int parse_one_arg(arg_t *arg, char **av, int idx)
{
    if (idx == 1) {
        arg->src_ip = av[idx];
        if (is_valid_ip(av[idx]))
            return (RETURN_FAILURE);
    }
    if (idx == 2) {
        arg->dest_ip = av[idx];
        if (is_valid_ip(av[idx]))
            return (RETURN_FAILURE);
    }
    if (idx == 3) {
        arg->iface = av[idx];
        if (is_valid_interface(av[idx]))
            return (RETURN_FAILURE);
    }
    return (RETURN_SUCCESS);
}

static int parse_ip_iface(arg_t *arg, char **av)
{
    for (int i = 1; i < 5; i++)
        if (parse_one_arg(arg, av, i) == RETURN_FAILURE)
            return (RETURN_FAILURE);
    return (RETURN_SUCCESS);
}

static int parse_optional_arg(int ac, char **av, arg_t *arg, int *idx)
{
    if (!strcmp(av[*idx], "--printBroadcast"))
        arg->print_broadcast = true;
    else if (!strcmp(av[*idx], "--printSpoof") && *idx + 1 < ac) {
        if (is_valid_mac(av[*idx + 1]))
            return (RETURN_FAILURE);
        arg->print_spoof = true;
        arg->mac_addr = av[++(*idx)];
    }
    else
        return (RETURN_FAILURE);
    return (RETURN_SUCCESS);
}


int parsing(arg_t *arg, int ac, char **av)
{
    if (ac < 4 || ac > 7 || parse_ip_iface(arg, av) == RETURN_FAILURE)
        return (RETURN_FAILURE);
    for (int i = 4; i < ac; i++)
        if (parse_optional_arg(ac, av, arg, &i) == RETURN_FAILURE)
            return (RETURN_FAILURE);
    return (RETURN_SUCCESS);
}