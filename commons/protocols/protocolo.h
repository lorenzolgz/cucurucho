#ifndef CUCURUCHO_PROTOCOLO_H
#define CUCURUCHO_PROTOCOLO_H


#define MAX_ENEMIGOS 15

struct Comando {
	int arriba;
	int abajo;
	int izquierda;
	int derecha;
};

struct EstadoHelper {
	int posicionX;
	int posicionY;
	int angulo;
};

struct EstadoJugador {
	int posicionX;
	int posicionY;
	int contadorVelocidadY;
	EstadoHelper helper1;
	EstadoHelper helper2;
};

struct EstadoEnemigo {
	int posicionX;
	int posicionY;
	int clase;
};

struct EstadoTick {
	EstadoJugador estadoJugador;
	EstadoEnemigo estadosEnemigos[MAX_ENEMIGOS];
};


#endif //CUCURUCHO_PROTOCOLO_H
