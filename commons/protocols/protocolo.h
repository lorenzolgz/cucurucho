#ifndef CUCURUCHO_PROTOCOLO_H
#define CUCURUCHO_PROTOCOLO_H


#define MAX_ENEMIGOS 15
#define MAX_JUGADORES 4
#define LARGO_RECURSO 10

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

struct InformacionNivel {
	int muchaData;
};


#endif //CUCURUCHO_PROTOCOLO_H
