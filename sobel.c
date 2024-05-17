/*
 * Tópicos de Engenharia Informática
 * High Performance Computing
 * sobel.c
 * José Jasnau Caeiro
 * 2024.03.21
 *
 * código das aulas sobre OpenMP
 *
 * detetor de contornos de Sobel
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "omphpc.h"

double* sobel(unsigned char* img_in,
              int nrows, int ncols) {
  double* g = (double*) malloc(sizeof(double)*nrows*ncols);
  clock_t t0 = clock();
  for (int row=0; row < nrows; row++) {
    for (int col=0; col < ncols; col++) {
      int idx = row * ncols + col;
      double soma = 0.0;
      for (int k=0; k < NUMERO_REPETICOES; k++) {
        double gOX = 0.0;
        double gOY = 0.0;

        int a = (row-1)*ncols + col-1;
        int b = row*ncols     + col-1;
        int c = (row+1)*ncols + col-1;

        int d = (row-1)*ncols + col+1;
        int e = row*ncols     + col+1;
        int f = (row+1)*ncols + col+1;

        int u = (row-1)*ncols + col;
        int v = (row+1)*ncols + col;

        gOX = img_in[d]+2.0*img_in[e]+img_in[f]-
          img_in[a]-2.0*img_in[b]-img_in[c];
        gOY = img_in[c]+2.0*img_in[v]+img_in[f]-
          img_in[a]-2.0*img_in[u]-img_in[d];
        soma += sqrt(gOX*gOX + gOY*gOY);
      }
      g[idx] = soma / NUMERO_REPETICOES;
    }
  }
  clock_t t1 = clock();
  printf("Sobel: tempo de execucao %g segundos\n", 
         (double) (t1-t0) / CLOCKS_PER_SEC);
  return g;
}
