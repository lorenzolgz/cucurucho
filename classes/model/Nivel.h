#ifndef CUCURUCHO_NIVEL_H
#define CUCURUCHO_NIVEL_H


#include "CampoMovil.h"
#include "Ticker.h"
#include "SemillaEntidad.h"

#define PANTALLA_ANCHO 960
#define PANTALLA_ALTO 672

class Nivel : public Ticker {
public:
	Nivel(NivelConfiguracion* nivelConfig, Jugador* jugador, InformacionFondo* informacionFondo);

	void crearEnemigos(int cantClase1, int cantClase2);
	void tick() override;
    void crearEnemigosDeClase(int tipoDeEnemigo, int cantDeEnemigos);
	bool termino();
	void setEstado(std::list<EstadoEnemigo> estadosEnemigos);

private:
	float ancho;
	int alto;
	Hud* hud;
	CampoMovil* campo;
	list<SemillaEntidad*> semillasEntidades;
    int numeroDeNivel;
    float velocidad;

	CampoMovil *crearCampo(NivelConfiguracion *nivelConfig, Jugador* jugador, struct InformacionFondo* informacionFondo);
	void plantarSemillasEnCampo();
};


#endif //CUCURUCHO_NIVEL_H