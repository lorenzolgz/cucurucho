//
// Created by javier on 27/6/20.
//

#ifndef CUCURUCHO_USUARIOSCONFIGURACION_H
#define CUCURUCHO_USUARIOSCONFIGURACION_H


#include <string>
#include <map>

class UsuariosConfiguracion {
public:
    void nuevoUsuario(std::string usuario, std::string password);
    bool usuarioExiste(std::string usuario);
    bool credencialesValidas(std::string usuario, std::string password);

private:
    std::map<std::string, std::string> usuarios;
};


#endif //CUCURUCHO_USUARIOSCONFIGURACION_H
