//
// Created by ailen-magali on 3/6/20.
//

#include "ControladorDeSesiones.h"
#include "ConexionExcepcion.h"


ControladorDeSesiones::ControladorDeSesiones(ConexionServidor *conexionServidor, list<ConexionServidor *> *conexiones,
                                             int nroJugador, bool modificarConexiones) {
    this->conexionServidor = conexionServidor;
    this->conexiones = conexiones;
    ifstream archivo(JSON_USUARIOS, ifstream::binary);
    archivo >> this->jsonUsuarios;
    this->contrasenias = jsonUsuarios["usuariosRegistrados"];
	this->nroJugador = nroJugador;
	this->modificarConexiones = modificarConexiones;
}


// Dada la `conexionServidor` de la clase, se pide por la misma credenciales de logueo.
// Si las credenciales no estan en el archivo `usuarios.json`, se envia el estado
// de login correspondiente, se cierra la conexion y se devuelve false.
// Caso contrario, se le envia el numero de jugador y se devuelve true.
bool ControladorDeSesiones::iniciarSesion() {

	bool ok = true;

	//pedirle un usuario y contraseña al cliente
	struct Login login;
	pedirCredenciales(&login);

	char *usuario;
	usuario = login.usuario;
	char *contrasenia;
	contrasenia = login.contrasenia;

	//verifico que el usuario esté registrado
	if (!usuarioEstaRegistrado(usuario, contrasenia)
	        || !controlarQueNoIngreseUsuarioYaEnJuego(usuario)) {
        this->conexionServidor->enviarEstadoLogin({LOGIN_FALLO});
		this->conexionServidor->cerrar();
		ok = false;
	} else {
        this->conexionServidor->enviarEstadoLogin({nroJugador, LOGIN_ESPERAR});
		this->usuarioConectado = std::string(usuario);
		conexionServidor->setUsuario(std::string(usuario));
		conexionServidor->setNroJugador(nroJugador);
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
}

void ControladorDeSesiones::pedirCredenciales(Login *login){
    nlohmann::json mensajeJson = this->conexionServidor->recibirMensaje();
    strcpy(login->usuario, std::string(mensajeJson["usuario"]).c_str());
    strcpy(login->contrasenia, std::string(mensajeJson["contrasenia"]).c_str());
}

void ControladorDeSesiones::setServidor(ConexionServidor *servidor) {
    this->conexionServidor = servidor;
}

string ControladorDeSesiones::getUsuarioConectado(){
    return this->usuarioConectado;
}

bool ControladorDeSesiones::controlarQueNoIngreseUsuarioYaEnJuego(std::string usuario) {
    if (conexiones == nullptr) {
        return true;
    }

    auto j = conexiones->begin();
    while (j != conexiones->end()) {
        if ((*j)->getUsuario() != usuario) {
            j++;
            continue;
        }
        try {
            nlohmann::json json;
            json["tipoMensaje"] = MENSAJE_PING;
            (*j)->enviarMensaje(json);
            return false; // Si se recibe el ping, ese usuario ya se encuentra en el juego
        } catch (const ConexionExcepcion& e) {
            if (modificarConexiones) j = conexiones->erase(j);
            else j++;
        }
    }

    return true;
}

ConexionServidor *ControladorDeSesiones::getConexionServidor() const {
    return conexionServidor;
}

