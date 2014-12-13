#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "fun_targa.h"
#include "mem_targa.h"

void image_inject(image_desc i_img, image_desc m_img, image_desc * p_img) 
{
	
}

void image_mono(image_desc i_img, image_desc *p_img) 
{

}


void image_clone(image_desc i_img, image_desc *p_img) 
{
  int planeSize;
  uint8_t *iBlue  = i_img.pBlue; 
  uint8_t *iGreen = i_img.pGreen; 
  uint8_t *iRed   = i_img.pRed;
  uint8_t *oBlue, *oGreen, *oRed, *oBlueEnd,  *oBlueMid;
  /* Allocation memoire pour l'image */
  planeSize = mallocImage(p_img, i_img.width, i_img.height);	
  oBlue = p_img->pBlue; 
  oGreen = p_img->pGreen;
  oRed = p_img->pRed;

  /* Transformation */
  oBlueEnd = oBlue + sizeof(uint8_t) * planeSize;
  while (oBlue < oBlueEnd) {
	*oBlue = *iBlue;
	*oGreen = *iGreen;
	*oRed = *iRed;
	iBlue++; iGreen++; iRed++;
	oBlue++; oGreen++; oRed++;
  }
}

