//
// Created by javier on 10/4/20.
//

#ifndef CPP_SANDBOX_VECTOR_H
#define CPP_SANDBOX_VECTOR_H


class Vector {
private:
    double x, y;
public:
    Vector(double x, double y);
    Vector();
    friend Vector operator+(const Vector& lhs, const Vector& rhs);

    double getX() const;

    void setX(double x);

    double getY() const;

    void setY(double y);
};




#endif //CPP_SANDBOX_VECTOR_H
