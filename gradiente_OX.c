/*
 * Tópicos de Engenharia Informática
 * High Performance Computing
 * gradiente_OX.c
 * José Jasnau Caeiro
 * 2024.03.21
 *
 * código das aulas sobre OpenMP
 *
 * cálculo da componente do gradiente segundo OX 
 * no detetor de contornos de Sobel
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "omphpc.h"

double* gradiente_OX(unsigned char* img_in,
                     int nrows, int ncols) {
  double* gOX = (double*) malloc(sizeof(double) * nrows * ncols);
  for (int k = 0; k < nrows * ncols; k++) {
    gOX[k] = 0.0;
  }
  for (int row=1; row < nrows-1; row++) {
    for (int col=1; col < ncols-1; col++) {
      int idx = get_idx_gray(row, col, ncols);

      int a = get_idx_gray(row-1, col-1, ncols);
      int b = get_idx_gray(row,   col-1, ncols);
      int c = get_idx_gray(row+1, col-1, ncols);

      int d = get_idx_gray(row-1, col+1, ncols);
      int e = get_idx_gray(row,   col+1, ncols);
      int f = get_idx_gray(row+1, col+1, ncols);

      gOX[idx] = img_in[d]+2.0*img_in[e]+img_in[f]-
                 img_in[a]-2.0*img_in[b]-img_in[c];
    }
  }
  return gOX;
}


