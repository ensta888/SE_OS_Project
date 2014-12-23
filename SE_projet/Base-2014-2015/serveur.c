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

void read_header(int sock, char * username);
void print_msg(char *talker, char * chat);
void send_img(int socket);
void transforme_image(char * argtab[]);


int main(int argc, char * argv[])
{
  int socket_RV, socket_service, socket_talk, socket_RV_talk;
  int pidFils;
  int port;
  int talkport = 1111; // Fixe
  char nom[30];
  char commandeWrite[80];
  struct sockaddr_in adr, adresse;
  socklen_t lgadresse=0;
  if (argc!=2)
  {
    fprintf(stderr,"Usage : %s port-number\n", argv[0]);
    exit(1);
  }

  if (gethostname(nom, 30)==-1) 
  {
    perror("Impossible de recuperer le nom de l'hote");
    exit(1);
  }
  /* ----------------------------------------------------------- 
   * Connexion pour la manipulation distante d'images 
   * ----------------------------------------------------------- */ 
  if ((socket_RV=socket(AF_INET, SOCK_STREAM, 0)) ==-1)
  {
    perror("socket rendez-vous");
    exit(1);
  }

  // Construction de l'adresse
  port = atoi(argv[1]);
  adr.sin_family=AF_INET;
  adr.sin_port=htons(port);
  adr.sin_addr.s_addr = htonl(INADDR_ANY);
  // Liaison
  if (bind(socket_RV, (struct sockaddr *) &adr, sizeof(adr))==-1)
  {
    perror("Impossible d'etablir une liaison");
    exit(1);
  }
  // Ecoute
  if (listen(socket_RV,1)==-1)
  {
    perror("Impossible d'ecouter");
    exit(1);
  }
  socket_service=accept(socket_RV, (struct sockaddr *)&adresse, &lgadresse);
  close(socket_RV);
  printf("Connexion service etablie. User: %s - %d; Machine: %s\n", getlogin(), geteuid(), nom);

  /* ----------------------------------------------------------- 
   * Connection pour parler et echanger des donnees textuelles 
   * ----------------------------------------------------------- */
  if ((socket_RV_talk=socket(AF_INET, SOCK_STREAM, 0)) ==-1) {
    perror("socket rendez-vous");
    exit(1);  
  }
  // Construction de l'adresse
  adr.sin_family=AF_INET;
  adr.sin_port=htons(talkport);
  adr.sin_addr.s_addr = htonl(INADDR_ANY);
  // Liaison
  if (bind(socket_RV_talk, (struct sockaddr *) &adr, sizeof(adr))==-1) {
    perror("Impossible d'etablir une liaison");
    exit(1);
  }
  // Ecoute
  if (listen(socket_RV_talk,1)==-1) {
    perror("Impossible d'ecouter");
    exit(1);
  }
  socket_talk=accept(socket_RV_talk, (struct sockaddr *)&adresse, &lgadresse);
  close(socket_RV_talk);

  printf("Connexion talk etablie sur machine: %s\n", nom);


  char c = 'X';
  char *talker = (char*)malloc(MAXNAME);
  char *chat =  (char*)malloc(MAXTEXT);
  char *begchat;
  FILE * fp;
  ssize_t csize;
  read_header(socket_talk, talker);
  printf("%s is connected\n", talker);
  char cwrite;
  while(c!=EOF) {
		begchat = chat;
		printf("J'attends \n");
		do {
			read(socket_talk, &c, 1);
			*chat = c;
			chat++;
		} while (c!='\n');
		*(chat) = '\0';
		chat = begchat;
		print_msg(talker, chat);

		if (startswith("envoie",chat)) {
			printf("Je vais t'envoyer une image\n");
			send_img(socket_service);
		}	
		else if (startswith("info", chat)) {
			do
			{
				cwrite=getchar();
				write(socket_talk, &cwrite, 1);
			}
			while (cwrite!='\n'); 
		}
		else {
			printf("Rien de special\n");
		}
  }
  close(socket_service);
  close(socket_talk);	  
  return 0;
}


void send_img(int socket_service) {
  int written_size;
  int fd = open("./img_src/ensta.tga", O_RDONLY);
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


void print_msg(char *talker, char * chat) {
  fprintf(stdout, "%s-dit-au-serveur:%s.\n", talker, chat);
  fflush(stdout);
}

void read_header(int sock, char * username) {
  int loglen ;
  read(sock, &loglen, 1);
  read(sock, username, loglen);
}



