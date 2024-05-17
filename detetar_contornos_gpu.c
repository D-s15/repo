/*
 * Tópicos de Engenharia Informática
 * High Performance Computing
 * detetar_contornos_gpu.c
 * José Jasnau Caeiro
 * 2024.03.21
 *
 * código das aulas sobre OpenMP
 */


#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <unistd.h>
#include <time.h>
#include "omphpc.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

void detetar_contornos_gpu() { 
  int ncols, nrows, nchannels;
  const char *filename = "default.jpg";
  unsigned char *img_in = stbi_load(filename, 
                                    &ncols, &nrows, &nchannels, 
                                    0);
  printf("%s\n", "deteção de contornos paralela");
  printf("cols = %d, rows = %d, channels = %d\n", ncols, nrows, nchannels);
  unsigned char *img_gray = img_rgb2gray(img_in, ncols, nrows); 
  stbi_image_free(img_in);
  stbi_write_jpg("grayimg.jpg", ncols, nrows, 1, img_gray, 90);

  double *gs = sobel(img_gray, nrows, ncols);
  free(gs);

  double *gm = sobel_multicore(img_gray, nrows, ncols);
  free(gm);

  double* gu = sobel_gpu(img_gray, nrows, ncols);
  stbi_image_free(img_gray);
  unsigned char *ng = normalizar(gu, nrows, ncols); 
  free(gu);

  stbi_write_jpg("grayox.jpg", ncols, nrows, 1, ng, 100);
  free(ng);
}


