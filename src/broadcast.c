/*
** EPITECH PROJECT, 2019
** NWP_myarpspoof_2018
** File description:
** broadcast
*/

#include <sys/types.h>
#include <ifaddrs.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <regex.h>
#include <string.h>
#include "my_arp_spoof.h"

struct sockaddr_in get_broadcast_ip(const char *iface)
{
    struct ifaddrs *addr = NULL;
    struct ifaddrs *tmp = NULL;
    struct sockaddr_in *in = NULL;

    if (getifaddrs(&addr) == -1)
        return (*in);
    for (tmp = addr; tmp != NULL; tmp = tmp->ifa_next)
        if (!strcmp(iface, tmp->ifa_name) && tmp->ifa_addr->sa_family ==
        AF_INET)
            break;
    in = (struct sockaddr_in *)tmp->ifa_broadaddr;
    freeifaddrs(addr);
    return (*in);
}