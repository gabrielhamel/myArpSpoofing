/*
** EPITECH PROJECT, 2019
** NWP_myarpspoof_2018
** File description:
** my_arp_spoof
*/

#ifndef MY_ARP_SPOOF_H
#define MY_ARP_SPOOF_H

#include <stdbool.h>
#include <net/if_arp.h>
#include <stdint.h>
#include <netpacket/packet.h>
#include <netinet/in.h>
#include "error.h"

typedef struct {
    char *src_ip;
    char *dest_ip;
    char *iface;
    bool print_broadcast;
    bool print_spoof;
    char *mac_addr;
} arg_t;

typedef struct {
    int fd;
    struct in_addr src_ip;
    struct in_addr dest_ip;
    struct sockaddr_ll src_arp;
    struct sockaddr_ll dest_arp;
} sock_t;

typedef struct {
    struct arphdr head;
    uint8_t src_mac[6];
    uint8_t src_ip[4];
    uint8_t dest_mac[6];
    uint8_t dest_ip[4];
} __attribute__((packed)) myarp_t;

int parsing(arg_t *arg, int ac, char **av);
void usage(const char *name);
struct sockaddr_in get_broadcast_ip(const char *iface);
int get_mac_addr(uint8_t *buf, const char *iface);
int init_socket(sock_t *sock, arg_t *arg);
ssize_t send_arp(sock_t *sock, arg_t *arg);
ssize_t rcv_arp(sock_t *sock, uint8_t *buf);

#endif