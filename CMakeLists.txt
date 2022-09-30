cmake_minimum_required(VERSION 3.23)
project(MetodoDeGauss)

set(CMAKE_CXX_STANDARD 20)

add_executable(MetodoDeGauss main.cpp AnswerVector.h CoeffMatrix.h main.h System.h)
