#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <signal.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include"CreatBankImage.h"

#define MAXNAME 10
#define MAXTEXT 100

int socket_RV, socket_service;

void print_msg(char *talker, char * chat);

void read_header(int sock, char * username);

int conutNbOfImage(NodeImage * img);

void handleOfCommand(char *com);
