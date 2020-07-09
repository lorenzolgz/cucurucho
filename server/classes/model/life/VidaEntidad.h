#ifndef CUCURUCHO_VIDAENTIDAD_H
#define CUCURUCHO_VIDAENTIDAD_H


#define DANIO_TOTAL -1

class VidaEntidad {
public:
	virtual int getEnergiaInicial() = 0;

	void vivir();
	int getEnergia();
	virtual void procesarColision(const int tipoEntidad);

protected:
	// Template method
	virtual int danioColisionJugador();
	virtual int danioColisionEnemigo1();
	virtual int danioColisionEnemigo2();

private:
	int energia;

	// Template method.
	int calcularDanioPorColision(const int tipoEntidad);
};


#endif //CUCURUCHO_VIDAENTIDAD_H
