/*
** EPITECH PROJECT, 2019
** NWP_myarpspoof_2018
** File description:
** rcv
*/

#include <string.h>
#include <net/ethernet.h>
#include "my_arp_spoof.h"

static bool is_really_eth(sock_t *sock, struct ethhdr *eth)
{
    if (eth->h_proto != htons(ETH_P_ARP))
        return (false);
    if (memcmp(eth->h_dest, sock->src_arp.sll_addr, ETH_ALEN))
        return (false);
    return (true);
}

static bool is_really_arp(sock_t *sock, myarp_t *arp)
{
    if (arp->head.ar_hrd != htons(ARPHRD_ETHER))
        return (false);
    if (arp->head.ar_pro != htons(ETH_P_IP))
        return (false);
    if (arp->head.ar_hln != ETHER_ADDR_LEN)
        return (false);
    if (arp->head.ar_pln != sizeof(in_addr_t))
        return (false);
    if (arp->head.ar_op != htons(ARPOP_REPLY))
        return (false);
    if (memcmp(arp->src_ip, &sock->dest_ip.s_addr, 4))
        return (false);
    if (memcmp(arp->dest_ip, &sock->src_ip.s_addr, 4))
        return (false);
    if (memcmp(arp->dest_mac, sock->src_arp.sll_addr, ETH_ALEN))
        return (false);
    return (true);
}

ssize_t rcv_arp(sock_t *sock, uint8_t *buf)
{
    uint8_t packet[ETH_DATA_LEN] = {0};
    ssize_t res;
    myarp_t *arp = (myarp_t *)(packet + sizeof(struct ethhdr));
    socklen_t len = sizeof(struct sockaddr_ll);

    do {
        res = recvfrom(sock->fd, packet, ETH_DATA_LEN, 0,
        (struct sockaddr *)&(sock->dest_arp), &len);
    } while (!is_really_eth(sock, (struct ethhdr *)packet) ||
    !is_really_arp(sock, arp));
    memcpy(buf, arp->src_mac, ETH_ALEN);
    memcpy(sock->dest_arp.sll_addr, buf, ETH_ALEN);
    return (res);
}