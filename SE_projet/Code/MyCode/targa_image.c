#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include"targa_image.h"


void freeImage(image_desc *pDesc)
{
  free (pDesc->pBlue); pDesc->pBlue = NULL;
  free (pDesc->pGreen); pDesc->pGreen = NULL;
  free (pDesc->pRed); pDesc->pRed = NULL;
}

int readImage(image_desc *pDesc, targa_header *pHead, char * fName)
{
  FILE * fDesc;
  int i;
  targa_header head;
  /* Open fDesc file */
  fDesc = fopen(fName,"r");

  /* Lecture du header */
  fread(pHead, sizeof(targa_header), 1, fDesc);
  head = *pHead; // on le met dans une vari. temporarire pour faciliter l'acces aux champs

/*
  printf("[mem_targa] Header : %u %u %u %u %u\n", head.idlength, head.colourmaptype, head.datatypecode, head.width, head.height);
*/
  // Initialisation de la structure image
  pDesc->width = head.width;
  pDesc->height = head.height;
  pDesc->pRed   = malloc(sizeof(uint8_t)*head.width*head.height);
  pDesc->pGreen = malloc(sizeof(uint8_t)*head.width*head.height);
  pDesc->pBlue  = malloc(sizeof(uint8_t)*head.width*head.height);

  // Remplir pixel par pixel les 3 couches de couleurs
  for (i=0; i<head.width*head.height; i++) {
	// read 1 int : blue
	fread(pDesc->pBlue+i, sizeof(uint8_t), 1, fDesc);
	// read 1 int : green
	fread(pDesc->pGreen+i, sizeof(uint8_t), 1, fDesc);
	// read 1 int : red
	fread(pDesc->pRed+i, sizeof(uint8_t), 1, fDesc);
  }
  return 1;
  
}

int mallocImage(image_desc *pDesc, uint16_t width, uint16_t height)
{
  // Note : test of memory failures are omitted here.
  int planeSize;
  if (pDesc == NULL)
	pDesc = (image_desc*)malloc(sizeof(image_desc));
  pDesc->width = width;
  pDesc->height = height;
  planeSize = sizeof(uint8_t) * height * width;
  /* Allocate memory for each image plane */
  pDesc->pBlue = (uint8_t *) malloc (planeSize);
  pDesc->pGreen = (uint8_t *) malloc (planeSize);
  pDesc->pRed = (uint8_t *) malloc (planeSize);
  return planeSize;
}


int writeImage (image_desc iDesc, targa_header head, char * fName)
{
  FILE *fDesc;
  uint8_t *pBlue, *pGreen, *pRed, *pBlueEnd;
  int i;
  
  /* Open output image file */
  if ((fDesc = fopen (fName, "w")) == NULL)
  {
	fprintf (stderr, "Cannot create the file \"%s\".\n", fName);
	return 0;
  }

  /* Ecrire le header dans fDesc*/
  head.width = iDesc.width;
  head.height = iDesc.height;
  printf("[read mem_targa] Header : %u %u %u %u %u \n", 
		 head.idlength, head.colourmaptype, head.datatypecode, head.width, head.height);

  fwrite (&head, sizeof (targa_header), 1, fDesc);

// Variables temporaires 
  pBlue = iDesc.pBlue;
  pGreen = iDesc.pGreen;
  pRed = iDesc.pRed;
  /* On va lire head.width*head.height pixels pour les mettre dans le fichier fDesc */
  for (i=0; i<head.width*head.height; i++) 
  {
	fwrite(pBlue+i, sizeof(uint8_t), 1, fDesc);
	fwrite(pGreen+i, sizeof(uint8_t), 1, fDesc);
	fwrite(pRed+i, sizeof(uint8_t), 1, fDesc);
  }
  fclose (fDesc);
  return 1;
}
