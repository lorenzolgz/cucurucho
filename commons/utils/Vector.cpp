//
// Created by javier on 10/4/20.
//

#include <tgmath.h>
#include "Vector.h"
#include "Utils.h"

Vector::Vector(double x, double y) {
    Vector::x = x;
    Vector::y = y;
}

Vector::Vector() {
    x = 0;
    y = 0;
}

float Vector::modulo(){
    return sqrt(x*x + y*y);
}

Vector operator+(const Vector &lhs, const Vector &rhs) {
    return {lhs.x + rhs.x, lhs.y + rhs.y};
}

Vector operator-(const Vector &lhs, const Vector &rhs) {
    return {lhs.x - rhs.x, lhs.y - rhs.y};
}

Vector operator*(const Vector &lhs, const double &rhs) {
    return {lhs.x * rhs, lhs.y * rhs};
}

Vector operator/(const Vector &lhs, const double &rhs) {
    return {lhs.x / rhs, lhs.y / rhs};
}


double Vector::getX() const {
    return x;
}

void Vector::setX(double x) {
    Vector::x = x;
}

double Vector::getY() const {
    return y;
}

void Vector::setY(double y) {
    Vector::y = y;
}

double Vector::arg() const {
    // atan2 da un angulo en [-pi, pi]
    // creanme que esto lo pasa a [0°, 360°]

    double d = to_d(atan2(y, x));
    d = -d + 360 * (d > 0);
    return d;
}

bool Vector::esNulo() const {
    return x == 0 && y == 0;
}


std::string Vector::getVector() {
    return "("+ std::to_string(x)+" , "+std::to_string(y) + ").";
}

// Devuelve un nuevo vector con modulo `d`, conservando el angulo del vector actual
// Considerando el sistema de coordenadas del juego
Vector Vector::escalar(double d) {
	Vector v = Vector(- d * cos_d(arg()), d * sin_d(arg()));
	return v;
}


Vector Vector::polares(double mod, double a) {
	Vector v = Vector(mod * cos_d(a), - mod * sin_d(a));
	return v;
}