#ifndef CUCURUCHO_IACIRCULAR_H
#define CUCURUCHO_IACIRCULAR_H


#include <map>
#include "../IAEnemigo.h"
#include "../../EntidadEnemigo.h"

class IACircular : public IAEnemigo {
public:
	IACircular(EntidadEnemigo* entidadEnemigo, std::map<int, Jugador*>* jugadores, int anguloInicialGrados, bool sentidoHorario, Vector factor, float radio, int totalAnguloGrados, IAEnemigo* next);

	IAEnemigo* tick() override;
	void inicializar() override;
	void setNext(IAEnemigo *nuevoNext);

private:
	EntidadEnemigo* entidadEnemigo;
	std::map<int, Jugador*>* jugadores;
	IAEnemigo* next;
	bool primerTick;
	int ticks;
	Vector centro;
	int anguloInicialGrados;
	bool sentidoHorario;
	float radio;
	int totalAnguloGrados;
	Vector factorModificadorPosicion;

	Vector calcularDeltaPosicion(int anguloGrados);
};


#endif //CUCURUCHO_IACIRCULAR_H
