cmake_minimum_required(VERSION 3.7)

project(cucurucho)

find_package(PkgConfig REQUIRED)
find_package(SDL2 REQUIRED)

pkg_check_modules(SDL2 REQUIRED sdl2)
pkg_check_modules(JSONCPP jsoncpp)

link_libraries(${JSONCPP_LIBRARIES})

include_directories(${SDL2_INCLUDE_DIRS})

link_libraries(stdc++fs)

set(CMAKE_CXX_FLAGS -pthread)
set(CMAKE_CXX_STANDARD 11)


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


add_executable(cliente
        client/main.cpp
        client/classes/view/elements/FondoVista.cpp
        client/classes/view/elements/FondoVista.h
        commons/utils/Vector.cpp
        commons/utils/Vector.h
        commons/utils/Log.cpp
        commons/utils/Log.h
        commons/utils/Utils.cpp
        commons/utils/Utils.h
        client/classes/view/elements/JugadorVista.cpp
        client/classes/view/elements/JugadorVista.h
        client/classes/view/elements/Enemigo2Vista.cpp
        client/classes/view/elements/Enemigo2Vista.h
        client/classes/view/elements/Enemigo1Vista.cpp
        client/classes/view/elements/Enemigo1Vista.h
        client/classes/view/elements/HelperVista.cpp
        client/classes/view/elements/HelperVista.h
        client/classes/view/HudVista.cpp
        client/classes/view/HudVista.h
        client/classes/view/CampoVista.cpp
        client/classes/view/CampoVista.h
        client/classes/GeneradorDeTexturas.cpp
        client/classes/GeneradorDeTexturas.h
        client/classes/GraphicRenderer.cpp
        client/classes/GraphicRenderer.h
        client/classes/view/TextoVista.cpp
        client/classes/view/TextoVista.h
        client/classes/view/NivelIntermedioVista.cpp
        client/classes/view/NivelIntermedioVista.h
        client/classes/view/TituloVista.cpp
        client/classes/view/TituloVista.h
        client/classes/view/Titulo.cpp
        client/classes/view/Titulo.h
        client/classes/view/Colores.h
        client/classes/view/ManagerVista.cpp
        client/classes/view/ManagerVista.h
        client/classes/config/ConfiguracionParser.cpp
        client/classes/config/ConfiguracionParser.h
        commons/connections/ConexionCliente.cpp
        commons/connections/ConexionCliente.h
        commons/connections/IniciadorComunicacion.cpp
        commons/connections/IniciadorComunicacion.h
        commons/protocols/protocolo.h
        commons/utils/Constantes.h
        client/classes/view/ToastVista.cpp
        client/classes/view/ToastVista.h
        client/classes/GestorSDL.cpp
        client/classes/GestorSDL.h
        commons/ColaBloqueante.h
        commons/Thread.cpp
        commons/Thread.h
        commons/connections/ConexionUtils.h
        commons/connections/Conexion.cpp commons/connections/Conexion.h
        libraries/json/json.hpp
        client/classes/HiloConexionCliente.cpp client/classes/HiloConexionCliente.h
        client/classes/Partida.cpp client/classes/Partida.h
        client/classes/ManagerJuego.cpp client/classes/ManagerJuego.h
        commons/connections/ConexionExcepcion.h
        client/classes/config/Configuracion.cpp
        client/classes/config/Configuracion.h
        client/classes/view/elements/DisparoJugadorVista.cpp
        client/classes/view/elements/DisparoJugadorVista.h client/classes/view/elements/DisparoEnemigoVista.cpp client/classes/view/elements/DisparoEnemigoVista.h
        client/classes/Audio.cpp client/classes/Audio.h client/classes/Musica.cpp client/classes/Musica.h client/classes/EfectoSonido.cpp client/classes/EfectoSonido.h client/classes/view/elements/EnemigoFinal1Vista.cpp client/classes/view/elements/EnemigoFinal1Vista.h client/classes/view/elements/ExplosionVista.cpp client/classes/view/elements/ExplosionVista.h client/classes/view/elements/EnemigoFinal1ExtVista.cpp client/classes/view/elements/EnemigoFinal1ExtVista.h)

add_executable(servidor
        server/main.cpp
        commons/protocols/protocolo.h
        commons/connections/ConexionServidor.cpp
        commons/connections/ConexionServidor.h
        commons/connections/AceptadorConexiones.cpp
        commons/connections/AceptadorConexiones.h
        commons/connections/IniciadorComunicacion.cpp
        commons/connections/IniciadorComunicacion.h
        commons/connections/ConexionCliente.cpp
        commons/connections/ConexionCliente.h
        server/classes/model/Jugador.cpp
        server/classes/model/Jugador.h
        server/classes/model/Helper.cpp
        server/classes/model/Helper.h
        server/classes/model/Enemigo2.cpp
        server/classes/model/Enemigo2.h
        server/classes/model/Enemigo1.cpp
        server/classes/model/Enemigo1.h
        commons/utils/Vector.cpp
        commons/utils/Vector.h
        commons/utils/Log.cpp
        commons/utils/Log.h
        commons/utils/Utils.cpp
        commons/utils/Utils.h
        server/classes/model/CampoMovil.cpp
        server/classes/model/CampoMovil.h
        server/classes/model/ManagerNiveles.cpp
        server/classes/model/ManagerNiveles.h
        server/classes/config/Configuracion.h
        server/classes/config/Configuracion.cpp
        server/classes/config/NivelConfiguracion.cpp
        server/classes/config/NivelConfiguracion.h
        server/classes/config/EnemigosConfiguracion.cpp
        server/classes/config/EnemigosConfiguracion.h
        server/classes/config/ConfiguracionParser.cpp
        server/classes/config/ConfiguracionParser.h
        server/classes/model/Nivel.cpp
        server/classes/model/Nivel.h
        server/classes/model/SemillaEntidad.cpp
        server/classes/model/SemillaEntidad.h
        server/classes/model/Partida.cpp
        server/classes/model/Partida.h
        server/classes/model/EntidadEnemigo.h
        server/classes/states/EstadoInternoCampoMovil.h
        server/classes/config/FondoConfiguracion.cpp
        server/classes/config/FondoConfiguracion.h
        commons/connections/ControladorDeSesiones.cpp
        commons/connections/ControladorDeSesiones.h
        commons/Thread.cpp
        commons/Thread.h
        server/classes/HiloOrquestadorPartida.cpp
        server/classes/HiloOrquestadorPartida.h
        commons/ColaBloqueante.h
        server/classes/HiloConexionServidor.cpp server/classes/HiloConexionServidor.h
        commons/connections/ConexionUtils.h
        commons/connections/Conexion.cpp commons/connections/Conexion.h
        libraries/json/json.hpp
        commons/connections/ConexionExcepcion.h
        server/classes/HiloAceptadorConexiones.cpp server/classes/HiloAceptadorConexiones.h
        commons/connections/AceptarConexionExcepcion.h
        server/classes/config/UsuariosConfiguracion.cpp server/classes/config/UsuariosConfiguracion.h
        server/classes/model/life/VidaJugadorMortal.cpp server/classes/model/life/VidaJugadorMortal.h
        server/classes/model/life/VidaEntidad.cpp server/classes/model/life/VidaEntidad.h
        server/classes/model/life/VidaJugadorInvencible.cpp server/classes/model/life/VidaJugadorInvencible.h
        server/classes/model/entities/Forma.cpp server/classes/model/entities/Forma.h
        server/classes/model/life/VidaEnemigo1.cpp server/classes/model/life/VidaEnemigo1.h
        server/classes/model/life/VidaEnemigo2.cpp server/classes/model/life/VidaEnemigo2.h
        server/classes/model/entities/Entidad.cpp server/classes/model/entities/Entidad.h
        commons/connections/ConexionExcepcion.h server/classes/HiloAceptadorConexiones.cpp server/classes/HiloAceptadorConexiones.h commons/connections/AceptarConexionExcepcion.h server/classes/config/UsuariosConfiguracion.cpp server/classes/config/UsuariosConfiguracion.h server/classes/model/entities/projectiles/Disparo.cpp server/classes/model/entities/projectiles/Disparo.h server/classes/model/life/VidaProyectil.cpp server/classes/model/life/VidaProyectil.h server/classes/model/life/VidaJugador.cpp server/classes/model/life/VidaJugador.h server/classes/model/ais/IAEnemigo.h server/classes/model/ais/IAEnemigoPatron1.cpp server/classes/model/ais/IAEnemigoPatron1.h server/classes/model/ais/IAEnemigoPatron2.cpp server/classes/model/ais/IAEnemigoPatron2.h server/classes/model/EnemigoFinal1.cpp server/classes/model/EnemigoFinal1.h
        server/classes/model/ais/default/IAHorizontal.cpp server/classes/model/ais/default/IAHorizontal.h server/classes/model/ais/default/IAEstatico.cpp server/classes/model/ais/default/IAEstatico.h server/classes/model/ais/default/IACircular.cpp server/classes/model/ais/default/IACircular.h server/classes/model/ais/IAEnemigoPatron3.cpp server/classes/model/ais/IAEnemigoPatron3.h server/classes/model/life/VidaEnemigoFinal1.cpp server/classes/model/life/VidaEnemigoFinal1.h server/classes/model/ExtensionNivel.cpp server/classes/model/ExtensionNivel.h server/classes/model/entities/projectiles/DisparoEnemigo1.cpp server/classes/model/entities/projectiles/DisparoEnemigo1.h server/classes/model/entities/projectiles/EntidadDisparo.h server/classes/model/entities/projectiles/DisparoEnemigo2.cpp server/classes/model/entities/projectiles/DisparoEnemigo2.h)

target_link_libraries(cliente ${SDL2_LIBRARIES})
target_link_libraries(cliente SDL2 -lSDL2_image -lSDL2_mixer)
target_link_libraries(cliente ${JSONCPP_LIBRARIES})
