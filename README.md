# Cucurucho ++
## Repositorio creado para la realizacion del TP Grupal de la materia Taller de Programación

75.42 / 95.08 - Taller de Programación I - Azcurra

### Integrantes:

<p> Di Santo, Javier
<p> Dvorkin, Camila
<p> Garcia, Ailen
<p> Gimenez, Lorenzo
<p> Souto, Rodrigo

### Dependencias:

Instalar las siguientes dependencias:

```sh
sudo apt install cmake libsdl2-dev libsdl2-image-dev libjsoncpp-dev g++ nlohmann-json-dev
sudo python3 -m pip install cpplint
```


### Parámetros opcionales
Parámetros opcionales:
- `-l`: Nivel de log (`debug`, `info` o `error`)
- `-c`: Ruta del archivo de configuración. En el caso de no encontrarlo, se levantará un archivo de configuración por defecto.

### Compilar proyecto
```sh
# Desde el root del proyecto:
mkdir cmake-build-debug
cd cmake-build-debug
cmake ..
make
```

### Correr cliente
```sh
# Desde el root del proyecto:
cd cmake-build-debug 
./cliente
```

### Correr servidor
```sh
# Desde el root del proyecto:
cd cmake-build-debug
./servidor
```

![Gley Lancer](assets/screenshot.png)
