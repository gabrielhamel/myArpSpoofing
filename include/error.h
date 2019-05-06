/*
** EPITECH PROJECT, 2019
** NWP_myarpspoof_2018
** File description:
** error
*/

#ifndef ERROR_H
#define ERROR_H

#include <stdlib.h>

#ifdef EXIT_FAILURE
#undef EXIT_FAILURE
#endif

#define EXIT_FAILURE 84

#endif