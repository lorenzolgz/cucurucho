#include "EnemigosConfiguracion.h"

EnemigosConfiguracion::EnemigosConfiguracion(int enemigosClase1, int enemigosClase2, bool enemigoFinal) : clase1(enemigosClase1),
																										  clase2(enemigosClase2),
																										  final(enemigoFinal) {}

int EnemigosConfiguracion::getEnemigosClase1() const {
	return clase1;
}

int EnemigosConfiguracion::getEnemigosClase2() const {
	return clase2;
}

bool EnemigosConfiguracion::isFinal() const {
	return final;
}
