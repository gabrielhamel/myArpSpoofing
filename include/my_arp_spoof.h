/*
** EPITECH PROJECT, 2019
** NWP_myarpspoof_2018
** File description:
** my_arp_spoof
*/

#ifndef MY_ARP_SPOOF_H
#define MY_ARP_SPOOF_H

#include <stdbool.h>
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

int parsing(arg_t *arg, int ac, char **av);
void usage(const char *name);
struct sockaddr_in get_broadcast_ip(const char *iface);
int get_mac_addr(uint8_t *buf, const char *iface);
int init_socket(sock_t *sock, arg_t *arg);
ssize_t send_arp(sock_t *sock);

#endif