#include <stdio.h>
#include <omp.h>
#include "omphpc.h"

#define MAXTHREADS 4

/*
* função de demonstração de paralelismo
* em vários cores
*/
void multicore() {
  int num_cores=0;

  #ifdef _OPENMP
  num_cores = omp_get_num_procs();
  #endif 

  #ifdef _OPENMP
  #pragma omp parallel num_threads(MAXTHREADS)
  #endif
  {
    int tid = 0;

    #ifdef _OPENMP
    tid = omp_get_thread_num();
    #endif

    printf("número de cores = %d, thread = %d\n", num_cores, tid);
  }
}
