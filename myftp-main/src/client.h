/*
** EPITECH PROJECT, 2024
** Epitech [WSL: Ubuntu]
** File description:
** client
*/

#ifndef CLIENT_H_
    #define CLIENT_H_

    #define REP_200 "200 Command okay.\n"
    #define REP_220 "220 Service ready for new user.\n"
    #define REP_221 "221 Service closing control connection.\n"
    #define REP_230 "230 User logged in, proceed.\n"
    #define REP_250 "250 Requested file action okay, completed.\n"
    #define REP_331 "331 Please specify the password.\n"
    #define REP_421 "421 Service not available, closing control connection.\n"
    #define REP_425 "425 Can't open data connection.\n"
    #define REP_4251 "425 Can't open data connection.\n"
    #define REP_530 "530 Please login with USER and PASS.\n"
    #define REP_500 "500 Syntax error, command unrecognized.\n"
    #define REP_503 "503 Login with USER first.\n"
    #define REP_550 "550 Failed to change directory.\n"

    #include <stdint.h>


typedef struct {
    int activate;
    uint16_t port;
    char ip_adress[16];
} Port_t;

typedef struct {
    int activate;
    uint16_t port;
    char ip_adress[16];
} Pasv_t;


typedef struct clien_s {
    int _sd_client;
    int _sd_data;
    int _id;
    char *_path;
    char *_ip;
    char *command1;
    char user[64];
    int len_command;
    int connected;
    int _user_check;
    Port_t _port;
    Pasv_t _pasv;
}client_t;

#endif /* !CLIENT_H_ */
