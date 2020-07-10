#ifndef CUCURUCHO_VIDAENTIDAD_H
#define CUCURUCHO_VIDAENTIDAD_H


#define DANIO_TOTAL -1

class VidaEntidad {
public:
	VidaEntidad(int energia);
	virtual int getEnergia();
	virtual void procesarColision(const int tipoEntidad);

protected:
	// Metodos que se llaman en el template method
	virtual int danioColisionJugador();
	virtual int danioColisionEnemigo1();
	virtual int danioColisionEnemigo2();
	virtual int danioColisionDisparoJugador();

private:
	int energia;

	// Template method.
	int calcularDanioPorColision(const int tipoEntidad);
};


#endif //CUCURUCHO_VIDAENTIDAD_H