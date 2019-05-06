/*
** EPITECH PROJECT, 2019
** NWP_myarpspoof_2018
** File description:
** my_arp_spoof
*/

#ifndef MY_ARP_SPOOF_H
#define MY_ARP_SPOOF_H

#include <stdbool.h>
#include "error.h"

typedef struct {
    char *src_ip;
    char *dest_ip;
    char *iface;
} arg_t;

int parsing(arg_t *arg, int ac, char **av);

#endif