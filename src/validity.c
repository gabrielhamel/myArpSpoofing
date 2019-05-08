/*
** EPITECH PROJECT, 2019
** NWP_myarpspoof_2018
** File description:
** validity
*/

#include <sys/types.h>
#include <ifaddrs.h>
#include <regex.h>
#include <string.h>
#include "my_arp_spoof.h"

int is_valid_ip(const char *str)
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

int is_valid_interface(const char *str)
{
    struct ifaddrs *addr = NULL;
    struct ifaddrs *tmp = NULL;

    if (getifaddrs(&addr) == -1)
        return (RETURN_FAILURE);
    for (tmp = addr; tmp != NULL; tmp = tmp->ifa_next)
        if (!strcmp(str, tmp->ifa_name) && tmp->ifa_addr->sa_family
        == AF_INET) {
            freeifaddrs(addr);
            return (RETURN_SUCCESS);
        }
    freeifaddrs(addr);
    return (RETURN_FAILURE);
}

int is_valid_mac(const char *str)
{
    int res;
    regex_t preg = {0};
    char *str_regex = "^[\\da-fA-F]{2}:[\\da-fA-F]{2}:[\\da-fA-F]{2}:" \
    "[\\da-fA-F]{2}:[\\da-fA-F]{2}:[\\da-fA-F]{2}$";

    if (regcomp(&preg, str_regex, REG_NOSUB | REG_EXTENDED) == -1)
        return (RETURN_FAILURE);
    res = regexec(&preg, str, 0, NULL, 0);
    regfree(&preg);
    return (res);
}