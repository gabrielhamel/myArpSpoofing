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
    char *str_regex = "^[0-9]{1,3},[0-9]{1,3},[0-9]{1,3}," \
    "[0-9]{1,3},[0-9]{1,3},[0-9]{1,3}$";

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

int parsing(arg_t *arg, int ac, char **av)
{
    if (ac < 4 || ac > 6)
        return (RETURN_FAILURE);
    return (RETURN_SUCCESS);
}