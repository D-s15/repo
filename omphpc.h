#ifndef _OPMPHPC
#define _OPMPHPC 1

#define NUMERO_REPETICOES 10000

extern void hello_world(void);
extern double calcular_pi(int n);
extern void multicore(void);
extern void multicorefor(void); 
extern void reductionfor(void);
extern void detetar_contornos_gpu(void); 
extern unsigned char rgb2gray(unsigned char red,
    unsigned char green,
    unsigned char blue);
unsigned char* img_rgb2gray(unsigned char* img_rgb,
    int nrows,
    int ncols); 
extern int get_idx_gray(int row, int col, int ncols); 
extern double* gradiente_OX(unsigned char* img_in,
    int nrows, int ncols);
extern double* gradiente_OX(unsigned char* img_in,
    int nrows, int ncols);
extern unsigned char* normalizar(double* img_in,
    int nrows,
    int ncols);
extern double* gradiente_OX(unsigned char* img_in,
    int nrows, int ncols); 
extern double* gradiente_OY(unsigned char* img_in,
    int nrows, int ncols); 
extern double* sobel(unsigned char* img_in,
    int nrows, int ncols);
extern double* sobel_multicore(unsigned char* img_in,
    int nrows, int ncols);
extern double* sobel_gpu(unsigned char* img_in,
    int nrows, int ncols);
#endif // !_OPMPHPC
