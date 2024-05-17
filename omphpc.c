/*
 * Tópicos de Engenharia Informática
 * High Performance Computing
 * hpc.c
 * José Jasnau Caeiro
 * 2024.03.21
 *
 * código das aulas sobre OpenMP
 */

#include <stdio.h>
#include <stdlib.h>

#include "omphpc.h"

#define N 100000

int main(int argc, char *argv[])
{
  printf("%s\n", "TEI (HPC) 2024");

  // a mais simples das funções e que testa a compilação
  hello_world();

  // cálculo de pi por quadratura
  // printf("pi = %g\n", calcular_pi(N));
  // multicore();
  // multicorefor();
  // reductionfor();
  detetar_contornos_gpu();

  return EXIT_SUCCESS;
}
