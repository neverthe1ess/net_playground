cmake_minimum_required(VERSION 3.28)
project(net_playground C)

set(CMAKE_C_STANDARD 11)

add_executable(net_playground general_nowait_raw.c
        print_header.c)
