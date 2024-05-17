
double* sobel_gu(unsigned char* img_in,
                 int nrows, int ncols) {
  const int num_devices = 4;
  const int NUMERO_REPETICOES = 500;
  const int delta_rows = nrows / num_devices;
  double* g = (double*) malloc(sizeof(double)*nrows*ncols);
  clock_t t0, t1;
  t0 = clock();
  unsigned char** img_dev_in = (unsigned char**) malloc(sizeof(unsigned char*)*num_devices);
  unsigned char** img_dev_out = (unsigned char**) malloc(sizeof(unsigned char*)*num_devices);
  for(int dev=0; dev<num_devices;dev++){
    img_dev_in[dev] =
      (unsigned char*) malloc(sizeof(unsigned char)*delta_rows*ncols);

    int k = 0;
    for(int row=dev*delta_rows; row < delta_rows*(dev+1); row++) {
      for (int col=0; col < ncols; col++) {
        int idx = row*ncols+col;
        int idx_device = k*ncols+col; 
        img_dev_in[dev][idx_device] = img_in[idx]; 
      }
      k++;
    } 

    img_dev_out[dev] =
      (double*) malloc(sizeof(double)*delta_rows*ncols);
    for (int j=0; j < delta_rows*ncols; j++) {
      img_dev_out[dev][j] = 0.0;
    }
  }
#ifdef _OPENP
  #pragma omp parallel shared(img_in,g,img_dev_in,img_dev_out) for num_threads(num_devices) 
#endif /* ifdef _OPENMP */
  for (int dev=0; dev < num_devices; dev++) {
    // criam-se 4 pequenas imagens por device
    unsigned char* img_device_in = img_dev_in[dev];
    double* img_device_out = img_dev_out[dev]; 

    printf("DEVICE = %d\n",dev);
    const int NTEAMS = 108;
    const int thread_limit_per_team = delta_rows * ncols / NTEAMS; 
    printf("thread_limit_per_team = %d\n", thread_limit_per_team);
#ifdef _OPENP
    #pragma omp target teams device(dev) distribute parallel for \
    collapse(2) map(dev, NUMERO_REPETICOES) \
    map(img_device_in[0:delta_rows*ncols],img_device_out[0:delta_rows*ncols]) 
#endif /* ifdef _OPENMP */
    // cálculo do algoritmo de sobel para cada região device
    for (int row=1; row < delta_rows-1; row++) {
      for (int col=1; col < ncols-1; col++) {
        int tid = omp_get_thread_num();
        double soma = 0.0;
        int idx = row * ncols + col;

        /*
          if( tid == 100 && dev == 1 && col > 2000)
            printf("device id = %d, row = %d, col = %di, nr = %d\n", 
                   dev, row, col, NUMERO_REPETICOES);
                   */
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

        double x = img_device_in[d]-img_device_in[c];
        double y = img_device_in[f]-img_device_in[a];

        double d_da = img_device_in[d] -img_device_in[a];
        double d_eb = img_device_in[e] -img_device_in[b];
        double d_fc = img_device_in[f] -img_device_in[c];
        gOX = d_da + 2.0 * d_eb + d_fc;

        double d_ca = img_device_in[c] -img_device_in[a];
        double d_vu = img_device_in[v] -img_device_in[u];
        double d_fd = img_device_in[f] -img_device_in[d];
        gOY = d_ca + 2.0 * d_vu + d_fd; 

        //gOX =  x + y + 2.0 * (img_device_in[e] - img_device_in[b]);
        //gOY = -x + y + 2.0 * (img_device_in[v] - img_device_in[u]);

        soma = sqrt(gOX*gOX + gOY*gOY);
        // img_device_out[idx] = soma / NUMERO_REPETICOES;
        img_device_out[idx] = soma; // img_device_in[idx];
      } // for col
    } // for row

    int k = 0;
    for(int row=dev*delta_rows; row < delta_rows*(dev+1); row++) {
      for (int col=0; col < ncols; col++) {
        int idx = row*ncols+col;
        int idx_device = k*ncols+col; 
        g[idx] = img_device_out[idx_device]; 
        // g[idx] = img_dev_in[dev][idx_device]; 
      }
      k++;
    } 
  } // for dev

  for(int dev=0; dev<num_devices;dev++){
    free(img_dev_in[dev]);
    free(img_dev_out[dev]);
  }

  free(img_dev_in);
  free(img_dev_out);

  t1 = clock();
  printf("Sobel GPU: tempo de execucao %g segundos\n", 
         (double)(t1-t0) / CLOCKS_PER_SEC );
  return g;
}


