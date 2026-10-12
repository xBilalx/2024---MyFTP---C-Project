/*
** EPITECH PROJECT, 2024
** Untitled (Workspace)
** File description:
** other
*/

#include "client.h"
#include "data.h"

void init_data(int port, data_t *d, char *path)
{
    d->_max_sd = 0;
    d->_path = path;
    d->port_serveur = port;
    d->_address.sin_family = AF_INET;
    d->_address.sin_port = htons(port);
    d->_address.sin_addr.s_addr = INADDR_ANY;
    d->addrlen = sizeof(d->_address);
    d->_max_client = 32;
    d->_client_list = malloc(sizeof(client_t) * d->_max_client);
    init_data2(port, d, path);
}

char *dynamyc_buf(int fd, client_t *client)
{
    int read_max = 10;
    char *buf[read_max + 1];
    int a = 0;

    memset(buf, 0, read_max + 1);
    (a = read(fd, buf, read_max));
    client->command1 = realloc(client->command1, client->len_command + a + 1);
    if (client->command1 == NULL) {
        perror("Realloc error");
        return NULL;
    }
    memcpy(client->command1 + client->len_command, buf, a);
    client->len_command += a;
    client->command1[client->len_command] = '\0';
    return client->command1;
}

char **split_command(const char *command)
{
    char **array = malloc(sizeof(char *));
    int command_count = 0;
    char *str = strtok((char *)command, " ");

    while (str != NULL) {
        array = realloc(array, sizeof(char *) * (command_count + 1));
        array[command_count] = malloc(sizeof(char) * (strlen(str) + 1));
        strcpy(array[command_count], str);
        command_count++;
        str = strtok(NULL, " ");
    }
    array = realloc(array, sizeof(char *) * (command_count + 1));
    array[command_count] = NULL;
    return array;
}

void close_client(client_t *client, data_t *d)
{
    write(client->_sd_client, REP_221, strlen(REP_221));
    printf("\033[1;31mClient %d: déconnecté\033[0m\n", client->_id);
    close(client->_sd_client);
    client->_sd_client = 0;
    if (client->command1 != NULL)
        free(client->command1);
    client->command1 = NULL;
    client->len_command = 0;
    client->connected = 0;
    client->_user_check = 0;
    client->_path = d->_path;
    client->_port.activate = 0;
    client->_pasv.activate = 0;
    client->_sd_data = 0;
}

int client_connection_process(char **command, int size_com,
client_t *client, data_t *d)
{
    if (strcasecmp(command[0], "quit") == 0) {
        close_client(client, d);
        return 1;
    }
    if (client->_user_check == 0) {
        if (size_com == 2 && strcasecmp(command[0], "USER") == 0) {
            strcpy(client->user, command[1]);
            client->_user_check = 1;
            write(client->_sd_client, REP_331, 33);
        } else
            write(client->_sd_client, REP_530, 37);
    } else {
        if (size_com == 1 && strcasecmp(command[0], "PASS") == 0) {
            write(client->_sd_client, REP_230, strlen(REP_230));
            client->connected = 1;
        } else
            write(client->_sd_client, REP_530, 37);
    }
    return 0;
}
