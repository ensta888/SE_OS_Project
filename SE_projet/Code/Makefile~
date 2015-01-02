default: cliser

<<<<<<< HEAD
cliser: client_se.c serveur_se.c CreatBankImage.o  ReadWriteInMyWay.o strhelpers.o targa_image.o AnalyseImage.o
	gcc  -m32 -g client_se.c  targa_image.o CreatBankImage.o  ReadWriteInMyWay.o strhelpers.o -o c
	gcc  -m32 -g serveur_se.c targa_image.o CreatBankImage.o  strhelpers.o  AnalyseImage.o -o s
=======
cliser: client_se.c serveur_se.c CreatBankImage.o  ReadWriteInMyWay.o strhelpers.o targa_image.o AnalyseImage.o AnalyseRepertoire.o
<<<<<<< HEAD
	gcc  -g client_se.c  targa_image.o CreatBankImage.o  ReadWriteInMyWay.o strhelpers.o   AnalyseRepertoire.o -o c
	gcc  -g serveur_se.c targa_image.o CreatBankImage.o  AnalyseImage.o     strhelpers.o   AnalyseRepertoire.o -o s
=======
	gcc  -g client_se.c  targa_image.o CreatBankImage.o  ReadWriteInMyWay.o strhelpers.o -o c
	gcc  -g serveur_se.c targa_image.o CreatBankImage.o  strhelpers.o  AnalyseImage.o AnalyseRepertoire.o -o s
>>>>>>> fc08bc1da0cac157e83563fbfaabd3625dda130a

>>>>>>> 286e0520afef98586458bd48704844b20ad1f864

AnalyseRepertoire.o: AnalyseRepertoire.c
	gcc -g -c AnalyseRepertoire.c -o AnalyseRepertoire.o

strhelpers.o: strhelpers.c
	gcc -m32 -g -c strhelpers.c -o strhelpers.o

ReadWriteInMyWay.o: ReadWriteInMyWay.c
	gcc -m32 -g -c ReadWriteInMyWay.c -o ReadWriteInMyWay.o

AnalyseImage.o: AnalyseImage.c targa_image.o
	gcc -m32 -g -c AnalyseImage.c targa_image.o -o AnalyseImage.o

CreatBankImage.o: CreatBankImage.c targa_image.o
	gcc -m32 -g -c CreatBankImage.c targa_image.o -o CreatBankImage.o

targa_image.o: targa_image.c
	gcc -m32 -g -c targa_image.c -o targa_image.o

clean:
	rm *.o, c, s
