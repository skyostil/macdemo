/**
 * Copyright (C) 2009 Sami Kyostila <sami.kyostila@unrealvoodoo.org>
 */
#ifndef FIXEDPOINTMATRIX_H
#define FIXEDPOINTMATRIX_H
 
#include "FixedPointVector.h"

class Matrix	// 4x4
{
public:
	Matrix(Matrix *b);
	Matrix();

	scalar	cell(int row, int column) const;
	void	setCell(int i, scalar v);
	Vector	getTranslation() const;

	Matrix	operator*(const Matrix &b);
	Vector	operator*(const Vector &v);
	Matrix	operator*(scalar s);
	scalar	operator[](unsigned i) const;
	Matrix	operator*=(const Matrix &b);

	void	setColumn(int column, const Vector &v);
	Vector	getColumn(int column) const;
	void	setRow(int row, const Vector &v);
	Vector	getRow(int row) const;

	Matrix	inverse3x3();
	Matrix	inverse();
	Matrix	transpose3x3();
	Vector	mul3x3(const Vector &v);

	Matrix makeIdentity();
	static Matrix makeTranslation(const Vector &direction);
	static Matrix makeRotation(const Vector &axis, scalar angle);
	static Matrix makeRotation(const Vector &origin, const Vector &axis, scalar angle);
	static Matrix makeScaling(const Vector &scale);
	static Matrix makeLookAt(const Vector &zdirection, scalar angle);
protected:
	scalar	m[4*4];
};

#endif
