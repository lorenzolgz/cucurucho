//
// Created by ailen-magali on 3/6/20.
//

#include "ControladorDeSesiones.h"
#include "ConexionExcepcion.h"


ControladorDeSesiones::ControladorDeSesiones(ConexionServidor *conexionServidor, list<ConexionServidor *> *conexiones,
                                             int nroJugador, bool usuarioEnJuego) {
    this->conexionServidor = conexionServidor;
    this->conexiones = conexiones;
    ifstream archivo(JSON_USUARIOS, ifstream::binary);
    archivo >> this->jsonUsuarios;
    this->contrasenias = jsonUsuarios["usuariosRegistrados"];
	this->nroJugador = nroJugador;
	this->usuarioEnJuego = usuarioEnJuego;
}


// Dada la `conexionServidor` de la clase, se pide por la misma credenciales de logueo.
// Si las credenciales no estan en el archivo `usuarios.json`, se envia el estado
// de login correspondiente, se cierra la conexion y se devuelve false.
// Caso contrario, se le envia el numero de jugador y se devuelve true.
bool ControladorDeSesiones::iniciarSesion() {

	bool ok = true;

	//pedirle un usuario y contraseña al cliente
	struct Login login;
	try {
        pedirCredenciales(&login);
    } catch (...) {
	    l->info("ControladorDeSesiones. Error de protocolo. Rechazando conexion.");
	    return false;
	}

	char *usuario;
	usuario = login.usuario;
	char *contrasenia;
	contrasenia = login.contrasenia;

	//verifico que el usuario esté registrado
    try {
        if (!usuarioEstaRegistrado(usuario, contrasenia)
                || !controlarConUsuariosEnJuego(usuario)) {
            this->conexionServidor->cerrar();
            ok = false;
        } else {
            this->conexionServidor->enviarEstadoLogin({nroJugador, LOGIN_ESPERAR});
            this->usuarioConectado = std::string(usuario);
            conexionServidor->setUsuario(std::string(usuario));
            conexionServidor->setNroJugador(nroJugador);
        }
    } catch (...) {
        l->info("ControladorDeSesiones. Error al enviar resultado de logueo");
        return false;
    }

	return ok;
}

bool ControladorDeSesiones::usuarioEstaRegistrado(char* usuario, char* contrasenia) {
	// Chequeo si el usuario está registrado
	if (this->contrasenias[usuario].empty()) {
		l->info("Usuario " + std::string(usuario) + " no esta registrado");
        this->conexionServidor->enviarEstadoLogin({LOGIN_ERROR_USUARIO_INEXISTENTE});
		return false;
	}
	// Chequeo si la contrasenia es correcta
	if (strcmp(this->contrasenias[usuario].asCString(), contrasenia) != 0) {
		l->info("Password del usuario " + std::string(usuario) + " no coincide");
        this->conexionServidor->enviarEstadoLogin({LOGIN_ERROR_PASS_INVALIDA});
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

bool ControladorDeSesiones::controlarConUsuariosEnJuego(std::string usuario) {
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
            l->info("Usuario " + std::string(usuario) + " ya se encuentra conectado");
            this->conexionServidor->enviarEstadoLogin({LOGIN_ERROR_USUARIO_EN_JUEGO});
            return false; // Si se recibe el ping, ese usuario ya se encuentra en el juego
        } catch (const ConexionExcepcion& e) {
            (*j)->cerrar();
            if (usuarioEnJuego) {
                return true;
            }
            j = conexiones->erase(j);
            j++;
            // Si solo se aceptan usuarios que ya esten en el juego, se lo deja aceptar
            // porque se lo encontro en la lista y desconectado
        }
    }

    // Si `usuarioEnJuego` es false, significa que se pueden aceptar usuarios fuera de la lista original de jugadores
    if (usuarioEnJuego) {
        this->conexionServidor->enviarEstadoLogin({LOGIN_ERROR_EN_PARTIDA});
        return false;
    }

    return !usuarioEnJuego;

}

ConexionServidor *ControladorDeSesiones::getConexionServidor() const {
    return conexionServidor;
}

