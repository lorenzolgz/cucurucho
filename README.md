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
sudo apt install cmake libsdl2-dev libsdl2-image-dev libjsoncpp-dev g++ nlohmann-json-dev libsdl2-mixer-dev
sudo python3 -m pip install cpplint
```


### Parámetros opcionales
- Ver parámetro `--help` del cliente y del servidor

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


### Correr el servidor en docker
```sh
# Desde el root del proyecto:
docker build -t ubuntu-cucurucho .
docker container run ubuntu-cucurucho
```

![Gley Lancer](client/assets/screenshot.png)
