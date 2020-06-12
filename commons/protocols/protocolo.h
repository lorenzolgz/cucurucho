#ifndef CUCURUCHO_PROTOCOLO_H
#define CUCURUCHO_PROTOCOLO_H


#define MAX_ENEMIGOS 15
#define MAX_FONDOS 15
#define LARGO_PATH 255
#define MAX_JUGADORES 4
#define LARGO_USERNAME 30
#define LARGO_PASSWORD 30

// Parametros para controlar la cantidad maxima de elementos de
// las colas del cliente y del servidor
#define MAX_COLA_CLIENTE 1
#define MAX_COLA_SERVIDOR 1

// Tipos de mensajes
enum {
    INFORMACION_NIVEL,
    ESTADO_TICK,
    COMANDO,
    ESTADO_LOGIN
};

// Codigos Estado Login
#define LOGIN_SIN_CONEXION -2
#define LOGIN_FALLO -1
#define LOGIN_PENDIENTE 0
#define LOGIN_ESPERAR 1
#define LOGIN_COMENZAR 2

struct Comando {
	int nroJugador;
	int arriba;
	int abajo;
	int izquierda;
	int derecha;
};

//para el logueo
struct Login {
    char usuario[LARGO_USERNAME];
    char contrasenia[LARGO_PASSWORD];
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
    int estadoLogin;
    char jugador1[LARGO_USERNAME];
    char jugador2[LARGO_USERNAME];
    char jugador3[LARGO_USERNAME];
    char jugador4[LARGO_USERNAME];
};


#endif //CUCURUCHO_PROTOCOLO_H
