#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <strings.h>
#include <netinet/in.h>
#include <netdb.h>
#include <signal.h>
#include <string.h>

#include"CreatBankImage.h"
#include"ReadWriteInMyWay.h"

#include"AnalyseImage.h"
#include"strhelpers.h"

#define MAXIMAGENAME 50
#define MAXTEXT 100

#ifndef M
#define M 4
#endif

#ifndef N
#define N 256
#endif

void write_header(int sock, char * username);

