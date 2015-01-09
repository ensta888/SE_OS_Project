//source
//http://www.google.fr/url?sa=t&rct=j&q=&esrc=s&source=web&cd=9&ved=0CFIQFjAI&url=http%3A%2F%2Fwww.tjhsst.edu%2F~dhyatt%2Fsuperap%2Fcode%2Ftarga.c&ei=ahGrVNbnDNavacH1gOAO&usg=AFQjCNHJofOVDERIfuoXSFD0DbXxg0uQGA&sig2=ADgZi1tFtGe0wp59lwbE9A&bvm=bv.82001339,d.d2s

#include <stdio.h>
#include <string.h>

/* This is the format for a header of a targa file.  The header tells
   basic information about the file prior to listing the RGB data    */
#ifndef _targa_header_his
#define _targa_header_his
typedef struct targa_header_his_{
   char id_len;                 // ID Field (Number of bytes - max 255)
   char map_type;               // Colormap Field (0 or 1)
   char img_type;               // Image Type (7 options - color vs. compression)
   int  map_first;              // Color Map stuff - first entry index
   int  map_len;                // Color Map stuff - total entries in file
   char map_entry_size;         // Color Map stuff - number of bits per entry
   int  x;                      // X-coordinate of origin 
   int  y;                      // Y-coordinate of origin
   int  width;                  // Width in Pixels
   int  height;                 // Height in Pixels
   char bpp;                    // Number of bits per pixel
   char misc;                   // Other stuff - scan origin and alpha bits
} targa_header_his;
#endif

#ifndef _pixel
#define _pixel
typedef struct pixel_{
	int b;
	int g;
	int r;
}pixel;
#endif

/* This function writes the header information to the file.  The function 
   has some unusual manipulations because integers in a targa file are two 
   bytes long and characters are only one byte long.  Because Targa files 
   need to be read by machines of different architectures, arithmetic must
   be done to write the low order bytes first using MOD (%), followed by 
   the high order bytes using DIV (/) for any integers.  */
   
void writeheader(targa_header_his h, FILE *tga) 
  {
   fputc(h.id_len, tga);          // Write chars for ID, map, and image type
   fputc(h.map_type, tga);
   fputc(h.img_type, tga);
   fputc(h.map_first % 256, tga); // Write integer, low order byte first
   fputc(h.map_first / 256, tga); // Write second byte of integer, high order
   fputc(h.map_len % 256, tga);   // Another integer 
   fputc(h.map_len / 256, tga);
   fputc(h.map_entry_size, tga);  // Write a char - only one byte
   fputc(h.x % 256, tga);         // More integers
   fputc(h.x / 256, tga);
   fputc(h.y % 256, tga);
   fputc(h.y / 256, tga);
   fputc(h.width % 256, tga);     // Even more integers
   fputc(h.width / 256, tga);
   fputc(h.height % 256, tga);
   fputc(h.height / 256, tga);
   fputc(h.bpp, tga);             // Write two chars
   fputc(h.misc, tga);
}
/*
int * handleOfHis(int *his,int nb){
	int i,j;
	int sum=0;
	int his_8[3][32];
	for (j=0;j<3;j++){
		int count=0;
		for (i=0;i<256;i++){
			if (i%8==0 && i!=0){
				his_8[j][count]=sum*100/nb;
				count++;
				sum=0;
			}else{
				sum+=*(his+j*256+i);
			}
		}
	}

	return &his_8[0][0];
}
*/

void afficherHis(int *hist,int nb){
	int i,j;
	int sum=0;
	printf ("--------------histo info\n");
	for (i=0;i<3;i++){
		for (j=0;j<nb;j++){
			int a=*(hist+i*256+j);
			printf ("%d ",a);
			sum+=a;
		}
		printf ("\n");
		printf ("sum is %d \n",sum);
	}
}

void drawHisImage_main(int * his,int count_bgr,int nbOfPix) {
   printf ("count_bgr is %d\n",count_bgr);
   printf ("nbofpix is %d\n",nbOfPix);
   FILE *tga;               // Pointer to a FILE
   targa_header_his header;     // Variable of targa_header type
   int x, y;
   int i,j,k;
   
/* First, set all the fields in the header to appropriate values */
  // afficherHis(his,256);
   header.id_len = 0;          /* no ID field */
   header.map_type = 0;        /* no colormap */
   header.img_type = 2;        /* trust me */
   header.map_first = 0;       /* not used */
   header.map_len = 0;         /* not used */
   header.map_entry_size = 0;  /* not used */
   header.x = 0;               /* image starts at (0,0) */
   header.y = 0;
   header.width = 600;         /* image is 200 x 100 */
   header.height = 600;
   header.bpp = 24;            /* 24 bits per pixel */
   header.misc = 0x20;         /* scan from upper left corner */

/* Open a file for writing targa data.  Call the file "test.tga" and
      write in binary mode (wb) so that nothing is lost as characters
      are written to the file */
 
/*
   //int * his_8=handleOfHis(his,nbOfPix);
   for (i=0;i<3;i++){
	for (j=0;j<32;j++){
			printf ("%d ",*(his_8+i*32+j));
		}
	}
   tga = fopen("test.tga", "wb"); /* Write the header information  */

   writeheader(header, tga);  

   /* Write the data for a graphic that measures 100 by 200 pixels. */
//draw the background
	
	pixel pix[header.height][header.width];
	for(y = 0; y < header.height; y++){      // Create 100 Rows of Pixels 
		for(x = 0; x < header.width; x++){   // Create 200 Pixels in each Row
			/* For each pixel, write a character representing the RGB color.
			    Notice that the order that is written to the file is B-G-R.
			    This sequence just cycles through the colors in some pattern
			    but all char values must be integers between 0 and 255. */
			pix[x][y].b=255;
			pix[x][y].g=255;
			pix[x][y].r=255;
		}
	}

//draw axe x
	for (x=44;x<600-44;x++){
		pix[x][600-50].b=0;
		pix[x][600-50].g=0;
		pix[x][600-50].r=0;
	}	
//draw axe y
	for (y=50;y<600-50;y++){
		pix[44][y].b=0;
		pix[44][y].g=0;
		pix[44][y].r=0;
	}

	//afficherHis(his_8,32);
	
//draw histo his[0] blue
	int yy;
	if (count_bgr==1 || count_bgr==111){
		for (i=0;i<32;i++){
			yy=*(his+0*32+i);
			//printf ("yy is %d\n",yy);
			while(yy!=0){
				for (k=0;k<4;k++){
					pix[44+i*16+k][550-yy].b=255;
					pix[44+i*16+k][550-yy].g=0;
					pix[44+i*16+k][550-yy].r=0;
				}
				yy--;
			}
		}
	}

	
//draw histo his[1] green
	if (count_bgr==10 || count_bgr==111){
		for (i=0;i<32;i++){
			yy=*(his+1*32+i);
			//printf ("green yy is %d\n",yy);
			while(yy!=0){
				for (k=0;k<4;k++){
					pix[48+i*16+k][550-yy].b=0;
					pix[48+i*16+k][550-yy].g=255;
					pix[48+i*16+k][550-yy].r=0;
				}
				yy--;
			}
		}
	}
//draw histo his[2] red
	if (count_bgr==100 || count_bgr==111){
		for (i=0;i<32;i++){
			yy=*(his+2*32+i);
			//printf ("red yy is %d\n",yy);
			while(yy!=0){
				for (k=0;k<4;k++){
					pix[52+i*16+k][550-yy].b=0;
					pix[52+i*16+k][550-yy].g=0;
					pix[52+i*16+k][550-yy].r=255;
				}
				yy--;
			}
		}
	}



//draw the final image
	for(y = 0; y < header.height; y++){      // Create 100 Rows of Pixels 
		for(x = 0; x < header.width; x++){   // Create 200 Pixels in each Row
			fputc(pix[x][y].b % 256, tga);               // Write char for BLUE            
			fputc(pix[x][y].g % 256, tga);   // Write char for GREEN
			fputc(pix[x][y].r % 256, tga);               // Write char for RED
		}
	}

/* close the file */
   fclose(tga);

}
/*
int main(){
	int his[3][256];
	int i,j;
	for (i=0;i<3;i++){
		for (j=0;j<256;j++){
			his[i][j]=i+j;
		}
	}
	drawHisImage_main(&his[0][0],1);
	return 0;
}*/


