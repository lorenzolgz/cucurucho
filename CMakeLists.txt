cmake_minimum_required(VERSION 3.7)

project(cucurucho)

find_package(PkgConfig REQUIRED)
find_package(SDL2 REQUIRED)

pkg_check_modules(SDL2 REQUIRED sdl2)
pkg_check_modules(JSONCPP jsoncpp)

link_libraries(${JSONCPP_LIBRARIES})

include_directories(${SDL2_INCLUDE_DIRS})

add_executable(cucurucho main.cpp classes/view/FondoVista.cpp classes/view/FondoVista.h classes/model/VentanaJuego.cpp classes/model/VentanaJuego.h classes/model/Jugador.cpp classes/model/Jugador.h classes/Vector.cpp classes/Vector.h classes/model/Hud.cpp classes/model/Hud.h classes/Utils.cpp classes/Utils.h classes/model/Helper.cpp classes/model/Helper.h classes/model/Enemigo2.cpp classes/model/Enemigo2.h classes/Log.cpp classes/Log.h classes/model/Enemigo1.cpp classes/model/Enemigo1.h classes/view/JugadorVista.cpp classes/view/JugadorVista.h classes/Configuracion.h classes/Configuracion.cpp classes/view/Enemigo2Vista.cpp classes/view/Enemigo2Vista.h classes/view/Enemigo1Vista.cpp classes/view/Enemigo1Vista.h classes/view/HelperVista.cpp classes/view/HelperVista.h classes/view/HudVista.cpp classes/view/HudVista.h classes/view/VentanaJuegoVista.cpp classes/view/VentanaJuegoVista.h)

target_link_libraries(cucurucho ${SDL2_LIBRARIES})
target_link_libraries(cucurucho SDL2 -lSDL2_image)
target_link_libraries(cucurucho ${JSONCPP_LIBRARIES})