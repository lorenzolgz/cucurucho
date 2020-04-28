cmake_minimum_required(VERSION 3.7)

project(cucurucho)

find_package(PkgConfig REQUIRED)
find_package(SDL2 REQUIRED)

pkg_check_modules(SDL2 REQUIRED sdl2)
pkg_check_modules(JSONCPP jsoncpp)

link_libraries(${JSONCPP_LIBRARIES})

include_directories(${SDL2_INCLUDE_DIRS})


# CPPLINT
set(CMAKE_CXX_STANDARD 11)
# set(CMAKE_CXX_FLAGS "-Wall -Werror -pedantic -pedantic-errors -ggdb -DDEBUG -fno-inline -pthread -lm")
set(CPPLINT_FILTER_OPTIONS
"-,+build/class,+build/deprecated,+build/include_what_you_use,+build/namespaces,+build/printf_format,\
+readability/braces,+readability/check,+readability/fn_size,+readability/function,+readability/multiline_comment,+readability/multiline_string,+readability/utf8,\
+runtime/arrays,+runtime/casting,+runtime/explicit,+runtime/init,+runtime/invalid_increment,+runtime/memset,+runtime/operator,+runtime/printf,+runtime/printf_format,+runtime/rtti,+runtime/string,+runtime/threadsafe_fn,\
+whitespace/blank_line,+whitespace/empty_loop_body,+whitespace/ending_newline,+whitespace/newline,+whitespace/parens,+whitespace/semicolon"
)
set(CMAKE_CXX_CPPLINT "cpplint;--extensions=h,hpp,c,cpp;--filter=${CPPLINT_FILTER_OPTIONS}")
# END CPPLINT

add_executable(cucurucho main.cpp classes/view/FondoVista.cpp classes/view/FondoVista.h classes/model/Jugador.cpp classes/model/Jugador.h classes/Vector.cpp classes/Vector.h classes/model/Hud.cpp classes/model/Hud.h classes/Utils.cpp classes/Utils.h classes/model/Helper.cpp classes/model/Helper.h classes/model/Enemigo2.cpp classes/model/Enemigo2.h classes/Log.cpp classes/Log.h classes/model/Enemigo1.cpp classes/model/Enemigo1.h classes/view/JugadorVista.cpp classes/view/JugadorVista.h classes/Configuracion.h classes/Configuracion.cpp classes/view/Enemigo2Vista.cpp classes/view/Enemigo2Vista.h classes/view/Enemigo1Vista.cpp classes/view/Enemigo1Vista.h classes/view/HelperVista.cpp classes/view/HelperVista.h classes/view/HudVista.cpp classes/view/HudVista.h classes/view/CampoVista.cpp classes/view/CampoVista.h classes/GeneradorDeTexturas.cpp classes/GeneradorDeTexturas.h classes/model/Ticker.h classes/GraphicRenderer.cpp classes/GraphicRenderer.h classes/model/Entidad.h classes/view/TextoView.cpp classes/view/TextoView.h classes/model/CampoMovil.cpp classes/model/CampoMovil.h classes/model/Nivel.cpp classes/model/Nivel.h classes/model/SemillaEntidad.cpp classes/model/SemillaEntidad.h)

target_link_libraries(cucurucho ${SDL2_LIBRARIES})
target_link_libraries(cucurucho SDL2 -lSDL2_image)
target_link_libraries(cucurucho ${JSONCPP_LIBRARIES})