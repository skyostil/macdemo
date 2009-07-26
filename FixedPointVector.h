/**
 * Copyright (C) 2001-2009 Sami Kyostila <sami.kyostila@unrealvoodoo.org>
 */
#ifndef FIXEDPOINTVECTOR_H
#define FIXEDPOINTVECTOR_H

#ifdef MSVC
#pragma warning (disable: 4786)
#endif

#include "Config.h"
#include "FixedPointMath.h"

class Vector	// 3
{
friend class Matrix;
public:
	Vector();
	Vector(const scalar _x, const scalar _y, const scalar _z);
	Vector(const class Vector &b);
	Vector operator=(const class Vector &b);
	
	bool   operator==(const class Vector &b);
	Vector operator+(const class Vector &b) const;
	scalar operator[](int i) const;
	Vector operator+=(const class Vector &b);
	Vector operator-=(const class Vector &b);
	Vector operator*=(const scalar s);
	Vector operator/=(const scalar s);
	Vector operator-(const class Vector &b) const;
	Vector operator-() const;
	Vector operator*(class Vector &b) const;
	Vector operator/(const scalar f) const;
	Vector operator*(const scalar f) const;
	
	scalar dot(const Vector &b) const;
	Vector cross(const class Vector &b) const;
	scalar length() const;
	scalar lengthSquared() const;
	scalar manhattanNorm() const;
	Vector normalize();
	void   set(const scalar _x, const scalar _y, const scalar _z);
	bool   nonzero() const;
	bool   positive() const;
	
	scalar	x,y,z;
};

#endif

