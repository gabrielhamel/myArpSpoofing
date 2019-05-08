/*
** EPITECH PROJECT, 2019
** NWP_myarpspoof_2018
** File description:
** socket
*/

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <linux/if_ether.h>
#include "my_arp_spoof.h"

int init_socket(sock_t *sock, arg_t *arg)
{
    sock->fd = socket(AF_INET, SOCK_RAW, IPPROTO_RAW);//htons(ETH_P_ALL));
    if (sock->fd == -1)
        return (RETURN_FAILURE);
    if (get_mac_addr(sock->src_mac, arg->iface) == RETURN_FAILURE)
        return (RETURN_FAILURE);
    sock->src_ip.sin_addr.s_addr = inet_addr(arg->src_ip);
    sock->dest_ip.sin_addr.s_addr = inet_addr(arg->dest_ip);
    sock->src_ip.sin_family = AF_INET;
    sock->dest_ip.sin_family = AF_INET;
    return (RETURN_SUCCESS);
}