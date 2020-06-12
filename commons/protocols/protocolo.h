#ifndef CUCURUCHO_PROTOCOLO_H
#define CUCURUCHO_PROTOCOLO_H


#define MAX_ENEMIGOS 15
#define MAX_FONDOS 15
#define LARGO_PATH 255
#define MAX_JUGADORES 4

// Tipos de mensajes
#define INFORMACION_NIVEL 0
#define ESTADO_TICK 1
#define COMANDO 2

// Codigos Estado Login
#define LOGIN_SIN_CONEXION -2
#define LOGIN_FALLO -1
#define LOGIN_PENDIENTE 0

struct Comando {
	int nroJugador;
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
    EstadoHelper(): posicionX(-200), posicionY(-200) {}
	int posicionX;
	int posicionY;
	int angulo;
};

struct EstadoJugador {
    EstadoJugador(): posicionX(-200), posicionY(-200) {}
	int posicionX;
	int posicionY;
	EstadoHelper helper1;
	EstadoHelper helper2;
};

struct EstadoEnemigo {
    EstadoEnemigo(): posicionX(-200), posicionY(-200) {}
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
    float velocidad;
    char informacionFinNivel[LARGO_PATH];
	InformacionFondo informacionFondo[MAX_FONDOS];
};

struct EstadoLogin {
	int nroJugador;
};


#endif //CUCURUCHO_PROTOCOLO_H
