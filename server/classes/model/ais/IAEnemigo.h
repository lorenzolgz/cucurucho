#ifndef CUCURUCHO_IAENEMIGO_H
#define CUCURUCHO_IAENEMIGO_H


class IAEnemigo {
public:
	virtual IAEnemigo* tick() = 0;

	virtual void inicializar() {
		return;
	}
};


#endif //CUCURUCHO_IAENEMIGO_H
