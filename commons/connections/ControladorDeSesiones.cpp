//
// Created by ailen-magali on 3/6/20.
//

#include "ControladorDeSesiones.h"


ControladorDeSesiones::ControladorDeSesiones(ConexionServidor* conexionServidor, int nroJugador){
    this->conexionServidor = conexionServidor;
    ifstream archivo(JSON_USUARIOS, ifstream::binary);
    archivo >> this->jsonUsuarios;
    this->contrasenias = jsonUsuarios["usuariosRegistrados"];
	this->nroJugador = nroJugador;
}


// Dada la `conexionServidor` de la clase, se pide por la misma credenciales de logueo.
// Si las credenciales no estan en el archivo `usuarios.json`, se envia el estado
// de login correspondiente, se cierra la conexion y se devuelve false.
// Caso contrario, se le envia el numero de jugador y se devuelve true.
bool ControladorDeSesiones::iniciarSesion(map<string, bool> &jugadoresConectados) {

	bool ok = true;

	//pedirle un usuario y contraseña al cliente
	struct Login login;
	pedirCredenciales(&login);

	char *usuario;
	usuario = login.usuario;
	char *contrasenia;
	contrasenia = login.contrasenia;

	//verifico que el usuario esté registrado
	if (!usuarioEstaRegistrado(usuario, contrasenia) || !controlarQueNoIngreseUsuarioYaEnJuego(usuario, jugadoresConectados)) {
        this->conexionServidor->enviarEstadoLogin({LOGIN_FALLO});
		this->conexionServidor->cerrar();
		ok = false;
	} else {
        this->conexionServidor->enviarEstadoLogin({nroJugador, LOGIN_ESPERAR});
		this->usuarioConectado = std::string(usuario);
	}

	return ok;
}

bool ControladorDeSesiones::usuarioEstaRegistrado(char* usuario, char* contrasenia) {
	// Chequeo si el usuario está registrado
	if (this->contrasenias[usuario].empty()) {
	    return false;
	}
	// Chequeo si la contrasenia es correcta
	if (strcmp(this->contrasenias[usuario].asCString(), contrasenia) != 0) {
	    return false;
	}

	return true;

	// Si está registrado, verifico la contraseña
//	if (usuarioRegistrado) {
//		contraseniaCorrecta = strcmp(this->contrasenias[usuario].asCString(), contrasenia) == 0;
//		while (!contraseniaCorrecta) {
//			// TODO esto funciona pero para una única vez
//			struct EstadoLogin estadoLogin;
//			estadoLogin.nroJugador = nroJugador;
//			this->conexionServidor->enviarEstadoLogin(estadoLogin);
//			pedirCredenciales(login);
//			contraseniaCorrecta = strcmp(this->contrasenias[usuario].asCString(), login.contrasenia);
//		}
//	}
//
//	struct EstadoLogin estadoLogin;
//	estadoLogin.nroJugador = nroJugador;
//	this->conexionServidor->enviarEstadoLogin(estadoLogin);

}

void ControladorDeSesiones::pedirCredenciales(Login *login){
    nlohmann::json mensajeJson = this->conexionServidor->recibirMensaje();
    strcpy(login->usuario, std::string(mensajeJson["usuario"]).c_str());
    strcpy(login->contrasenia, std::string(mensajeJson["contrasenia"]).c_str());
}

void ControladorDeSesiones::setServidor(ConexionServidor *servidor) {
    this->conexionServidor = servidor;
}

string ControladorDeSesiones::userConectado(){
    return this->usuarioConectado;
}

bool ControladorDeSesiones::controlarQueNoIngreseUsuarioYaEnJuego(std::string usuario, map<string, bool> &jugadoresConectados) {
	if (jugadoresConectados.count(usuario) == 1) { //si existe ese usuario en el map
		if (jugadoresConectados[usuario]) {//si ese usuario está jugando
			//TODO informar que ya se encuentra en juego alguien con ese nombre de usuario
			cout << "Ya se encuentra en juego alguien con ese nombre de usuario" << endl;
			return false;
		} else if (!jugadoresConectados[usuario]) { //TODO si ese usuario se conectó en esta partida pero se fue, ponerle false
			cout << "Te desconectaste y volviste" << endl;
			jugadoresConectados[usuario] = true; //ver reconexión
		}
	} else { //si no se conectó en esta partida alguien con ese nombre de usuario
		cout << "No se encuentra en juego todavía alguien con ese nombre de usuario" << endl;
		jugadoresConectados[usuario] = true;
	}
	return true;
}

