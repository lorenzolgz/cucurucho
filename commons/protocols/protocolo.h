#ifndef CUCURUCHO_PROTOCOLO_H
#define CUCURUCHO_PROTOCOLO_H

#include <list>
#define LARGO_PATH 255
#define MAX_JUGADORES 4
#define LARGO_USERNAME 11
#define LARGO_PASSWORD 11
#define TIMEOUT_MENSAJES 4

// Parametros para controlar la cantidad maxima de elementos de
// las colas del cliente y del servidor
#define MAX_COLA_CLIENTE 2
#define MAX_COLA_RECEPTORA_SERVIDOR 1
#define MAX_COLA_EMISORA_SERVIDOR 2

// Codigos Estado Login
#define LOGIN_ERROR_EN_PARTIDA -6
#define LOGIN_ERROR_USUARIO_EN_JUEGO -5
#define LOGIN_ERROR_PASS_INVALIDA -4
#define LOGIN_ERROR_USUARIO_INEXISTENTE -3
#define LOGIN_ESPERANDO_RESPUESTA -2
#define LOGIN_SIN_CONEXION -1
#define LOGIN_PENDIENTE 0
#define LOGIN_ESPERAR 1
#define LOGIN_COMENZAR 2
#define LOGIN_FIN 3

// Tiempo en segundos entre LOGIN_COMENZAR y LOGIN_FIN
#define TIMEOUT_LOGIN_FIN 2

// Tiempo en segundos de pasaje entre niveles
#define TIMEOUT_PROXIMO_NIVEL 5

//Fin de Juego
#define FIN_DE_JUEGO -1

// Tipos de mensajes
enum {
    INFORMACION_NIVEL,
    ESTADO_TICK,
    COMANDO,
    ESTADO_LOGIN,
    MENSAJE_PING
};

struct Comando {
	int nroJugador;
	int arriba;
	int abajo;
	int izquierda;
	int derecha;
	int disparo;
	int invencible;
};

//para el logueo
struct Login {
    char usuario[LARGO_USERNAME];
    char contrasenia[LARGO_PASSWORD];
};

struct EstadoDisparo {
  EstadoDisparo(): posicionX(-200), posicionY(-200), nroJugador(0), energia(1) {}
  int posicionX;
  int posicionY;
  int nroJugador;
  int energia;
  int inicio;
};

struct EstadoHelper {
    EstadoHelper(): posicionX(-1000), posicionY(-1000), angulo(0) {}
	int posicionX;
	int posicionY;
	int angulo;
};

struct EstadoJugador {
    EstadoJugador(): posicionX(-1000), posicionY(-1000), puntos(0), cantidadVidas(0), presente(0) {}
	int posicionX;
	int posicionY;
	EstadoHelper helper1;
	EstadoHelper helper2;
	char usuario[LARGO_USERNAME];
	int energia;
	int cantidadVidas;
	int esInvencible;
	int estaMuerto;
    int presente;
	int puntos;
	std::list<int> puntosParciales;
};

struct EstadoEnemigo {
	EstadoEnemigo(): posicionX(-200), posicionY(-200), energia(0) {}
	int posicionX;
	int posicionY;
	int energia;
	int clase;
};

struct EstadoTick {
    EstadoTick(): posX(0) {}
    int numeroNivel;
	int nuevoNivel;
	int posX;
	std::list<EstadoEnemigo> estadosEnemigos;
    std::list<EstadoDisparo> estadosDisparos;
    std::list<EstadoDisparo> estadosDisparosEnemigos;
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
    char audioNivel[LARGO_PATH];
	std::list<InformacionFondo> informacionFondo;
};

struct EstadoLogin {
    int nroJugador;
    int estadoLogin;
    int cantidadJugadores;
    char jugadores[MAX_JUGADORES][LARGO_USERNAME];
};


#endif //CUCURUCHO_PROTOCOLO_H
