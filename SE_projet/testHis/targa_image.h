#include <stdint.h>



/* 
 A simplified targa header.
*/
#ifndef _targa_header
#define _targa_header
typedef struct targa_header_ {
  uint8_t  idlength;
  uint8_t  colourmaptype;
  uint8_t  datatypecode;
  uint8_t useless[9];
  uint16_t width;
  uint16_t height;
  uint8_t useless2[2];
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
