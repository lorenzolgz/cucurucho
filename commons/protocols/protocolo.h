#ifndef CUCURUCHO_PROTOCOLO_H
#define CUCURUCHO_PROTOCOLO_H


#define MAX_ENEMIGOS 15
#define LARGO_RECURSO 10

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

struct InformacionNivel {
	int muchaData;
};


#endif //CUCURUCHO_PROTOCOLO_H
