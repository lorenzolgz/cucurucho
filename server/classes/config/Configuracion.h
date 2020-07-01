#ifndef CUCURUCHO_CONFIGURACION_H
#define CUCURUCHO_CONFIGURACION_H

#include <string>
#include <queue>
#include <jsoncpp/json/json.h>
#include "NivelConfiguracion.h"
#include "UsuariosConfiguracion.h"

class Configuracion {
public:
    Configuracion(int altoPantalla, int anchoPantalla, int escalaPantalla, std::string nivelLog,
                  std::list<NivelConfiguracion *> niveles, int cantidadJugadores, bool std_out,
                  int maxColaEmisora, int maxColaReceptora, UsuariosConfiguracion *usuariosConfiguracion);

    int getAltoPantalla();
    int getAnchoPantalla();
    int getEscalaPantalla();
    std::string getNivelLog();
	const std::list<NivelConfiguracion *> &getNiveles() const;
	int getCantidadJugadores();
    bool isStdOut() const;

    int getMaxColaEmisora() const;

    int getMaxColaReceptora() const;

    UsuariosConfiguracion *getUsuarios() const;

private:
    int altoPantalla;
    int anchoPantalla;
    int escalaPantalla;
    int cantidadJugadores;
    bool std_out;
    std::string nivelLog;
	std::list<NivelConfiguracion*> niveles;
    int maxColaEmisora;
    int maxColaReceptora;
    UsuariosConfiguracion* usuarios;
};


#endif //CUCURUCHO_CONFIGURACION_H
