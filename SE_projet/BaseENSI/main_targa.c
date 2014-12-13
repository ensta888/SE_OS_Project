#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <dirent.h>
#include "fun_targa.h"
#include "mem_targa.h"

int main(int argc, char **argv)
{
  char *inputfn=NULL, *outputfn=NULL; /* input image file, output image file */
  char *inject=NULL;       /* Image to inject */
  image_desc i_img, o_img;
  targa_header i_head; /* Header of input image */
  FILE *input, *output; /* Input and output file descriptors */
  int clone = 0;

  if (inputfn==NULL || outputfn==NULL || !OK) {
		fprintf(stderr, "Usage : %s [-f<number>|-r<number>|-d|-m <H|V>|-b] -i <input_file> -o <output_file>\n", argv[0]); 
		fprintf(stderr, "No input and/or output file.\n");
		exit(EXIT_FAILURE);
  }

  /* Test if input directory exist */
  if (opendir("./input") == NULL)
  {         
		printf("Required 'input' directory does not exist\n");
		exit(EXIT_FAILURE);
  }

	// READ
	readImage(&i_img, &i_head, inputfn);

	// CLONE
  if (clone) {
		image_clone(i_img, &o_img);
  }

	// WRITE. Note: input image header of clone is also the same as output image header.
  writeImage(o_img, i_head, outputfn);
	
	freeImage(&o_img);
	
	exit(EXIT_SUCCESS);
}
