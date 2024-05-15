#include <stdio.h>
#include <stdlib.h>
#include "stb_image_write.h"

#define WIDTH 7680
#define HEIGHT 4320
#define MAX_ITER 1000

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

// Função para gerar a imagem do conjunto de Mandelbrot
void generate_mandelbrot_image(unsigned char *image) {
    double x_step = 3.5 / WIDTH;
    double y_step = 2.0 / HEIGHT;

    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            double real = -2.5 + x * x_step;
            double imag = -1.0 + y * y_step;
            int iter = mandelbrot(real, imag);
            // Mapeamento do valor iter para uma cor
            // Aqui você pode usar o mapa de cores escolhido pelo grupo
            // Por exemplo, pode-se atribuir diferentes valores de RGB com base no valor de iter
            // Isso produzirá uma imagem colorida
            // A atribuição das cores dependerá do mapa de cores específico que o grupo escolher
            // Por enquanto, vou atribuir uma cor básica para simplificar
            int color = (iter % 256); // Apenas para ilustração, precisa ser substituído por um mapeamento de cor real
            image[3 * (y * WIDTH + x) + 0] = color; // Red
            image[3 * (y * WIDTH + x) + 1] = color; // Green
            image[3 * (y * WIDTH + x) + 2] = color; // Blue
        }
    }
}

int main() {
    unsigned char *image = (unsigned char *)malloc(3 * WIDTH * HEIGHT * sizeof(unsigned char));
    if (image == NULL) {
        fprintf(stderr, "Erro ao alocar memória para a imagem.\n");
        return EXIT_FAILURE;
    }

    generate_mandelbrot_image(image);

    // Escrever a imagem em um arquivo JPEG usando a biblioteca STB
    if (!stbi_write_jpg("mandelbrot.jpg", WIDTH, HEIGHT, 3, image, 100)) {
        fprintf(stderr, "Erro ao escrever a imagem.\n");
        free(image);
        return EXIT_FAILURE;
    }

    free(image);
    printf("Imagem gerada com sucesso!\n");
    return EXIT_SUCCESS;
}
