/**
 * Copyright (C) 2001-2009 Sami Kyostila <sami.kyostila@unrealvoodoo.org>
 */
#include "FixedPointVector.h"
#include "FixedPointMath.h"

Vector::Vector()
{}

Vector::Vector(const scalar _x, const scalar _y, const scalar _z)
{
    x=_x;
    y=_y;
    z=_z;
}

Vector::Vector(const class Vector &b)
{
    x=b.x;
    y=b.y;
    z=b.z;
}

Vector Vector::operator=(const class Vector &b)
{
    x=b.x;
    y=b.y;
    z=b.z;
    return *this;
}

bool Vector::operator==(const class Vector &b)
{
    return (x==b.x && y==b.y && z==b.z);
}

Vector Vector::operator+(const class Vector &b) const
{
    return Vector(x+b.x,y+b.y,z+b.z);
}

scalar Vector::operator[](int i) const
{
    switch(i)
    {
    case 0:
        return x;
    case 1:
        return y;
    case 2:
        return z;
    }
    return 0;
}

Vector Vector::operator+=(const class Vector &b)
{
    x+=b.x; y+=b.y; z+=b.z;
    return *this;
}

Vector Vector::operator-=(const class Vector &b)
{
    x-=b.x; y-=b.y; z-=b.z;
    return *this;
}

Vector Vector::operator*=(const scalar s)
{
    x=FPMul(x,s); y=FPMul(y,s); z=FPMul(z,s);
    return *this;
}

Vector Vector::operator/=(const scalar s)
{
    x=FPDiv(x,s);
    y=FPDiv(y,s);
    z=FPDiv(z,s);
    return *this;
}

Vector Vector::operator-(const class Vector &b) const
{
    return Vector(x-b.x,y-b.y,z-b.z);
}

Vector Vector::operator-() const
{
    return Vector(-x,-y,-z);
}

Vector Vector::operator*(class Vector &b) const
{
    return Vector(
               FPMul(x,b.x),
               FPMul(y,b.y),
               FPMul(z,b.z));
}

Vector Vector::operator/(const scalar f) const
{
    return Vector(FPDiv(x,f), FPDiv(y,f), FPDiv(z,f));
}

Vector Vector::operator*(const scalar f) const
{
    return Vector(FPMul(x,f), FPMul(y,f), FPMul(z,f));
}

scalar Vector::dot(const Vector &b) const
{
    return (scalar)(
               FPMul(x,b.x)+
               FPMul(y,b.y)+
               FPMul(z,b.z));
}

Vector Vector::cross(const class Vector &b) const
{
    return Vector(
               FPMul(y,b.z) - FPMul(b.y,z),
               FPMul(z,b.x) - FPMul(b.z,x),
               FPMul(x,b.y) - FPMul(b.x,y));
}

scalar Vector::length() const
{
    return (scalar)FPSqrt(FPMul(x,x) + FPMul(y,y) + FPMul(z,z));
}

scalar Vector::lengthSquared() const
{
    return (FPMul(x,x) + FPMul(y,y) + FPMul(z,z));
}

Vector Vector::normalize()
{
    scalar l=length();

    if (l!=0)
        set(FPDiv(x,l),FPDiv(y,l),FPDiv(z,l));
#ifdef LOG_H
    else
        Log::addMessage(Log::Error, "Vector", "Tried to normalize a degenerate vector.");
#endif

    return *this;
}

void Vector::set(const scalar _x, const scalar _y, const scalar _z)
{
    x=_x;y=_y;z=_z;
}

bool Vector::nonzero() const
{
    return (x||y||z);
}

bool Vector::positive() const
{
    return (x>=0&&y>=0&&z>=0);
}

scalar Vector::manhattanNorm() const
{
    return FPAbs(x) + FPAbs(y) + FPAbs(z);
}


