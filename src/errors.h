#ifndef ERRORS__H
#define ERRORS__H
#include <stdio.h>
#include "types.h"
#define MAX_ERRORS 13

/* PROGRAM INVOCATION */
#define MSG_ERROR_PROGRAM_INVOCATION "Modo no soportado, el primer parámetro debe ser server o client\n"
#define MSG_ERROR_SERVER_PROGRAM_INVOCATION "Uso: ./tp server <puerto>\n"
#define MSG_ERROR_CLIENT_PROGRAM_INVOCATION "Uso: ./tp client <host> <puerto>\n"

/* COMMAND INVOCATION */
#define MSG_ERROR_UNSUPPORTED_INDICES "Error en los índices. Rango soportado: [1,9]\n"
#define MSG_ERROR_UNSUPPORTED_VALUE "Error en el valor ingresado. Rango soportado: [1,9]\n"
#define MSG_ERROR_UNMODIFIABLE_CELL "La celda indicada no es modificable\n"

/* SOCKETS */
#define MSG_ERROR_SOCKET_CONNECTION "Error en la conexión.\n"
#define MSG_ERROR_SOCKET_BINDING_AND_LISTEN "Error al establecer conexiones entrantes.\n"
#define MSG_ERROR_ACCEPTING_SOCKET_CONNECTION "Error al aceptar conexión.\n"
#define MSG_ERROR_CLOSED_SOCKET "La conexión está cerrada.\n"
#define MSG_ERROR_SOCKET_SENDING "Error en el envío de datos.\n"
#define MSG_ERROR_SOCKET_RECEIVING "Error en la recepción de datos.\n"
#define MSG_ERROR_CREATING_SUDOKU "Error en la inicialización del sudoku.\n"
#define MSG_ERROR_FORMATTING_SUDOKU "Error en el formato del sudoku.\n"
#define MSG_ERROR_OPENING_FILE "No se pudo abrir el archivo.\n"

status_t print_error_msg(status_t code);
char* get_error_msg(status_t code);

#endif
