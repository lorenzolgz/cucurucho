#ifndef CUCURUCHO_VIDAENTIDAD_H
#define CUCURUCHO_VIDAENTIDAD_H


#define DANIO_TOTAL -1

class VidaEntidad {
public:
	virtual int getEnergiaInicial() = 0;

	void vivir();
	int getEnergia();
	void procesarColision(const int tipoEntidad);

	// !!!!! actually add protected
	// protected methods
	virtual int danioColisionJugador();
	virtual int danioColisionEnemigo1();
	virtual int danioColisionEnemigo2();

	// protected atributes
	int energia;

private:
	int calcularDanioPorColision(const int tipoEntidad);
};


#endif //CUCURUCHO_VIDAENTIDAD_H
