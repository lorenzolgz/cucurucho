#ifndef CUCURUCHO_FORMA_H
#define CUCURUCHO_FORMA_H


class Forma {
public:
	Forma(float posX, float posY, float ancho, float alto);

	bool colisiona(Forma otraForma);
	float getPosX();
	float getPosY();
	int getAncho();
	int getAlto();

private:
	float posX;
	float posY;
	int ancho;
	int alto;
};


#endif //CUCURUCHO_FORMA_H
