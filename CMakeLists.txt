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
add_executable(main
  main.c
omphpc.h
  stb_image.h
  stb_image_write.h
)

target_compile_options(main PUBLIC -O2 -mp=gpu)
target_include_directories(main PUBLIC
  ${OpenMP_C_INCLUDE_DIRS}
)
