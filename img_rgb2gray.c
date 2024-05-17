/*
 * Tópicos de Engenharia Informática
 * High Performance Computing
 * img_rgb2gray.c
 * José Jasnau Caeiro
 * 2024.03.21
 *
 * código das aulas sobre OpenMP
 * conversão duma imagem a cores numa imagem a 
 * níveis de cinzento
 */

#include <stdlib.h>
#include "omphpc.h"

/*
* conversão em imagem de níveis de cinzento
* duma imagem RGB 
*/ 
unsigned char* img_rgb2gray(unsigned char* img_rgb,
                            int nrows,
                            int ncols) {
  const int NCHANNELS = 3;
  unsigned char *img_gray = (unsigned char*)
    malloc(sizeof(unsigned char) * ncols * nrows);

  for (int col=0; col < ncols; col++) {
    for (int row=0; row < nrows; row++) {
      int idx_rgb = (row * ncols + col) * NCHANNELS; 
      unsigned char red   = img_rgb[idx_rgb];   
      unsigned char green = img_rgb[idx_rgb+1]; 
      unsigned char blue  = img_rgb[idx_rgb+2];

      int idx_gray = get_idx_gray(row, col, ncols); // row * ncols + col;
      img_gray[ idx_gray ] = rgb2gray(red, green, blue);
    }
  }

  return img_gray;
}


