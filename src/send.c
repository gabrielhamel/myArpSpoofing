/*
** EPITECH PROJECT, 2019
** NWP_myarpspoof_2018
** File description:
** send
*/

#include <string.h>
#include <netinet/if_ether.h>
#include <net/ethernet.h>
#include "my_arp_spoof.h"

static size_t fill_arp(sock_t *sock, struct ether_arp *arp)
{
    arp->arp_hrd = htons(ARPHRD_ETHER);
    arp->arp_pro = htons(ETH_P_IP);
    arp->arp_hln = ETHER_ADDR_LEN;
    arp->arp_pln = sizeof(in_addr_t);
    arp->arp_op = htons(ARPOP_REQUEST);
    memcpy(arp->arp_tha, &sock->dest_ip.s_addr, ETH_ALEN);
    return (sizeof(struct ether_arp));
}

ssize_t send_arp(sock_t *sock)
{
    uint8_t packet[ETH_DATA_LEN] = {0};
    size_t size = sizeof(struct ether_arp);

    size += fill_arp(sock, (struct ether_arp *)packet);
    return (sendto(sock->fd, packet, size, 0, (struct sockaddr *)
    &(sock->dest_arp), sizeof(struct sockaddr_ll)));
}