/*
 * Tópicos de Engenharia Informática
 * High Performance Computing
 * calcular_pi.c
 * José Jasnau Caeiro
 * 2024.03.21
 *
 * código das aulas sobre OpenMP
 */

#include <math.h>
#include "omphpc.h"

double ff(double x) {
  return sqrt(1.0 - x*x);
}

/*
* cálculo por meio de quadratura simples da área delimitada por 
* uma função f() e o eixo OX
* a - início do intervalo 
* b - fim do intervalo 
* n - número de intervalos
* f - apontador para a função 
*/
double quadratura( double a,
                    double b,
                    int n, 
                    double (*f)(double) ) {
  double dx = (double) (b-a) / (double) n;

  double soma = 0.0;
  double x = a;
  for (int k=0; k < n; k++) {
    soma += f(x) * dx;
    x += dx;
  }

  return soma;
}


/*
* calcular numericamente o valor da constante matemática pi 
* através dum processo de quadratura simples
* n - número de intervalos na quadratura
*/  
double calcular_pi(int n) {
  double a = 0.0;
  double b = 1.0;
  double pi = 4.0 * quadratura(a, b, n, ff);
  return pi;
}



