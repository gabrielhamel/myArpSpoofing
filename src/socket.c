/*
** EPITECH PROJECT, 2019
** NWP_myarpspoof_2018
** File description:
** socket
*/

#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/if_ether.h>
#include <net/ethernet.h>
#include <net/if.h>
#include <string.h>
#include <netinet/in.h>
#include "my_arp_spoof.h"

static void fill_info(sock_t *sock, arg_t *arg, uint8_t *mac)
{
    unsigned char broadcast[ETHER_ADDR_LEN] = {0xff, 0xff, 0xff, 0xff,
    0xff, 0xff};

    sock->dest_arp.sll_family = AF_PACKET;
    sock->dest_arp.sll_halen = ETHER_ADDR_LEN;
    sock->dest_arp.sll_protocol = htons(ETH_P_ARP);   
    sock->dest_arp.sll_ifindex = if_nametoindex(arg->iface);
    memcpy(sock->dest_arp.sll_addr, broadcast, ETHER_ADDR_LEN);
    memcpy(&sock->src_arp, &sock->dest_arp, sizeof(struct sockaddr_ll));
    memcpy(sock->src_arp.sll_addr, mac, ETHER_ADDR_LEN);
    inet_aton(arg->dest_ip, &sock->dest_ip);
    inet_aton(arg->src_ip, &sock->src_ip);
}

int init_socket(sock_t *sock, arg_t *arg)
{
    uint8_t mac[8] = {0};
    socklen_t size = sizeof(struct sockaddr_ll);

    if (arg->print_broadcast == false)
        sock->fd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ARP));
    if (sock->fd == -1 || get_mac_addr(mac, arg->iface) == RETURN_FAILURE)
        return (RETURN_FAILURE);
    fill_info(sock, arg, mac);
    if (arg->print_broadcast == false)
        if (bind(sock->fd, (struct sockaddr *)&sock->src_arp, size) == -1)
            return (RETURN_FAILURE);
    return (RETURN_SUCCESS);
}