/*
** EPITECH PROJECT, 2019
** NWP_myarpspoof_2018
** File description:
** send
*/

#include <linux/if_ether.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <netinet/if_ether.h>
#include "my_arp_spoof.h"

// static size_t fill_arp(sock_t *sock, struct ether_arp *arp, size_t size_payload)
// {
//     arp->arp_hrd;
//     arp->arp_pro;
//     arp->arp_hln;
//     arp->arp_pln;
//     arp->arp_op;
//     arp->arp_sha;
//     arp->arp_spa;
//     arp->arp_tha;
//     arp->arp_tpa;
//     return (sizeof(struct ether_arp));
// }

// static size_t fill_eth(sock_t *sock, struct ethhdr *eth, size_t size_payload)
// {
//     memcpy(eth->h_source, sock->src_mac, ETH_ALEN);
//     memcpy(eth->h_dest, sock->src_mac, ETH_ALEN);
//     eth->h_proto = IPPROTO_RAW;
//     return (sizeof(struct ethhdr));
// }

ssize_t send_arp(sock_t *sock)
{
    uint8_t packet[ETH_DATA_LEN] = {0};
    size_t size = 0;

    //size += fill_arp(sock, (struct ether_arp *)(packet +
    //sizeof(struct ethhdr)), size);
    
    //int no = 1;
    //setsockopt(sock->fd, IPPROTO_IP, IP_HDRINCL, &no, sizeof(int));
    // size += fill_eth(sock, (struct ethhdr *)packet, size);
    size = 5;
    memcpy(packet, "salut", 5);
    return (sendto(sock->fd, packet, size, 0, (struct sockaddr *)
    &(sock->dest_ip), sizeof(struct sockaddr_in)));
}