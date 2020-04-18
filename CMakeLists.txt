cmake_minimum_required(VERSION 3.7)

project(cucurucho)

find_package(PkgConfig REQUIRED)
find_package(SDL2 REQUIRED)

pkg_check_modules(SDL2 REQUIRED sdl2)
pkg_check_modules(JSONCPP jsoncpp)

link_libraries(${JSONCPP_LIBRARIES})

include_directories(${SDL2_INCLUDE_DIRS})

add_executable(cucurucho main.cpp classes/Fondo.cpp classes/Fondo.h classes/VentanaJuego.cpp classes/VentanaJuego.h classes/Jugador.cpp classes/Jugador.h classes/Vector.cpp classes/Vector.h classes/Hud.cpp classes/Hud.h classes/Utils.cpp classes/Utils.h classes/Helper.cpp classes/Helper.h classes/Enemigo2.cpp classes/Enemigo2.h classes/Log.cpp classes/Log.h classes/Enemigo1.cpp classes/Enemigo1.h classes/Configuracion.h classes/Configuracion.cpp)

target_link_libraries(cucurucho ${SDL2_LIBRARIES})
target_link_libraries(cucurucho SDL2 -lSDL2_image)
target_link_libraries(cucurucho ${JSONCPP_LIBRARIES})