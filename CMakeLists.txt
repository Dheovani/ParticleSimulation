cmake_minimum_required(VERSION 3.10)
project(ParticleSimulation)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(SFML 2.5 COMPONENTS system network window graphics CONFIG REQUIRED)
add_executable(ParticleSimulation main.cpp particles.h particles.cpp)

target_link_libraries(ParticleSimulation sfml-system sfml-network sfml-graphics sfml-window)