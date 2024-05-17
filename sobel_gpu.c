/*
 * Tópicos de Engenharia Informática
 * High Performance Computing
 * sobel_gpu.c
 * José Jasnau Caeiro
 * 2024.03.21
 *
 * código das aulas sobre OpenMP
 *
 * detetor de contornos de Sobel
 * em versão nos GPUs
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "omphpc.h"

#ifdef _OPENMP
#include <omp.h>
#endif /* ifdef _OPENMP */

void copiar_imagem(unsigned char* img_in,
                   double *img_dev,
                   int nrows, int ncols,
                   int dev, int num_devices) {
  const int delta_rows = nrows / num_devices;
  int cc = 0;
  for (int row=dev*delta_rows; row<(dev+1)*delta_rows; row++) {
    for (int col=0; col < ncols; col++) {
      int idx = row*ncols+col;
      img_dev[cc] = (double) img_in[idx]; 
      cc++;
    }
  }
}

double* criar_gradiente(int nrows, int ncols) {
  double* g = (double*) malloc(sizeof(double)*nrows*ncols);
  for (int k=0; k < nrows*ncols; k++) {
    g[k] = 0.0;
  }
  return g;
}

void copiar_imagem_processada(double *g, double *g_dev,
                              int nrows, int ncols,
                              int dev, int num_devices) {
  const int delta_rows = nrows / num_devices;
  int k = 0;
  for(int row=dev*delta_rows; row < delta_rows*(dev+1); row++) {
    for (int col=0; col < ncols; col++) {
      int idx = row*ncols+col;
      int idx_device = k*ncols+col; 
      g[idx] = g_dev[idx_device]; 
    }
    k++;
  } 
}

void sobel_device(double *img,
                  double *g,
                  int nrows, int ncols,
                  int dev) {
  for (int row=1; row < nrows-1; row++) {
    for (int col=1; col < ncols-1; col++) {
      int idx = row * ncols + col;
      int a = (row-1) * ncols + (col-1);
      int b =  row    * ncols + (col-1);
      int c = (row+1) * ncols + (col-1);

      int d = (row-1) * ncols + (col+1);
      int e =  row    * ncols + (col+1);
      int f = (row+1) * ncols + (col+1);

      int u = (row-1) * ncols + col;
      int v = (row+1) * ncols + col;
      
      double gx = img[d]-img[a] + 2.0 * (img[e]-img[b]) + img[f]-img[c];
      double gy = img[c]-img[a] + 2.0 * (img[v]-img[u]) + img[f]-img[d];
      g[idx] = sqrt(gx*gx+gy*gy);
    }
  }
}

double* sobel_gpu(unsigned char* img_in,
                  int nrows, int ncols) {
  const int num_devices = 4;
  const int delta_rows = nrows / num_devices;
  double *g = criar_gradiente(nrows, ncols); 
  clock_t t0, t1;
  t0 = clock();

  for(int dev = 0; dev < num_devices; dev++) {
    // cria uma cópia da parte da imagem 
    double *img_dev = (double*) malloc(sizeof(double) 
                                       * delta_rows * ncols);
    copiar_imagem(img_in, img_dev, nrows, ncols, dev, num_devices);
    // processa a parte da imagem no device
    double* g_dev = (double*) malloc(sizeof(double)
                                     * delta_rows * ncols); 
#ifdef _OPENMP
    #pragma omp target teams device(dev) distribute parallel for collapse(2) \
    map(img_dev[0:delta_rows*ncols],g_dev[0:delta_rows*ncols]) \
    map(delta_rows,ncols,dev)
#endif /* ifdef _OPENMP */
    // sobel_device(img_dev, g_dev, delta_rows, ncols, dev);
    for (int row=1; row < delta_rows-1; row++) {
      for (int col=1; col < ncols-1; col++) {
        double soma = 0.0;
        int idx = row * ncols + col;
        for (int n=0; n < NUMERO_REPETICOES; n++) {
          int a = (row-1) * ncols + (col-1);
          int b =  row    * ncols + (col-1);
          int c = (row+1) * ncols + (col-1);

          int d = (row-1) * ncols + (col+1);
          int e =  row    * ncols + (col+1);
          int f = (row+1) * ncols + (col+1);

          int u = (row-1) * ncols + col;
          int v = (row+1) * ncols + col;

          double gx = img_dev[d]-img_dev[a] + 2.0 * (img_dev[e]-img_dev[b]) + img_dev[f]-img_dev[c];
          double gy = img_dev[c]-img_dev[a] + 2.0 * (img_dev[v]-img_dev[u]) + img_dev[f]-img_dev[d];
          // g_dev[idx] = sqrt(gx*gx+gy*gy);
          soma += sqrt(gx*gx+gy*gy);
        }
        g_dev[idx] = soma / NUMERO_REPETICOES;
      }
    }

    free(img_dev);

    // copia de volta a parte da imagem
    copiar_imagem_processada(g, g_dev,
                             nrows, ncols,
                             dev, num_devices); 
    free(g_dev);
  }
  t1 = clock();
  printf("Sobel GPU: tempo de execucao %g segundos\n", 
         (double)(t1-t0) / CLOCKS_PER_SEC );
  return g;
}


