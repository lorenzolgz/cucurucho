cmake_minimum_required(VERSION 3.7)

project(cucurucho)

#find_package(PkgConfig REQUIRED)
#pkg_check_modules(SDL2 REQUIRED sdl2)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(cucurucho main.cpp classes/Fondo.cpp classes/Fondo.h classes/VentanaJuego.cpp classes/VentanaJuego.h classes/Jugador.cpp classes/Jugador.h classes/Vector.cpp classes/Vector.h classes/Hud.cpp classes/Hud.h classes/Utils.cpp classes/Utils.h)

target_link_libraries(cucurucho ${SDL2_LIBRARIES})
target_link_libraries(cucurucho SDL2::SDL2 -lSDL2_image)