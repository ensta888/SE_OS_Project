newHis:targa_image.o newImage.o
	gcc -m32 -g targa_image.o newImage.o -o n

newImage.o : newImage.c
	gcc -m32 -g -c newImage.c -o newImage.o

targa_image.o: targa_image.c
	gcc -m32 -g -c targa_image.c -o targa_image.o

clean:
	rm *.o, c, s
