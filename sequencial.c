#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stdio.h>
#include <stdlib.h>
#include "stb_image_write.h"
#include <time.h>

#define WIDTH 7680
#define HEIGHT 4320
#define MAX_ITER 1000
#define TIME_LIMIT 30 // Limite de tempo em segundos
#define FILENAME_LENGTH 50 // Tamanho máximo do nome do arquivo

// Função para calcular a cor de um ponto no conjunto de Mandelbrot
int mandelbrot(double real, double imag) {
    double z_real = 0, z_imag = 0;
    int iter = 0;
    while (iter < MAX_ITER) {
        double z_real_temp = z_real * z_real - z_imag * z_imag + real;
        double z_imag_temp = 2 * z_real * z_imag + imag;
        z_real = z_real_temp;
        z_imag = z_imag_temp;
        if ((z_real * z_real + z_imag * z_imag) > 4.0)
            break;
        iter++;
    }
    return iter;
}

// Função para gerar a imagem do conjunto de Mandelbrot e salvar em um arquivo
void generate_and_save_image(unsigned char *image, int image_num) {
    double x_step = 3.5 / WIDTH;
    double y_step = 2.0 / HEIGHT;

    clock_t start_time = clock(); // Capturar o tempo de início

    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            double real = -2.5 + x * x_step;
            double imag = -1.0 + y * y_step;
            int iter = mandelbrot(real, imag);
            // Mapeamento do valor iter para uma cor
            int red = (iter * 255) / MAX_ITER;
            int blue = 255 - red;
            int green = 0;
            // Atribuir a cor ao pixel na imagem
            image[3 * (y * WIDTH + x) + 0] = red;   // Red
            image[3 * (y * WIDTH + x) + 1] = green; // Green
            image[3 * (y * WIDTH + x) + 2] = blue;  // Blue
        }
    }

    clock_t end_time = clock(); // Capturar o tempo de término
    double elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC; // Calcular o tempo decorrido

    // Criar o nome do arquivo usando o número da imagem
    char filename[FILENAME_LENGTH];
    snprintf(filename, FILENAME_LENGTH, "mandelbrot_%d.jpg", image_num);

    // Escrever a imagem em um arquivo JPEG usando a biblioteca STB
    if (!stbi_write_jpg(filename, WIDTH, HEIGHT, 3, image, 100)) {
        fprintf(stderr, "Erro ao escrever a imagem %s.\n", filename);
    } else {
        printf("Imagem %s gerada e salva com sucesso! Tempo de execução: %.6f segundos\n", filename, elapsed_time);
    }
}

int main() {
    unsigned char *image = (unsigned char *)malloc(3 * WIDTH * HEIGHT * sizeof(unsigned char));
    if (image == NULL) {
        fprintf(stderr, "Erro ao alocar memória para a imagem.\n");
        return 1;
    }

    clock_t start_time = clock(); // Capturar o tempo de início

    int image_num = 1;
    while (1) {
        generate_and_save_image(image, image_num);
        clock_t current_time = clock();
        if ((double)(current_time - start_time) / CLOCKS_PER_SEC >= TIME_LIMIT) {
            break; // Sai do loop se o tempo limite for atingido
        }
        image_num++;
    }

    free(image);
    return 0;
}
