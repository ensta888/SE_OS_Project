#include <stdint.h>



/* 
 A simplified targa header.
*/
#ifndef _targa_header
#define _targa_header
typedef struct targa_header_ {
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
#endif

/* Structure for manipulating an image */
#ifndef _image_desc
#define _image_desc
typedef struct image_desc_
{
  char *fname;               /* Libellé du fichier image (path)                 */
  uint16_t width;
  uint16_t height;
  uint8_t *pRed;               /* Référence sur le plan mémoire de couleur rouge  */
  uint8_t *pBlue;              /* Référence sur le plan mémoire de couleur bleue  */
  uint8_t *pGreen;             /* Référence sur le plan mémoire de couleur verte  */
} image_desc ;
#endif

void freeImage(image_desc *pDesc);

int readImage(image_desc *pDesc, targa_header *pHead, char * fName);

int mallocImage(image_desc *pDesc, uint16_t width, uint16_t height);

int writeImage (image_desc iDesc, targa_header head, char * fName);
