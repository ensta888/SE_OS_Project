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
#include <fcntl.h>
#include "strhelpers.h"
#define MAXTEXT 1024


void receive_image(int sock, char * filename)
{
	long img_size ;	
	printf("Je vais recevoir une image\n");
	read(sock, &img_size, sizeof(long));
	printf("Taille de l'image a recevoir : %ld\n", img_size);
	recv_img(sock, img_size, filename);
}


void recv_img(int sock, long img_size,char * filename) {
	char *buffer = malloc(img_size);
	int readdata = 1;
	int total = 0;
	char *startbuffer = buffer;
	do
	{	 
		readdata = read(sock, buffer, img_size);
		buffer += readdata*sizeof(char);
		total+=readdata;
	} while (total<img_size && readdata != -1);

	buffer = startbuffer;
	printf("Copie terminee : lu %d octets , \n", total);
	int fd = open(filename, O_CREAT|O_RDWR);
	write(fd, buffer, img_size); 
	close(fd);
	free(buffer);
}





