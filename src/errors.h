#ifndef ERRORS__H
#define ERRORS__H
#include <stdio.h>
#include "types.h"
#define MAX_ERRORS 5

#define MSG_ERROR_PROGRAM_INVOCATION "Modo no soportado, el primer parámetro debe ser server o client"
#define MSG_ERROR_SERVER_PROGRAM_INVOCATION "Uso: ./tp server <puerto>"
#define MSG_ERROR_CLIENT_PROGRAM_INVOCATION "Uso: ./tp client <host> <puerto>"

status_t print_error_msg(status_t code);

#endif
