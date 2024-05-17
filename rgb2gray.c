/*
 * Tópicos de Engenharia Informática
 * High Performance Computing
 * rgb2gray.c
 * José Jasnau Caeiro
 * 2024.03.21
 *
 * código das aulas sobre OpenMP
 * conversão de imagem a cores para imagem em 
 * níveis de cinzento
 */

/*
 * usa como entradas os valores de red, green e blue
 * e a converte num valor em nível de cinzento
 */ 
unsigned char rgb2gray(unsigned char r,
                       unsigned char g,
                       unsigned char b) {
  const double pr = 0.3;
  const double pg = 0.59;
  const double pb = 0.11;
  double gray = (double) r * pr +
    (double) g * pg +
    (double) b * pb ;
   return (unsigned char) gray; 
}




