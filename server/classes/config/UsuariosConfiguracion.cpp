//
// Created by javier on 27/6/20.
//

#include "UsuariosConfiguracion.h"

void UsuariosConfiguracion::nuevoUsuario(std::string usuario, std::string password) {
    usuarios.insert({usuario, password});
}

bool UsuariosConfiguracion::usuarioExiste(std::string usuario) {
    return usuarios.count(usuario) == 1;
}

bool UsuariosConfiguracion::credencialesValidas(std::string usuario, std::string password) {
    return usuarios[usuario] == password;
}

