cmake_minimum_required(VERSION 3.10)

project(BigBaseC C)

add_subdirectory(${PROJECT_SOURCE_DIR}/../minhook minhook)

file(GLOB ROOT_SRC ${PROJECT_SOURCE_DIR}/*c)

add_library(BigBaseC MODULE ${ROOT_SRC})

if (CMAKE_C_COMPILER_ID MATCHES "MSVC")
    target_compile_options(BigBaseC PRIVATE -DUNICODE -D_UNICODE -DNOMINMAX /Zi)
    target_link_options(BigBaseC PRIVATE /DEBUG /OPT:REF /OPT:ICF)
else()
    target_compile_options(BigBaseC PRIVATE -municode -static -Woverflow)
endif()

target_include_directories(BigBaseC PRIVATE ${PROJECT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/../minhook)

target_precompile_headers(BigBaseC PRIVATE pch.c)

target_link_libraries(BigBaseC PRIVATE minhook)

# mostly stolen from ChaosModV
