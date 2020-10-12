cmake_minimum_required(VERSION 3.14)

project(b64 C)

add_executable(b64 main.c base64.c encode.c decode.c)