#ifndef CUCURUCHO_ENEMIGOSCONFIGURACION_H
#define CUCURUCHO_ENEMIGOSCONFIGURACION_H


class EnemigosConfiguracion {
public:
	EnemigosConfiguracion(int enemigosClase1, int enemigosClase2, bool enemigoFinal);

	int getEnemigosClase1() const;
	int getEnemigosClase2() const;
	bool isFinal() const;

private:
	int clase1;
	int clase2;
	bool final;
};


#endif //CUCURUCHO_ENEMIGOSCONFIGURACION_H
