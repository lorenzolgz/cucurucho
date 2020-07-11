#ifndef CUCURUCHO_ENEMIGOFINAL1_H
#define CUCURUCHO_ENEMIGOFINAL1_H


#include "EntidadEnemigo.h"

const int ENEMIGO_FINAL1_ANCHO = 375;
const int ENEMIGO_FINAL1_ALTO = 288;

class EnemigoFinal1 : public EntidadEnemigo {
public:
public:
	EnemigoFinal1(float x, float y, float velocidadX, std::map<int, Jugador*>* jugadores);

	EstadoEnemigo state() override;
	float getVelocidadX() override;
	void setPosicion(Vector nuevaPosicion) override;
	void tick() override;
	Vector getPosicion() override;
	int getAncho() override;
	int getAlto() override;
	int getTipoEntidad() override;
	std::list<Forma> getFormas() override;
	VidaEntidad *getVidaEntidad() override;

private:
	Vector posicion;
	float velocidadX;
	VidaEntidad* vida;
};


#endif //CUCURUCHO_ENEMIGOFINAL1_H
