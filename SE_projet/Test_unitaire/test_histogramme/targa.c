/* TARGA.C -- a demonstration of how to use 24-bit RGB uncompressed Targa file
   Original program written by Grant Emery, now a student at MIT.  */

#include <stdio.h>

/* This is the format for a header of a targa file.  The header tells
   basic information about the file prior to listing the RGB data    */

typedef struct {
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
} targa_header;



/* This function writes the header information to the file.  The function 
   has some unusual manipulations because integers in a targa file are two 
   bytes long and characters are only one byte long.  Because Targa files 
   need to be read by machines of different architectures, arithmetic must
   be done to write the low order bytes first using MOD (%), followed by 
   the high order bytes using DIV (/) for any integers.  */
   
void writeheader(targa_header h, FILE *tga) 
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


int main(void) {
   FILE *tga;               // Pointer to a FILE
   targa_header header;     // Variable of targa_header type
   int x, y;

/* First, set all the fields in the header to appropriate values */
   header.id_len = 0;          /* no ID field */
   header.map_type = 0;        /* no colormap */
   header.img_type = 2;        /* trust me */
   header.map_first = 0;       /* not used */
   header.map_len = 0;         /* not used */
   header.map_entry_size = 0;  /* not used */
   header.x = 0;               /* image starts at (0,0) */
   header.y = 0;
   header.width = 200;         /* image is 200 x 100 */
   header.height = 100;
   header.bpp = 24;            /* 24 bits per pixel */
   header.misc = 0x20;         /* scan from upper left corner */

/* Open a file for writing targa data.  Call the file "test.tga" and
      write in binary mode (wb) so that nothing is lost as characters
      are written to the file */

   tga = fopen("test.tga", "wb"); /* Write the header information  */

   writeheader(header, tga);  

   /* Write the data for a graphic that measures 100 by 200 pixels. */

   for(y = 0; y < 100; y++)      // Create 100 Rows of Pixels 
      for(x = 0; x < 200; x++)   // Create 200 Pixels in each Row

       { /* For each pixel, write a character representing the RGB color.
            Notice that the order that is written to the file is B-G-R.
            This sequence just cycles through the colors in some pattern
            but all char values must be integers between 0 and 255. */

        fputc((4*y)%256, tga);               // Write char for BLUE            
        fputc(255 - (x*2 + y*2)%256, tga);   // Write char for GREEN
        fputc((3*x)%256, tga);               // Write char for RED
       }

/* close the file */
   fclose(tga);

/* that was easy, right? */
   return 0;
}


