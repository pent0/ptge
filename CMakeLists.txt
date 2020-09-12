cmake_minimum_required(VERSION 2.8)

add_library(ptge
    include/ptge/ptgpak.h
    src/ptgpak.cpp)

target_include_directories(ptge PUBLIC include)

add_executable(pakreader
    tools/pakreader.cpp)

target_link_libraries(pakreader PRIVATE ptge)