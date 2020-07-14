#ifndef CUCURUCHO_VIDAENTIDAD_H
#define CUCURUCHO_VIDAENTIDAD_H


#define DANIO_TOTAL -1

class VidaEntidad {
public:
	VidaEntidad(int energia);
	virtual int getEnergia();
	virtual void procesarColision(const int tipoEntidad);
	virtual bool estaMuerto();

protected:
	// Metodos que se llaman en el template method
	virtual int danioColisionJugador();
	virtual int danioColisionEnemigo1();
	virtual int danioColisionEnemigo2();
	virtual int danioColisionDisparoJugador();
    virtual int danioColisionDisparoEnemigo1();
    virtual int danioColisionDisparoEnemigo2();


private:
	int energia;

	// Template method.
	int calcularDanioPorColision(const int tipoEntidad);

	int danioColisionEnemigoFinal1();

};


#endif //CUCURUCHO_VIDAENTIDAD_H
