/*
** EPITECH PROJECT, 2019
** NWP_myarpspoof_2018
** File description:
** broadcast
*/

#include <sys/types.h>
#include <ifaddrs.h>
#include <linux/if_ether.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <net/if.h>
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

int get_mac_addr(uint8_t *buf, const char *iface)
{
    struct ifreq req = {0};
    int sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_IP);

    strcpy(req.ifr_name, iface);
    if (ioctl(sock, SIOCGIFHWADDR, &req) == -1)
        return (RETURN_FAILURE);
    memcpy(buf, req.ifr_hwaddr.sa_data, 6);
    return (RETURN_SUCCESS);
}