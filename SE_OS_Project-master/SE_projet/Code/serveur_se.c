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

NodeImage * headImage;//=(NodeImage *)malloc(sizeof(NodeImage))

void handleOfCommand(char *com){
	//printf ("command is %s\n",com);
	
	if (strcmp(com,"acquerir")==0){ //acquerir
		headImage=(NodeImage *)malloc(sizeof(NodeImage));
		headImage=readBankImage(PathInSchoolPC);
		int nb=countNbOfImage(headImage);
		printf ("Number is %d\n",nb);
		write(socket_service,&nb,sizeof(int));
	}else{
		if (strcmp(com,"afficher")==0){//afficher
			NodeImage *current=headImage;
			const char *endFile="\n";
			const char *final="final";
			if (headImage!=NULL){
				//printListImage(headImage);
				//write(socket_service,headImage,sizeof(NodeImage));
				while(current!=NULL){
					write(socket_service,current->imageName,sizeof(char)*strlen(current->imageName));
					write(socket_service,endFile,sizeof(char));	
					printf ("Sent file %s\n",current->imageName);
					current=current->next;
				}
				write(socket_service,final,sizeof(char)*strlen(final));
				write(socket_service,endFile,sizeof(char));
				printf ("Sent file finished!\n");			
				//printListImage(headImg);

			}else{
				printf("Bank Image was not created\n");
			}
		}else{
			if (strcmp(com,"quitter")==0){//quitter
				exit(1);
			}else{
				if (startswith("histogramme",com)){
					char * arg_his=convertirString(com);
					int nbarg_his;
					char * argtab_his[10];
					int i;
					int his_img[M][N];
					for(i=0;i<10;i++){
						argtab_his[i]=(char *) malloc(sizeof(char)*10);
					}
					nbarg_his=str_split(arg_his,argtab_his);
					//printf ("argtab[1] is %s\n",argtab[1]);
					//printf ("head image name is %s\n",headImage->imageName);
					//printf ("head image name is %s\n",headImage->path);
					char *hisimg=(char *)malloc(sizeof(char)*200);					
					sprintf(hisimg,"%s/%s",headImage->path,argtab_his[1]);
					printf ("filename is %s\n",hisimg);
					int count_bgr=calculBgr(argtab_his[2]);
					if (count_bgr==1 || count_bgr==10 || count_bgr==100 || count_bgr==111){
						int nbOfPix=histogramme(hisimg,* his_img,M,N);					
						drawHisImage_main(&his_img[0][0],count_bgr,nbOfPix);
						char * send_image_name="test_histo.tga";
						send_img(socket_service, send_image_name);
					}else{
						if (count_bgr==3 || count_bgr==30 || count_bgr==300){
							int cnt[3];
							//printf ("count_bgr is %d\n",count_bgr);
							for (i=0;i<3;i++){
								cnt[i]=0;
								printf ("cnt %d is %d\n",i,cnt[i]);
							}
							printf ("start\n");
							identifyColor(hisimg,cnt);
							printf ("end identify\n");
							for (i=0;i<3;i++){
								printf ("cnt is %d\n",cnt[i]);
							}
							drawHis_threeRect(cnt);
							for (i=0;i<3;i++){
								printf ("cnt is %d\n",cnt[i]);
							}		
							char * send_image_name="test_size.tga";
							send_img(socket_service, send_image_name);				
						}
					}
					for(i=0;i<10;i++){
						free(argtab_his[i]); argtab_his[i]=NULL;
					}
					free(hisimg); hisimg=NULL;
				}
				else{
					if (startswith("classifier",com)){
						char * arg_class=convertirString(com);
						int nbarg_class;
						char * argtab_class[10];
						int i;
						int his[M][N];
						int set[11];
						int num[11];
						memset(set,0,sizeof(set));
						for(i=0;i<10;i++){
							argtab_class[i]=(char *) malloc(sizeof(char)*10);
						}	
						nbarg_class=str_split(arg_class,argtab_class);	
						int nbImage=countNbOfImage(headImage);
						int len=3;
						if (strcmp(argtab_class[1],"size")==0){	
						//check if they were number							
							argStringToNb(nbarg_class,argtab_class,set);
							diviserRepertoire(headImage->path,set,num,nbarg_class-2);
							len=nbarg_class-1;
							write(socket_service,&len,sizeof(int));
							for (i=0;i<len;i++){
								printf ("set is %d, num is %d\n",set[i],num[i]);
								write(socket_service,&set[i],sizeof(int));
								write(socket_service,&num[i],sizeof(int));
							}
							
							drawHis_size(set,num,len,nbImage);
							char * send_image_name="test_size.tga";
							send_img(socket_service, send_image_name);		
						}else{
							if (strcmp(argtab_class[1],"color")==0){
						//check if it was the color
								int count_bgr=calculBgr(argtab_class[2]);
								//printf ("headImage path is %s\n",headImage->path);
								divisercolor(headImage->path,num); //num[0] blue num[1] green num[2] red
								len=3;
								write(socket_service,&len,sizeof(int));
								for (i=0;i<3;i++){
									set[i]=i;
									printf ("num is %d\n",num[i]);
									write(socket_service,&set[i],sizeof(int));
									write(socket_service,&num[i],sizeof(int));
								}
								drawHis_size(set,num,len,nbImage);
								char * send_image_name="test_size.tga";
								send_img(socket_service, send_image_name);		
							}else{
								len=-1;
								write(socket_service,&len,sizeof(int));
							}
						}
						
						
						
					}else{
						if (startswith("envoyer",com)){
							char * arg_envy=convertirString(com);
							printf ("arg_envy is %s - %s\n",arg_envy,com);
							int nbarg_envy;
							char * argtab_envy[10];
							int i;
							for(i=0;i<10;i++){
								argtab_envy[i]=(char *) malloc(sizeof(char)*10);
							}	
							nbarg_envy=str_split(arg_envy,argtab_envy);
							
							char * recv_image_name= (char *) malloc(sizeof(char)*255);
							sprintf(recv_image_name,"%s/%s",headImage->path,argtab_envy[1]);
							printf ("revc_image_name is %s\n",recv_image_name);
							receive_image(socket_service, recv_image_name);	
							printf ("head Image name is %s\n",headImage->imageName);
							headImage=updateBankImage(argtab_envy[1],headImage->path,headImage);
							printf ("Updated\n");
							int nbImage=countNbOfImage(headImage);
							printf ("head Image name in server is %s\n",headImage->imageName);
							printf ("Now there are %d images\n",nbImage);
						}
					}
				}
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
	free(talker);talker=NULL;	
	
	char c;
	do{
		c = EOF;
		read(socket_service, &c, sizeof(char));
		printf ("%c",c);
		*chat = c;
		chat++;
		if (c == '\n' || c == EOF){
			chat--;
			*chat = '\0';
			chat = begchat;
			//printf("message is %s\n",chat);
			handleOfCommand(chat);
			
		}
	}
	while (c!=EOF);
	return 0;
}





