#ifndef CUCURUCHO_PROTOCOLO_H
#define CUCURUCHO_PROTOCOLO_H


#define MAX_ENEMIGOS 15
#define MAX_FONDOS 15
#define LARGO_PATH 255
#define MAX_JUGADORES 4

struct Comando {
	int arriba;
	int abajo;
	int izquierda;
	int derecha;
};

//para el logueo
struct Login {
    char usuario[30];
    char contrasenia[50];
};

struct EstadoHelper {
	int posicionX;
	int posicionY;
	int angulo;
};

struct EstadoJugador {
	int posicionX;
	int posicionY;
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
	EstadoEnemigo estadosEnemigos[MAX_ENEMIGOS];
    EstadoJugador estadosJugadores[MAX_JUGADORES];
};

struct InformacionFondo{
    float pVelocidad;
    char pFondo[LARGO_PATH];
};

struct InformacionNivel {
	int numeroNivel;
	InformacionFondo informacionFondo[MAX_FONDOS];
	char informacionFinNivel[LARGO_PATH];
	float velocidad;
};


#endif //CUCURUCHO_PROTOCOLO_H
