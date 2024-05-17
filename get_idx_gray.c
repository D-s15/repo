/*
 * Tópicos de Engenharia Informática
 * High Performance Computing
 * get_idx_gray.c
 * José Jasnau Caeiro
 * 2024.03.21
 *
 * código das aulas sobre OpenMP
 * calcula o indice correspondente a uma 
 * coordenada (row, col)
 * numa imagem de níveis de cinzento
 */

int get_idx_gray(int row, int col, int ncols) {
  return row * ncols + col;
}

