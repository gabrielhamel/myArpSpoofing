/*
** EPITECH PROJECT, 2019
** NWP_myarpspoof_2018
** File description:
** arguments
*/

#include <sys/types.h>
#include <ifaddrs.h>
#include <regex.h>
#include <string.h>
#include "my_arp_spoof.h"

static int is_valid_ip(const char *str)
{
    int res;
    regex_t preg = {0};
    char *str_regex = "^[0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3}$";

    if (regcomp(&preg, str_regex, REG_NOSUB | REG_EXTENDED) == -1)
        return (RETURN_FAILURE);
    res = regexec(&preg, str, 0, NULL, 0);
    regfree(&preg);
    return (res);
}

static int is_valid_interface(const char *str)
{
    struct ifaddrs *addr = NULL;
    struct ifaddrs *tmp = NULL;

    if (getifaddrs(&addr) == -1)
        return (RETURN_FAILURE);
    for (tmp = addr; tmp != NULL; tmp = tmp->ifa_next)
        if (!strcmp(str, tmp->ifa_name) && tmp->ifa_addr->sa_family
        == AF_INET)
            return (RETURN_SUCCESS);
    return (RETURN_FAILURE);
}

static int parse_ip_iface(arg_t *arg, char **av)
{
    for (int i = 1; i < 5; i++)
        switch (i) {
            case 1:
                arg->src_ip = av[i];
                if (is_valid_ip(av[i]) == RETURN_FAILURE)
                    return (RETURN_FAILURE);
            break;
            case 2:
                arg->dest_ip = av[i];
                if (is_valid_ip(av[i]) == RETURN_FAILURE)
                    return (RETURN_FAILURE);
            break;
            case 3:
                arg->iface = av[i];
                if (is_valid_interface(av[i]) == RETURN_FAILURE)
                    return (RETURN_FAILURE);
            break;
        }
    return (RETURN_SUCCESS);
}

int parsing(arg_t *arg, int ac, char **av)
{
    if (ac < 4 || ac > 7 || parse_ip_iface(arg, av) == RETURN_FAILURE)
        return (RETURN_FAILURE);
    return (RETURN_SUCCESS);
}