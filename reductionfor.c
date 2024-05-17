#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <unistd.h>
#include <time.h>
#include "omphpc.h"

#define MAXTHREADS 3
#define M 24

/*
* função de demonstração de paralelismo for
* em vários cores por meio de uma redução
* e variáveis partilhadas entre threads
*/
void reductionfor(void)
{
  double *r = (double*) malloc(sizeof(double) * M);
  srand48(time(NULL));
  for (int k=0; k < M; k++) {
    r[k] = drand48();
  }
  double *tempos_somados = (double*) malloc(sizeof(double) * MAXTHREADS);
  double soma = 0.0;
  double t0 = time(0);
#ifdef _OPENMP
  #pragma omp parallel for num_threads(MAXTHREADS) reduction(+:soma) shared(tempos_somados)
#endif
  for (int k=0; k < M; k++) {
    double ta = 0.0; double tb = 0.0;
    int tid = 0;
#ifdef _OPENMP
    tid = omp_get_thread_num();
    ta = omp_get_wtime();
#endif
    sleep(1);  
#ifdef _OPENMP
    tb = omp_get_wtime();
#endif /* ifdef _OPENMP */
    printf("%s %d = %g segundos\n", "tempo de execução na thread = ", tid, tb-ta);
    soma += r[k];
    tempos_somados[tid] += (tb-ta);
  } 
  double t1 = time(0);
  for (int k=0; k < MAXTHREADS; k++) {
    printf("tempos somados na thread %d = %g\n", k, tempos_somados[k]);
  }
  printf("%s %g\n", "tempo total de execução = ", t1-t0);
  printf("soma de valores aleatórios = %g\n", soma);
  free(r); free(tempos_somados);
}
