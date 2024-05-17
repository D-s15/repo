/*
 * Tópicos de Engenharia Informática
 * High Performance Computing
 * normalizar.c
 * José Jasnau Caeiro
 * 2024.03.21
 *
 * código das aulas sobre OpenMP
 *
 * normalizar a imagem entre 0 e 255
 */

#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include "omphpc.h"

unsigned char* normalizar(double* img_in,
                          int nrows,
                          int ncols){
  unsigned char* img_out = (unsigned char*)
                            malloc(sizeof(unsigned char)*nrows*ncols);
  // determinar o máximo e o mínimo da imagem
  double maximo = -DBL_MAX; 
  double minimo = DBL_MAX; 
  for (int row=0; row < nrows; row++) {
    for (int col=0; col < ncols; col++) {
      int idx = get_idx_gray(row, col, ncols);
      if (maximo < img_in[idx]) {
        maximo = img_in[idx];
      }
      if (minimo > img_in[idx]) {
        minimo = img_in[idx];
      }
    }
  }
  double h = 255.0 / (maximo-minimo);
  for (int row=0; row < nrows; row++) {
    for (int col=0; col < ncols; col++) {
      int idx = get_idx_gray(row, col, ncols);  
      unsigned char v = (unsigned char) ((img_in[idx]-minimo) * h);
      img_out[idx] = img_in[idx];
    }
  }
  return img_out;
}

