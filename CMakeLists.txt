# PROJECT: TÓPICOS DE ENGENHARIA INFORMÁTICA- HIGH PERFORMANCE COMPUTING
# FILE:    CMakeLists.txt
# AUTHOR:  José Jasnau Caeiro
# DATE:    2024-03-21
# cmake -DCMAKE_C_FLAGS="-mp=gpu -O3" ~/workspace/disciplinas/tei/openmp"
# cmake --build . --config Release
# 
cmake_minimum_required(VERSION 3.16)
set(CMAKE_C_COMPILER nvc)
set(CMAKE_C_FLAGS "-mp=gpu -O2" CACHE STRING "NVC OPENMP")

# set the project name
project(repo VERSION 0.1 LANGUAGES C)
add_executable(parallelCPU ${SOURCES} ${STB_SRC_DIR}/stb_image_write.c
  omphpc
  omphpc.c
  omphpc.h
  hello_world.c
  calcular_pi.c
  multicore.c
  multicorefor.c
  reductionfor.c
  stb_image.h
  stb_image_write.h
  detetar_contornos_gpu.c
  rgb2gray.c
  img_rgb2gray.c
  get_idx_gray.c
  gradiente_OX.c
  gradiente_OY.c
  sobel.c
  sobel_multicore.c
  sobel_gpu.c
  normalizar.c
  aceleracaoGPU.c
  parallelCPU.c
  sequencial.c
)

target_compile_options(main PUBLIC -O2 -mp=gpu)
target_include_directories(main PUBLIC
  ${OpenMP_C_INCLUDE_DIRS}
)