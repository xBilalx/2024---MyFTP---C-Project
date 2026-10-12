/*
** EPITECH PROJECT, 2024
** bilux [WSL: Ubuntu]
** File description:
** main
*/

#include "client.h"
#include "data.h"

void clients_request(int i, data_t *d)
{
    if (FD_ISSET(d->_client_list[i]._sd_client, &d->_readfs)) {
        dynamyc_buf(d->_client_list[i]._sd_client, &d->_client_list[i]);
        process_command(&d->_client_list[i], d);
        if (d->_client_list[i].command1 != NULL)
            printf("%s\n", d->_client_list[i].command1);
    }
}

int run_serveur(int ar, char *argc[])
{
    data_t *d = malloc(sizeof(data_t));
    struct sockaddr_in address;

    init_data(atoi(argc[1]), d, argc[2]);
    d->_master_socket = set_socket(d);
    while (1) {
        FD_ZERO(&d->_readfs);
        FD_SET(d->_master_socket, &d->_readfs);
        d->_max_sd = d->_master_socket;
        add_client_to_select(d);
        select(d->_max_sd + 1, &d->_readfs, NULL, NULL, NULL);
        if (FD_ISSET(d->_master_socket, &d->_readfs)) {
            add_client_to_struct(d);
        }
        for (int i = 0; i < d->_max_client; i++)
            clients_request(i, d);
    }
}

void help_message(char *bin)
{
    printf("USAGE: %s port path\n       ", bin);
    printf("port is the port number on which the server socket listens\n");
    printf("       path is the path to the home directory for the ");
    printf("Anonymous user\n");
}

int check_arg(int ar, char *argc[])
{
    int port_num = 0;

    if (ar != 3) {
        help_message(argc[0]);
        return 1;
    }
    port_num = atoi(argc[1]);
    if (port_num < 1 || port_num > 65535) {
        printf("Error: port value is not valide.\n");
        return 1;
    }
    return check_dir(argc[2]);
}

int main(int ar, char *argc[])
{
    int error = 0;

    error = check_arg(ar, argc);
    if (error)
        return 84;
    run_serveur(ar, argc);
}
