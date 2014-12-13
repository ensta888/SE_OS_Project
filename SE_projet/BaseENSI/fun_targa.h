#include <stdint.h>

#ifndef _FUN_TARGA
#define _FUN_TARGA

typedef enum { HORIZONTAL, VERTICAL, NONE } Direction;
typedef enum { BLUE, GREEN, RED, NOPLANE } Plane;

/* 
 A simplified targa header.
*/
typedef struct targa_header_ {
  uint8_t  idlength;
  uint8_t  colourmaptype;
  uint8_t  datatypecode;
  uint8_t useless[9];
  uint16_t width;
  uint16_t height;
  uint8_t useless2[2];
} targa_header;


/* Structure for manipulating an image */
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

void image_clone(image_desc i_img, image_desc * o_img);

/* Completer avec les prototypes necessaires */
