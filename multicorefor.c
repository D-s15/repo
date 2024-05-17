#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <unistd.h>
#include <time.h>
#include "omphpc.h"

#define MAXTHREADS 4
#define M 10

/*
* função de demonstração de paralelismo for
* em vários cores por meio da soma elemento 
* a elemento de dois vetores
*/
void multicorefor() {
  double *u = (double*) malloc(sizeof(double) * M);
  double *v = (double*) malloc(sizeof(double) * M);
  double *w = (double*) malloc(sizeof(double) * M);
  for (int k=0; k < M; k++) {
    u[k] = (double) k; v[k] = 2.0 * (double) k;
    w[k] = 0.0;
  }
  int num_cores=0;
#ifdef _OPENMP
  num_cores = omp_get_num_procs();
#endif 
  double t0 = time(0);
#ifdef _OPENMP
  #pragma omp parallel for num_threads(MAXTHREADS) 
#endif
  for (int k=0; k < M; k++) 
  {
    int tid = 0;
    double ta = 0.0; double tb = 0.0;
#ifdef _OPENMP
    tid = omp_get_thread_num();
    ta = omp_get_wtime();
#endif
    w[k] = u[k] + v[k];
    sleep(1);  
#ifdef _OPENMP
    tb = omp_get_wtime();
#endif /* ifdef _OPENMP */
    printf("k = %d número de cores = %d, thread = %d\n", k, num_cores, tid);
    printf("%s %g segundos\n\n", "tempo de execução na thread = ", tb-ta);
  }
  double t1 = time(0);
  printf("tempo total de execução %g segundos\n", t1-t0);
  for (int k=0; k < M; k++) {
    printf("w[%d] = %g + %g = %g\n", k, u[k], v[k], w[k] );
  }
  free(u); free(v); free(w);
}


