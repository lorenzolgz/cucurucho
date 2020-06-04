cmake_minimum_required(VERSION 3.7)

project(cucurucho)

find_package(PkgConfig REQUIRED)
find_package(SDL2 REQUIRED)

pkg_check_modules(SDL2 REQUIRED sdl2)
pkg_check_modules(JSONCPP jsoncpp)

link_libraries(${JSONCPP_LIBRARIES})

include_directories(${SDL2_INCLUDE_DIRS})
link_libraries(stdc++fs)


# CPPLINT
#set(CMAKE_CXX_STANDARD 11)
# set(CMAKE_CXX_FLAGS "-Wall -Werror -pedantic -pedantic-errors -ggdb -DDEBUG -fno-inline -pthread -lm")
#set(CPPLINT_FILTER_OPTIONS
#"-,+build/class,+build/deprecated,+build/include_what_you_use,+build/namespaces,+build/printf_format,\
#+readability/braces,+readability/check,+readability/fn_size,+readability/function,+readability/multiline_comment,+readability/multiline_string,+readability/utf8,\
#+runtime/arrays,+runtime/casting,+runtime/explicit,+runtime/init,+runtime/invalid_increment,+runtime/memset,+runtime/operator,+runtime/printf,+runtime/printf_format,+runtime/rtti,+runtime/string,+runtime/threadsafe_fn,\
#+whitespace/blank_line,+whitespace/empty_loop_body,+whitespace/ending_newline,+whitespace/newline,+whitespace/parens,+whitespace/semicolon"
#)
#set(CMAKE_CXX_CPPLINT "cpplint;--extensions=h,hpp,c,cpp;--filter=${CPPLINT_FILTER_OPTIONS}")
# END CPPLINT

add_executable(cliente client/main.cpp classes/view/FondoVista.cpp classes/view/FondoVista.h classes/model/Jugador.cpp classes/model/Jugador.h commons/utils/Vector.cpp commons/utils/Vector.h classes/model/Hud.cpp classes/model/Hud.h classes/model/Helper.cpp classes/model/Helper.h classes/model/Enemigo2.cpp classes/model/Enemigo2.h commons/utils/Log.cpp commons/utils/Log.h classes/model/Enemigo1.cpp classes/model/Enemigo1.h classes/view/JugadorVista.cpp classes/view/JugadorVista.h classes/config/Configuracion.h classes/config/Configuracion.cpp classes/view/Enemigo2Vista.cpp classes/view/Enemigo2Vista.h classes/view/Enemigo1Vista.cpp classes/view/Enemigo1Vista.h classes/view/HelperVista.cpp classes/view/HelperVista.h classes/view/HudVista.cpp classes/view/HudVista.h classes/view/CampoVista.cpp classes/view/CampoVista.h classes/GeneradorDeTexturas.cpp classes/GeneradorDeTexturas.h classes/model/Ticker.h classes/GraphicRenderer.cpp classes/GraphicRenderer.h classes/model/Entidad.h classes/view/TextoVista.cpp classes/view/TextoVista.h classes/model/CampoMovil.cpp classes/model/CampoMovil.h classes/model/Nivel.cpp classes/model/Nivel.h classes/model/SemillaEntidad.cpp classes/model/SemillaEntidad.h classes/config/NivelConfiguracion.cpp classes/config/NivelConfiguracion.h classes/config/FondoConfiguracion.cpp classes/config/FondoConfiguracion.h classes/config/EnemigosConfiguracion.cpp classes/config/EnemigosConfiguracion.h classes/config/ConfiguracionParser.cpp classes/config/ConfiguracionParser.h classes/model/ManagerNiveles.cpp classes/model/ManagerNiveles.h classes/model/NivelIntermedio.cpp classes/model/NivelIntermedio.h classes/view/NivelIntermedioVista.cpp classes/view/NivelIntermedioVista.h classes/model/Titulo.cpp classes/model/Titulo.h classes/view/TituloVista.cpp classes/view/TituloVista.h classes/view/Colores.h commons/protocols/protocolo.h commons/connections/IniciadorComunicacion.cpp commons/connections/IniciadorComunicacion.h commons/connections/ConexionCliente.cpp commons/connections/ConexionCliente.h commons/utils/Utils.cpp commons/utils/Utils.h server/classes/states/EstadoInternoNivel.h)
add_executable(servidor server/main.cpp commons/protocols/protocolo.h commons/connections/ConexionServidor.cpp commons/connections/ConexionServidor.h commons/connections/AceptadorConexiones.cpp commons/connections/AceptadorConexiones.h commons/connections/IniciadorComunicacion.cpp commons/connections/IniciadorComunicacion.h commons/connections/ConexionCliente.cpp commons/connections/ConexionCliente.h server/classes/model/Jugador.cpp server/classes/model/Jugador.h server/classes/model/Hud.cpp server/classes/model/Hud.h server/classes/model/Helper.cpp server/classes/model/Helper.h server/classes/model/Enemigo2.cpp server/classes/model/Enemigo2.h server/classes/model/Enemigo1.cpp server/classes/model/Enemigo1.h commons/utils/Vector.cpp commons/utils/Vector.h commons/utils/Log.cpp commons/utils/Log.h commons/utils/Utils.cpp commons/utils/Utils.h server/classes/model/CampoMovil.cpp server/classes/model/CampoMovil.h server/classes/model/ManagerNiveles.cpp server/classes/model/ManagerNiveles.h server/classes/model/NivelIntermedio.cpp server/classes/model/NivelIntermedio.h server/classes/config/Configuracion.h server/classes/config/Configuracion.cpp server/classes/config/NivelConfiguracion.cpp server/classes/config/NivelConfiguracion.h server/classes/config/EnemigosConfiguracion.cpp server/classes/config/EnemigosConfiguracion.h server/classes/config/ConfiguracionParser.cpp server/classes/config/ConfiguracionParser.h server/classes/model/Nivel.cpp server/classes/model/Nivel.h server/classes/model/SemillaEntidad.cpp server/classes/model/SemillaEntidad.h server/classes/model/Partida.cpp server/classes/model/Partida.h server/classes/model/EntidadEnemigo.h server/classes/states/EstadoInternoCampoMovil.h server/classes/config/FondoConfiguracion.cpp server/classes/config/FondoConfiguracion.h)

target_link_libraries(cliente ${SDL2_LIBRARIES})
target_link_libraries(cliente SDL2 -lSDL2_image)
target_link_libraries(cliente ${JSONCPP_LIBRARIES})