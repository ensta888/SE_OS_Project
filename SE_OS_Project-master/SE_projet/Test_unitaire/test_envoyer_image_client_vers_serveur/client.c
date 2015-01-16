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

// Definition des prototypes de fonctions appelees dans le fichier
void write_header(int sock, char * username);
void print_msg(char * chat);
void recv_img(int sock, long img_size);
int main(int argc, char * argv[])
{
  int sock;
  int sock_talk;
  int port;
  int port_talk = 1111;
  int pidFils;
  char *username;
  struct hostent * hote;
  struct sockaddr_in adr;

  // On verifie qu'il y a au moins 2 options donnees au lancement du client
  if (argc!=4)
  {
    fprintf(stderr,"Usage : %s machine port-number username\n", argv[0]);
    exit(1);
  }
  // Creation d'un socket pour initier le rendez-vous du client avec le serveur
  sock=socket(AF_INET, SOCK_STREAM, 0);
  if (sock == -1)
  {
    fprintf(stderr, "Socket rendez-vous n'a pu etre cree");
    exit(1);
  }
  // On recupere la structure de donnee hote a partir du nom de la machine
  hote=gethostbyname(argv[1]);
  port=atoi(argv[2]);
  username=argv[3];
  printf("User: %s - %d; Machine: %s\n", username, geteuid(), argv[1]);

  /* Connexion au service */
  // On convertit l'addresse de l'hote en type compatible avec le type de socket
  // choisi (AF_INET/SOCK_STREAM)
  adr.sin_family=AF_INET;
  adr.sin_port=htons(port);
  bcopy(hote->h_addr, &adr.sin_addr.s_addr, hote->h_length);
  // On demande a se connecter
  int connectResult = connect(sock, (struct sockaddr *)&adr, sizeof(adr));
  if (connectResult ==-1)
  {
    fprintf(stderr, "Erreur de connexion");
    exit(1);
  }


  /* Connexion au talk */
  sock_talk=socket(AF_INET, SOCK_STREAM, 0);
  if (sock == -1)
  {
    fprintf(stderr, "Socket rendez-vous pour talk n'a pu etre cree\n");
    exit(1);
  }
  // On convertit l'addresse de l'hote en type compatible avec le type de socket
  // choisi (AF_INET/SOCK_STREAM)
  adr.sin_family=AF_INET;
  adr.sin_port=htons(port_talk);
  bcopy(hote->h_addr, &adr.sin_addr.s_addr, hote->h_length);
  // On demande a se connecter
  sleep(1);
  connectResult = connect(sock_talk, (struct sockaddr *)&adr, sizeof(adr));
  if (connectResult ==-1)
  {
	perror("Erreur de connexion au talk");
    exit(1);
  }
  printf("Connexion au talk etablie\n");

  char c;
  char *chat =  malloc(MAXTEXT);
  char *begchat = chat;
  long img_size ;
  int i;
  char *msgclient = malloc(MAXTEXT);
  /* Le premier message ecrit le nom de l'utilisateur */
  write_header(sock_talk, username);
  while (c!=EOF) {
	printf("Dites moi quelque chose\n");
	i = 0;
	// Le pere produit les requetes sur sock_talk
	do
	{
	  c=getchar();
	  // Stocker la requete client pour savoir s'il faut attendre un message.
	  msgclient[i]=c;
	  write(sock_talk, &c, sizeof(char));
	  i++;
	}
	while (c!='\n');
	msgclient[i]='\0';
   	if (startswith("envoie", msgclient)) {
	  printf("Je vais recevoir une image\n");
	  read(sock, &img_size, sizeof(long));
	  printf("Taille de l'image a recevoir : %ld\n", img_size);
	  recv_img(sock, img_size);
	}
	if (startswith("transforme", msgclient)) {
	  printf("Je transforme une image : %s\n", msgclient);
	}

  }	
  close(sock);
  close(sock_talk);	   
  return 0;
}


void recv_img(int sock, long img_size) {
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
  int fd = open("output/testsortie.tga", O_CREAT|O_RDWR);
  write(fd, buffer, img_size); 
  close(fd);
  free(buffer);
}

void print_msg(char * chat) {
  fputs("reply: ", stdout);
  fputs(chat, stdout);
}

void write_header(int sock, char * username) {
  int loglen = strlen(username);
  write(sock, &loglen, sizeof(int));
  write(sock, username, sizeof(char)*loglen);
}

