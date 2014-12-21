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
#define MAXTEXT 100

//ip 172.20.10.2

void write_header(int sock, char * username) {
	int loglen = strlen(username);
	write(sock, &loglen, sizeof(int));
	//printf ("%d",loglen);
	write(sock, username, sizeof(char)*loglen);
	//printf ("%s\n",username);
}


int main(int argc, char * argv[])
{
	int sock;
	int port = 8888;
	int pidFils;
	char *username;
	struct hostent * hote;
	struct sockaddr_in adr;

	if (argc!=3){
		fprintf(stderr,"Usage : %s machine port-number\n", argv[0]);
		exit(1);
	}

	if ((sock=socket(AF_INET, SOCK_STREAM, 0)) ==-1){
		perror("socket rendez-vous");
		exit(1);
	}

	hote=gethostbyname(argv[1]);
	port=atoi(argv[2]);
	username = getlogin(); /*pb : signature not conform to man doc.*/
	printf("User: %s - %d; Machine: %s\n", username, geteuid(), argv[1]);

	adr.sin_family=AF_INET;
	adr.sin_port=htons(port);
	bcopy(hote->h_addr, &adr.sin_addr.s_addr, hote->h_length);

	if (connect(sock, (struct sockaddr *)&adr, sizeof(adr))==-1){
		perror("connect");
		exit(1);
	}

//begin
	char *input=(char *) malloc(sizeof(char)*MAXTEXT);
	const char * acq="acquerir";
	//printf ("username is %s\n",username);
	write_header(sock,username);
	while(1){
		scanf("%s",input);
		//printf ("input is %s\n",input);	
		if (strcmp(input,acq)==0){
			write(sock,acq,sizeof(char)*strlen(acq));
			const char * end="\n";
			write(sock,end,sizeof(end));
			printf ("you had demanded acquerir\n");
		}
	}
/*
	char c;
	switch(pidFils=fork()) {

	case -1:
		perror("fork");
		exit(1);
	case 0:
		do{
			c = EOF;
			read(sock, &c, 1);
			putchar(c);
		}
		while (c!=EOF);
		fprintf(stderr,"Cote client: fin fils\n");
		break;
	default:
		// First message sends the name of talking user 
		write_header(sock, username);
		do{
			c=getchar();
			write(sock, &c, 1);
		}
		while (c!=EOF);

		kill(pidFils,SIGTERM);
		fprintf(stderr,"Cote client: fin pere\n");
	}
*/
	return 0;
}

