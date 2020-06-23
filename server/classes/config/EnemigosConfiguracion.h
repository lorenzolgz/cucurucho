#ifndef CUCURUCHO_ENEMIGOSCONFIGURACION_H
#define CUCURUCHO_ENEMIGOSCONFIGURACION_H


class EnemigosConfiguracion {
public:
	EnemigosConfiguracion(int enemigosClase1, int enemigosClase2);

	int getEnemigosClase1() const;
	int getEnemigosClase2() const;

private:
	int clase1;
	int clase2;
};


#endif //CUCURUCHO_ENEMIGOSCONFIGURACION_H
