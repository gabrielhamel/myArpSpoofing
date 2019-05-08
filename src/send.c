/*
** EPITECH PROJECT, 2019
** NWP_myarpspoof_2018
** File description:
** send
*/

#include <string.h>
#include <stdio.h>
#include <net/ethernet.h>
#include "my_arp_spoof.h"

static size_t fill_arp(sock_t *sock, myarp_t *arp)
{
    arp->head.ar_hrd = htons(ARPHRD_ETHER);
    arp->head.ar_pro = htons(ETH_P_IP);
    arp->head.ar_hln = ETHER_ADDR_LEN;
    arp->head.ar_pln = sizeof(in_addr_t);
    arp->head.ar_op = htons(ARPOP_REQUEST);
    memcpy(arp->src_mac, sock->src_arp.sll_addr, 6);
    memcpy(arp->src_ip, &sock->src_ip.s_addr, 4);
    memcpy(arp->dest_ip, &sock->dest_ip.s_addr, 4);
    return (sizeof(myarp_t));
}

static size_t fill_eth(sock_t *sock, struct ethhdr *eth)
{
    memcpy(eth->h_source, sock->src_arp.sll_addr, ETH_ALEN);
    memcpy(eth->h_dest, sock->dest_arp.sll_addr, ETH_ALEN);
    eth->h_proto = htons(ETH_P_ARP);
    return (sizeof(struct ethhdr));
}

static void print_packet(uint8_t *packet, size_t size)
{
    for (size_t i = 0; i < size; i++) {
        printf("%02x", packet[i]);
        if (i != size - 1)
            printf(" ");
    }
    printf("\n");
}

ssize_t send_arp(sock_t *sock, arg_t *arg)
{
    uint8_t packet[ETH_DATA_LEN] = {0};
    size_t size = 0;

    size += fill_arp(sock, (myarp_t *)(packet +
    sizeof(struct ethhdr)));
    size += fill_eth(sock, (struct ethhdr *)packet);
    if (arg->print_broadcast == true) {
        print_packet(packet, size);
        return (0);
    }
    return (sendto(sock->fd, packet, size, 0, (struct sockaddr *)
    &(sock->dest_arp), sizeof(struct sockaddr_ll)));
}