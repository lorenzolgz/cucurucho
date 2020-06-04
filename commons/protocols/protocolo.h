#ifndef CUCURUCHO_PROTOCOLO_H
#define CUCURUCHO_PROTOCOLO_H


#define MAX_ENEMIGOS 15
#define LARGO_RECURSO 10
#define MAX_FONDOS 15
#define LARGO_PATH 255

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
	int nuevoNivel;
	EstadoJugador estadoJugador;
	EstadoEnemigo estadosEnemigos[MAX_ENEMIGOS];
};

struct InformacionFondo{
    float pVelocidad;
    char pFondo[LARGO_PATH];
};

struct InformacionNivel {
	int numeroNivel;
	InformacionFondo informacionFondo[MAX_FONDOS];
	char informacionFinNivel[LARGO_PATH];
};


#endif //CUCURUCHO_PROTOCOLO_H
