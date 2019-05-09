/*
** EPITECH PROJECT, 2019
** NWP_myarpspoof_2018
** File description:
** spoofed
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
    memcpy(arp->dest_mac, sock->dest_arp.sll_addr, 6);
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

ssize_t build_spoofed(sock_t *sock, uint8_t *buf, arg_t *arg)
{
    size_t size = 0;
    uint8_t mac[6] = {0};

    if (arg->print_spoof == true) {
        sscanf(arg->mac_addr, "%hhx:%hhx:%hhx:%hhx:%hhx:%hhx",
        &mac[0], &mac[1], &mac[2], &mac[3], &mac[4], &mac[5]);
        memcpy(&sock->dest_arp.sll_addr, mac, 6);
    }
    size += fill_arp(sock, (myarp_t *)(buf +
    sizeof(struct ethhdr)));
    size += fill_eth(sock, (struct ethhdr *)buf);
    return (size);
}