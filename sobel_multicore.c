/*
 * Tópicos de Engenharia Informática
 * High Performance Computing
 * sobel_multicore.c
 * José Jasnau Caeiro
 * 2024.03.21
 *
 * código das aulas sobre OpenMP
 *
 * detetor de contornos de Sobel
 * em versão multicore
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "omphpc.h"

#ifdef _OPENMP
#include <omp.h>
#endif /* ifdef _OPENMP */

double* sobel_multicore(unsigned char* img_in,
                        int nrows, int ncols) {
  double* g = (double*) malloc(sizeof(double)*nrows*ncols);
  clock_t t0, t1;
  const int NCORES = 96;
  const int delta_rows = nrows / NCORES;
  t0 = clock();
  int num_threads = 1;
  #pragma omp parallel num_threads(NCORES) for collapse(1) shared(g,img_in) 
  for (int row=1; row < nrows-1; row++) {
    for (int col=1; col < ncols-1; col++) {
      num_threads = omp_get_num_threads();
      int idx = row*ncols + col;
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

        double x = img_in[d]-img_in[c];
        double y = img_in[f]-img_in[a];

        gOX =  x + y + 2.0 * (img_in[e] - img_in[b]);
        gOY = -x + y + 2.0 * (img_in[v] - img_in[u]);

        soma += sqrt(gOX*gOX + gOY*gOY);
      }
      g[idx] = soma / NUMERO_REPETICOES;
    }
  }

  printf("número de cores/threads = %d\n", num_threads);
  t1 = clock();
  printf("Sobel multicore: tempo de execucao %g segundos\n", 
         (double)(t1-t0) / CLOCKS_PER_SEC );
  return g;
}
