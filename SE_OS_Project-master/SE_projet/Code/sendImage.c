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
#include <fcntl.h>
#include "strhelpers.h"
#define MAXNAME 10
#define MAXTEXT 100

void send_img(int socket_service, char * filename) {
	int written_size;
	int fd = open(filename, O_RDONLY);
	long img_size = lseek(fd, 0L, SEEK_END);
	lseek(fd, 0L, SEEK_SET);
	char *buffer = malloc(img_size);
	int readinfile = read(fd, buffer, img_size);
	close(fd);
	write(socket_service, &img_size, sizeof(long)); 
	printf("Taille de l'image : %ld\n", img_size);
	do {
		written_size = write(socket_service, buffer,img_size);
		printf("Envoi termine. Taille (octets): %ld. Lu = %d, Envoye = %d\n", 
					 img_size, readinfile, written_size);
	} while (written_size<img_size && written_size<=0);
	printf("Envoi termine : %d.\n", written_size);
}






