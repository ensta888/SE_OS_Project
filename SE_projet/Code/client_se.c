#include"client_se.h"
//ip 172.20.10.2

void write_header(int sock, char * username) {
	int loglen = strlen(username);
	write(sock, &loglen, sizeof(int));
	write(sock, username, sizeof(char)*loglen);
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
	char * argtab[10];
	int i;
	int nbOfArgTab;
	for(i=0;i<10;i++){
		argtab[i]=(char *) malloc(sizeof(char)*10);
	}

	int his[M][N];
	memset(his,0,sizeof(his));
	const char * acq="acquerir";
	const char * aff="afficher";
	const char * quit="quitter";
	const char * end="\n";

	write_header(sock,username);
	while(1){
		input=readInMyWay(); // ici on enleve les espaces dans la tete et a la fin
		//scanf("%s",input);	
		if (strcmp(input,acq)==0){ //acquerir
			write(sock,acq,sizeof(char)*strlen(acq));
			write(sock,end,sizeof(char)*strlen(end));
			printf ("you had demanded acquerir\n");
			int nb=0;
			read(sock, &nb, sizeof(int));
			if (nb==0 || nb==1) printf("There are %d image\n",nb);
			else printf ("There are %d images\n",nb);
		}else{
			if (strcmp(input,aff)==0){//afficher 
				write(sock,aff,sizeof(char)*strlen(aff));
				write(sock,end,sizeof(char));
				printf ("you had demanded afficher\n");
			
				char *imageName_rv= (char *) malloc (sizeof(char)*MAXIMAGENAME);
				char *begImg=imageName_rv;
				char *final="final\n";
				char c;
				do{
					c = EOF;
					read(sock, &c, sizeof(char));
					printf ("%c",c);
					*imageName_rv = c;
					imageName_rv++;
					if (c == '\n' || c == EOF){
						*imageName_rv = '\0';
						imageName_rv = begImg;
						printf ("imageName is %s",imageName_rv);
						if (strcmp(final,imageName_rv)!=0)
							printf ("filename is %s",imageName_rv);
						else break;
					}
				}
				while (c!=EOF);
				printf ("afficher finished!\n");
			}else{
				if (strcmp(input,quit)==0){ //quitter
					write(sock,quit,sizeof(char)*strlen(quit));
					write(sock,end,sizeof(char)*strlen(end));
					break;
				}else{
/*
	pour chaque histo de couleur dans l'image, le command est "histogramme+filename+couleur(R ou G ou B)";
	pour tous les histos dans la meme figure, le command est "histogramme+filename+RGB"(si pour les deux, on remplace "RGB" par "RG");
	pour les trois rectangles, le command est "histogramme+filename+rect3 "
*/
					if (startswith("histogramme",input)){//histogramme filename
						nbOfArgTab=str_split(input,argtab);
						if (nbOfArgTab!=3){
							perror("Number of arguments error");
							//ajouter une fonction d'aide qui afficher des commands utils 								//il faut verfier si tous les commands sont corrects!!!
						}else{

							int j;
							histogramme(argtab[1], *his,M,N);
							for (i=0;i<3;i++){
								for (j=0;j<256;j++){
									printf ("%d ",his[i][j]);
								}
								printf ("\n");
							}

						}
					}else{
						perror("Command does not exist");
						
						printf ("If you need some help, please input \"help\"\n");
					}
				}
			}
		}
	}

	return 0;
}

