cmake_minimum_required(VERSION 3.7)

project(cucurucho)

find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2 REQUIRED sdl2)

pkg_check_modules(JSONCPP jsoncpp)
link_libraries(${JSONCPP_LIBRARIES})

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(cucurucho main.cpp classes/Fondo.cpp classes/Fondo.h classes/VentanaJuego.cpp classes/VentanaJuego.h classes/model/Jugador.cpp classes/model/Jugador.h classes/Vector.cpp classes/Vector.h classes/Hud.cpp classes/Hud.h classes/Utils.cpp classes/Utils.h classes/Helper.cpp classes/Helper.h classes/Enemigo2.cpp classes/Enemigo2.h classes/Log.cpp classes/Log.h classes/Enemigo1.cpp classes/Enemigo1.h constants.h classes/view/JugadorView.cpp classes/view/JugadorView.h)

target_link_libraries(cucurucho ${SDL2_LIBRARIES})
target_link_libraries(cucurucho SDL2 -lSDL2_image)