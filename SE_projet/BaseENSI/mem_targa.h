#include "fun_targa.h"

/* A documenter */
void freeImage(image_desc *pdesc);
/* A documenter */
int writeImage(image_desc desc, targa_header head, char* fName);
/* A documenter */
int readImage(image_desc *pDesc, targa_header *pHeader, char * fName);
/* A documenter */
int mallocImage(image_desc *pDesc, uint16_t width, uint16_t height);
