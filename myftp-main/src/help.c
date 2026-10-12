/*
** EPITECH PROJECT, 2024
** Untitled (Workspace)
** File description:
** help
*/

void help_message_client(int fd)
{
    write(fd, "Help message.\nOn how to use the server or the meaning of", 57);
    write(fd, " a particular non-standard command. This reply is useful ", 57);
    write(fd, "only to the human user.\n", 24);
}
