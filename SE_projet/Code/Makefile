default: cliser

cliser: client_se.c serveur_se.c CreatBankImage.o  ReadWriteInMyWay.o strhelpers.o targa_image.o
	gcc  -g client_se.c  targa_image.o CreatBankImage.o  ReadWriteInMyWay.o strhelpers.o  -o c
	gcc  -g serveur_se.c targa_image.o CreatBankImage.o   -o s


strhelpers.o: strhelpers.c
	gcc -g -c strhelpers.c -o strhelpers.o

ReadWriteInMyWay.o: ReadWriteInMyWay.c
	gcc -g -c ReadWriteInMyWay.c -o ReadWriteInMyWay.o

CreatBankImage.o: CreatBankImage.c targa_image.o
	gcc -g -c CreatBankImage.c targa_image.o -o CreatBankImage.o

targa_image.o: targa_image.c
	gcc -g -c targa_image.c -o targa_image.o

clean:
	rm *.o, c, s
