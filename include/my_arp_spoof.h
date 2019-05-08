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
#include "error.h"

typedef struct {
    char *src_ip;
    char *dest_ip;
    char *iface;
    bool print_broadcast;
    bool print_spoof;
    char *mac_addr;
} arg_t;

int parsing(arg_t *arg, int ac, char **av);
void usage(const char *name);
struct sockaddr_in get_broadcast_ip(const char *iface);
int get_mac_addr(uint8_t *buf, const char *iface);

#endif