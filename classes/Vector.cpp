//
// Created by javier on 10/4/20.
//

#include "Vector.h"

Vector::Vector(double x, double y) {
    Vector::x = x;
    Vector::y = y;
}

Vector::Vector() {
    x = 0;
    y = 0;
}

Vector operator+(const Vector &lhs, const Vector &rhs) {
    return {lhs.x + rhs.x, lhs.y + rhs.y};
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
