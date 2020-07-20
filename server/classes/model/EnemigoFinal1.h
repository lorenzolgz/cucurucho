#ifndef CUCURUCHO_ENEMIGOFINAL1_H
#define CUCURUCHO_ENEMIGOFINAL1_H


#include "EntidadEnemigo.h"

const int ENEMIGO_FINAL1_ANCHO = 375;
const int ENEMIGO_FINAL1_ALTO = 288;

class EnemigoFinal1 : public EntidadEnemigo {
public:
	EnemigoFinal1(float x, float y, float velocidadX, std::map<int, Jugador*>* jugadores, CampoMovil* campo);

	EstadoEnemigo state() override;
	float getVelocidadX() override;
	void setPosicion(Vector nuevaPosicion) override;
	void tick() override;
	std::list<Forma> getFormas() override;
	int getTipoEntidad() override;
	void disparar(Vector vector) override;
	std::list<EntidadEnemigo*> getExtensiones();

private:
	float velocidadX;
	std::list<EntidadEnemigo*> extensiones;

	void crearExtensiones(std::map<int, Jugador*>* jugadores);

	CampoMovil *campo;
};


#endif //CUCURUCHO_ENEMIGOFINAL1_H
