#include"serveur_se.h"

void print_msg(char *talker, char * chat) {
	fputs(talker, stdout);
	fputs(": ", stdout);
	fputs(chat, stdout);
	fflush(stdout);
}

void read_header(int sock, char * username) {
	int loglen ;
	read(sock, &loglen, sizeof(int));
	//printf ("loglen is %d\n",loglen);
	read(sock, username, sizeof(char)*loglen);
	//printf ("username is %s\n",username);
	//printf ("read_header finished\n");
}

int countNbOfImage(NodeImage * img){
	NodeImage * p=img;
	int count=0;
	while(p!=NULL){
		count++;
		p=p->next;
	}
	return count;
}

void handleOfCommand(char *com){
	printf ("command is %s\n",com);
	const char * acq="acquerir";
	const char * aff="afiicher";
	const char * quit="quitter";
	NodeImage * headImg=(NodeImage *)malloc(sizeof(NodeImage));
	if (strcmp(com,acq)==0){ //acquerir
		headImg=readBankImage(PathInMyPC);
		int nb=countNbOfImage(headImg);
		printf ("number is %d\n",nb);
		write(socket_service,&nb,sizeof(int));
	}else{
		if (strcmp(com,aff)==0){//afficher
			if (headImg!=NULL){
				write(socket_service,headImg,sizeof(NodeImage));
				printf ("Afficher List\n");
				//printListImage(headImg);
			}else{
				printf("Bank Image was not created\n");
			}
		}else{
			if (strcmp(com,quit)==0){//quitter
				exit(1);
			}
		}
	}
}

int main(int argc, char * argv[])
{
	int pidFils;
	int port =9999;
	char nom[30];
	char commandeWrite[80];
	struct sockaddr_in adr, adresse;
	socklen_t lgadresse;//sizeof(struct sockaddr_in);
	if (argc!=2){
		fprintf(stderr,"Usage : %s port-number", argv[0]);
		exit(1);
	}

	port = atoi(argv[1]);

	if ((socket_RV=socket(AF_INET, SOCK_STREAM, 0)) ==-1){
		perror("socket rendez-vous");
		exit(1);
	}

	if (gethostname(nom, 30)==-1){
		perror("Qui suis-je ?");
		exit(1);
	}

	printf("User: %s - %d; Machine: %s\n", getlogin(), geteuid(), nom);

	adr.sin_family=AF_INET;
	adr.sin_port=htons(port);
	adr.sin_addr.s_addr = htonl(INADDR_ANY);

	if (bind(socket_RV, (struct sockaddr *) &adr, sizeof(adr))==-1){
		perror("bind");
		exit(1);
	}

	if (listen(socket_RV,1)==-1){
		perror("listen");
		exit(1);
	}

	socket_service=accept(socket_RV, (struct sockaddr *)&adresse, &lgadresse);
	close(socket_RV);

//begin

	char *talker = (char*)malloc(MAXNAME);
	char *chat =  (char*)malloc(MAXTEXT);
	char *begchat = chat;

	
	read_header(socket_service, talker);
	printf("%s is connected\n", talker);
	
	char c;
	do{
		c = EOF;
		read(socket_service, &c, sizeof(char));
		//printf ("%c",c);
		*chat = c;
		chat++;
		if (c == '\n' || c == EOF){
			*chat = '\0';
			chat = begchat;
			printf("message is %s\n",chat);
			handleOfCommand(chat);
			//print_msg(talker, chat);
		}
	}
	while (c!=EOF);

/*
	char c;
	char *talker = (char*)malloc(MAXNAME);
	char *chat =  (char*)malloc(MAXTEXT);
	char *begchat = chat;
	switch(pidFils=fork()) {
	case -1:
		perror("fork");
		exit(1);
	case 0:

		read_header(socket_service, talker);
		printf("%s is connected\n", talker);
		do{
			c = EOF;
			read(socket_service, &c, 1);
			*chat = c;
			chat++;
			if (c == '\n' || c == EOF){
				*chat = '\0';
				chat = begchat;
				print_msg(talker, chat);
			}
		}
		while (c!=EOF);
		fprintf(stderr,"Cote serveur: fin fils\n");
		break;
	default:
		do{
			c=getchar();
			write(socket_service, &c, 1);
		}
		while (c!=EOF);

		kill(pidFils, SIGTERM);
		fprintf(stderr,"Cote serveur: fin pere\n");
	}
*/
	return 0;
}




