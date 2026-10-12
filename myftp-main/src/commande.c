/*
** EPITECH PROJECT, 2024
** Untitled (Workspace)
** File description:
** commande
*/

#include "data.h"
#include "client.h"

void command_cwd(char **command, int size_com, client_t *client)
{
    if (size_com != 2) {
        write(client->_sd_client, REP_550, strlen(REP_550));
        return;
    }
    if (check_dir(command[1]) == 0) {
        client->_path = command[1];
        write(client->_sd_client, REP_250, strlen(REP_250));
    } else {
        write(client->_sd_client, REP_550, strlen(REP_550));
    }
}

int client_command2(char **command, int size_com, client_t *client, data_t *d)
{
    if (strcasecmp(command[0], "cdup") == 0) {
        client->_path = d->_path;
        write(client->_sd_client, REP_200, strlen(REP_200));
        return 0;
    }
    if (strcasecmp(command[0], "PORT") == 0) {
        return 0;
    }
    write(client->_sd_client, REP_500, strlen(REP_500));
    return 0;
}

int client_command(char **command, int size_com, client_t *client, data_t *d)
{
    if (strcasecmp(command[0], "quit") == 0) {
        close_client(client, d);
        return 1;
    }
    if (strcasecmp(command[0], "pwd") == 0) {
        dprintf(client->_sd_client, "257 \"%s\" created.\n", client->_path);
        return 0;
    }
    if (strcasecmp(command[0], "help") == 0) {
        help_message_client(client->_sd_client);
        return 0;
    }
    if (strcasecmp(command[0], "cwd") == 0) {
        command_cwd(command, size_com, client);
        return 0;
    }
    return client_command2(command, size_com, client, d);
}

int run_command(client_t *client, data_t *d)
{
    char **command = split_command(client->command1);
    int i = 0;
    int value = 0;

    for (i = 0; command[i] != NULL; i++);
    if (i == 0)
        return 0;
    if (client->connected == 1)
        value = client_command(command, i, client, d);
    if (client->connected == 0 && value == 0)
        value = client_connection_process(command, i, client, d);
    return value;
}

void process_command(client_t *client, data_t *d)
{
    int size_commande = 0;
    char *pointeur = strstr(client->command1, "\r\n");

    if (pointeur == NULL) {
        printf("Aucune commande trouvé\n");
        return;
    } else {
        *pointeur = '\0';
        if (run_command(client, d) == 1)
            return;
        size_commande = (pointeur - client->command1) + 2;
        client->len_command -= size_commande;
        memmove(client->command1, pointeur + 2, client->len_command + 1);
        client->command1 = realloc(client->command1, client->len_command + 1);
        if (client->command1 == NULL)
            perror("Realloc error");
    }
}
