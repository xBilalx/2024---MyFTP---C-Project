/*
** EPITECH PROJECT, 2024
** Untitled (Workspace)
** File description:
** set_serveur
*/

#include "data.h"
#include "client.h"

int check_dir(const char *path)
{
    DIR* dir = opendir(path);

    if (dir) {
        closedir(dir);
    } else if (ENOENT == errno) {
        perror("");
        return 1;
    }
    return 0;
}

int set_socket(data_t *d)
{
    int sockfd = 0;
    int new_sockfd = 0;
    int opt = 1;
    char buf[1024];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Socket failed\n");
        exit(84);
    }
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
    &opt, sizeof(opt)) == -1)
        exit(84);
    if (bind(sockfd, (struct sockaddr*)&d->_address, sizeof(d->_address)) == 1)
        exit(84);
    if (listen(sockfd, d->_max_client) == 1)
        exit(84);
    return sockfd;
}

void add_client_to_select(data_t *d)
{
    int sd = 0;

    for (int i = 0; i < d->_max_client; i++) {
        if (d->_client_list[i]._sd_client > 0)
            FD_SET(d->_client_list[i]._sd_client, &d->_readfs);
        if (d->_client_list[i]._sd_client > d->_max_sd) {
            d->_max_sd = d->_client_list[i]._sd_client;
        }
    }
}

void add_client_to_struct(data_t *d)
{
    int new_socket = 0;

    new_socket = accept(d->_master_socket,
    (struct sockaddr*)&d->_address, &d->addrlen);
    for (int i = 0; i < d->_max_client; i++) {
        if (d->_client_list[i]._sd_client == 0) {
            d->_client_list[i]._sd_client = new_socket;
            printf("\033[1;35m-> Client %d : connecté\033[0m\n",
            d->_client_list[i]._id);
            write(new_socket, REP_220, strlen(REP_220));
            return;
        }
    }
    write(new_socket, REP_421, strlen(REP_421));
    close(new_socket);
}

void init_data2(int port, data_t *d, char *path)
{
    for (int i = 0; i < d->_max_client; i++) {
        d->_client_list[i]._sd_client = 0;
        d->_client_list[i]._id = i + 1;
        d->_client_list[i].command1 = NULL;
        d->_client_list[i].len_command = 0;
        d->_client_list[i].connected = 0;
        d->_client_list[i]._user_check = 0;
        d->_client_list[i]._path = d->_path;
        d->_client_list[i]._pasv.activate = 0;
        d->_client_list[i]._port.activate = 0;
        d->_client_list[i]._sd_data = 0;
    }
}
