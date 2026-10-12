/*
** EPITECH PROJECT, 2024
** Untitled (Workspace)
** File description:
** data
*/

#ifndef DATA_H_
    #define DATA_H_

    #include <stdio.h>
    #include <string.h>
    #include <stdlib.h>
    #include <errno.h>
    #include <strings.h>
    #include <unistd.h>
    #include <arpa/inet.h>
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <stdbool.h>
    #include <netinet/in.h>
    #include <sys/time.h>
    #include <dirent.h>
    #include <errno.h>
    #include <asm-generic/socket.h>
    #include "client.h"

typedef struct data_s {
    struct sockaddr_in _address;
    socklen_t addrlen;
    char *_path;
    fd_set _readfs;
    int _max_client;
    int port_serveur;
    int _master_socket;
    int _max_sd;
    client_t *_client_list;
}data_t;

int client_connection_process(char **command, int size_com,
client_t *client, data_t *d);
char **split_command(const char *command);
void help_message_client(int fd);
void close_client(client_t *client, data_t *d);
int check_dir(const char *path);
void add_client_to_struct(data_t *d);
void add_client_to_select(data_t *d);
int set_socket(data_t *d);
#endif /* !DATA_H_ */
