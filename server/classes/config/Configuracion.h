#ifndef CUCURUCHO_CONFIGURACION_H
#define CUCURUCHO_CONFIGURACION_H

#include <string>
#include <queue>
#include <jsoncpp/json/json.h>
#include "NivelConfiguracion.h"

class Configuracion {
public:
    Configuracion(int altoPantalla, int anchoPantalla, int escalaPantalla, std::string nivelLog,
                  std::list<NivelConfiguracion *> niveles, int cantidadJugadores, bool std_out, int i, int i1);

    int getAltoPantalla();
    int getAnchoPantalla();
    int getEscalaPantalla();
    std::string getNivelLog();
	const std::list<NivelConfiguracion *> &getNiveles() const;
	int getCantidadJugadores();
    bool isStdOut() const;

    int getMaxColaEmisora() const;

    int getMaxColaReceptora() const;

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
};


#endif //CUCURUCHO_CONFIGURACION_H
