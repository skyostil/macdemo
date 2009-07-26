/**
 * Copyright (C) 2009 Sami Kyostila <sami.kyostila@unrealvoodoo.org>
 */
#ifndef MATRIX_H
#define MATRIX_H

#include "FixedPointMatrix.h"
#include "FixedPointMath.h"
#include <string.h>

#define M_CELL(col,row) (((row)<<2)+(col))

Matrix::Matrix(Matrix *b)
{
	memcpy(&m[0],&b->m[0],sizeof(m));
}

Matrix::Matrix()
{
	makeIdentity();
}

scalar Matrix::cell(int row, int column) const
{
	return m[M_CELL(column,row)];
}

Matrix Matrix::makeIdentity()
{
	m[M_CELL(0,0)]=1<<FP;	m[M_CELL(1,0)]=0;	m[M_CELL(2,0)]=0;	m[M_CELL(3,0)]=0;
	m[M_CELL(0,1)]=0;	m[M_CELL(1,1)]=1<<FP;	m[M_CELL(2,1)]=0;	m[M_CELL(3,1)]=0;
	m[M_CELL(0,2)]=0;	m[M_CELL(1,2)]=0;	m[M_CELL(2,2)]=1<<FP;	m[M_CELL(3,2)]=0;
	m[M_CELL(0,3)]=0;	m[M_CELL(1,3)]=0;	m[M_CELL(2,3)]=0;	m[M_CELL(3,3)]=1<<FP;
	return *this;
}

scalar Matrix::operator[](unsigned i) const
{
	return m[i];
}

Matrix Matrix::operator*=(const Matrix &b)
{
	(*this) = (*this) * b;
	return *this;
}

Vector Matrix::getTranslation() const
{
	return Vector(
		m[M_CELL(3,0)],
		m[M_CELL(3,1)],
		m[M_CELL(3,2)]);
}

Matrix Matrix::transpose3x3()
{
	Matrix n;
	unsigned i,j;

	for(i=0;i<3;i++)
		for(j=0;j<3;j++)
			n.m[M_CELL(j,i)] = m[M_CELL(i,j)];
	return n;
}

Matrix Matrix::operator*(const Matrix &b)
{
	int i,j;
	Matrix n;

	for (i=0;i<4;i++)
	for (j=0;j<4;j++)
	{
		n.m[M_CELL(i,j)] =
			FPMul(m[M_CELL(i,0)],b.m[M_CELL(0,j)]) +
			FPMul(m[M_CELL(i,1)],b.m[M_CELL(1,j)]) +
			FPMul(m[M_CELL(i,2)],b.m[M_CELL(2,j)]) +
			FPMul(m[M_CELL(i,3)],b.m[M_CELL(3,j)]);
	}
	return n;
}

Vector Matrix::mul3x3(const Vector &v)
{
	return Vector(
		FPMul(v.x,m[M_CELL(0,0)]) + FPMul(v.y,m[M_CELL(1,0)]) + FPMul(v.z,m[M_CELL(2,0)]),
		FPMul(v.x,m[M_CELL(0,1)]) + FPMul(v.y,m[M_CELL(1,1)]) + FPMul(v.z,m[M_CELL(2,1)]),
		FPMul(v.x,m[M_CELL(0,2)]) + FPMul(v.y,m[M_CELL(1,2)]) + FPMul(v.z,m[M_CELL(2,2)]));
}

Vector Matrix::operator*(const Vector &v)
{
	return Vector(
		FPMul(v.x,m[M_CELL(0,0)]) + FPMul(v.y,m[M_CELL(1,0)]) + FPMul(v.z,m[M_CELL(2,0)]) + m[M_CELL(3,0)],
		FPMul(v.x,m[M_CELL(0,1)]) + FPMul(v.y,m[M_CELL(1,1)]) + FPMul(v.z,m[M_CELL(2,1)]) + m[M_CELL(3,1)],
		FPMul(v.x,m[M_CELL(0,2)]) + FPMul(v.y,m[M_CELL(1,2)]) + FPMul(v.z,m[M_CELL(2,2)]) + m[M_CELL(3,2)]);
}

Matrix Matrix::operator*(scalar s)
{
	int i,j;
	Matrix n;

	for (i=0;i<4;i++)
	for (j=0;j<4;j++)
		n.m[M_CELL(i,j)] = FPMul(m[M_CELL(i,j)],s);
	return n;
}

void Matrix::setColumn(int column, const Vector &v)
{
	m[M_CELL(column,0)]=v.x;
	m[M_CELL(column,1)]=v.y;
	m[M_CELL(column,2)]=v.z;
}

Vector Matrix::getColumn(int column) const
{
	return Vector(
		m[M_CELL(column,0)],
		m[M_CELL(column,1)],
		m[M_CELL(column,2)]);
}

void Matrix::setRow(int row, const Vector &v)
{
	m[M_CELL(0,row)]=v.x;
	m[M_CELL(1,row)]=v.y;
	m[M_CELL(2,row)]=v.z;
}

Vector Matrix::getRow(int row) const
{
	return Vector(m[(row<<2)+0],m[(row<<2)+1],m[(row<<2)+2]);
}

Matrix Matrix::makeTranslation(const Vector &direction)
{
	Matrix	n;
	n.setColumn(3, direction);
	return n;
}

Matrix Matrix::makeRotation(const Vector &_axis, scalar angle)
{
	scalar	s, c, t;
	Matrix	n;
	Vector	axis(_axis);

	axis.normalize();
	s = FPSin(angle);
	c = FPCos(angle);
	t = FP_ONE - c;

	n.m[M_CELL(0,0)] = FPMul(t,FPMul(axis.x,axis.x)) + c;
	n.m[M_CELL(1,0)] = FPMul(t,FPMul(axis.x,axis.y)) + FPMul(s, axis.z);
	n.m[M_CELL(2,0)] = FPMul(t,FPMul(axis.x,axis.z)) - FPMul(s, axis.y);
	n.m[M_CELL(3,0)] = 0;
	n.m[M_CELL(0,1)] = FPMul(t, FPMul(axis.x, axis.y)) - FPMul(s, axis.z);
	n.m[M_CELL(1,1)] = FPMul(t, FPMul(axis.y, axis.y)) + c;
	n.m[M_CELL(2,1)] = FPMul(t, FPMul(axis.y, axis.z)) + FPMul(s, axis.x);
	n.m[M_CELL(3,1)] = 0;
	n.m[M_CELL(0,2)] = FPMul(t, FPMul(axis.x, axis.z)) + FPMul(s, axis.y);
	n.m[M_CELL(1,2)] = FPMul(t, FPMul(axis.y, axis.z)) - FPMul(s, axis.x);
	n.m[M_CELL(2,2)] = FPMul(t, FPMul(axis.z, axis.z)) + c;
	n.m[M_CELL(3,2)] = 0;
	n.m[M_CELL(0,3)] = 0;
	n.m[M_CELL(1,3)] = 0;
	n.m[M_CELL(2,3)] = 0;
	n.m[M_CELL(3,3)] = FP_ONE;

	return n;
}

Matrix Matrix::makeRotation(const Vector &origin, const Vector &axis, scalar angle)
{
	Vector o = -origin;
	Matrix trans1 = Matrix::makeTranslation(o);
	Matrix trans2 = Matrix::makeTranslation(origin);
	Matrix rot = makeRotation(axis,angle);
	return trans1 * rot * trans2;
}

#if 0
Matrix Matrix::inverse3x3()
{
	Matrix n;
	scalar det;
	det =
			  m[0] * ( m[4]*m[8] - m[7]*m[5] )
			- m[1] * ( m[3]*m[8] - m[6]*m[5] )
			+ m[2] * ( m[3]*m[7] - m[6]*m[4] );

	if ( fabs( det ) < 0.0005 )
	{
		return n;
	}

	n.m[0] =    m[4]*m[8] - m[5]*m[7]   / det;
	n.m[1] = -( m[1]*m[8] - m[7]*m[2] ) / det;
	n.m[2] =    m[1]*m[5] - m[4]*m[2]   / det;

	n.m[3] = -( m[3]*m[8] - m[5]*m[6] ) / det;
	n.m[4] =    m[0]*m[8] - m[6]*m[2]   / det;
	n.m[5] = -( m[0]*m[5] - m[3]*m[2] ) / det;

	n.m[6] =    m[3]*m[7] - m[6]*m[4]   / det;
	n.m[7] = -( m[0]*m[7] - m[6]*m[1] ) / det;
	n.m[8] =    m[0]*m[4] - m[1]*m[3]   / det;

	return n;

/*
	// thanks to Miika Sell [itchi] for this!
	Matrix n;
//		scalar mat[]={m[data[0][0],data[0][1],data[0][2],data[1][0],data[1][1],data[1][2],data[2][0],data[2][1],data[2][2]};
//		scalar mat[]={m[M_CELL(0,0)],m[M_CELL(0,1)],m[M_CELL(0,2)],m[M_CELL(1,0)],m[M_CELL(1,1)],m[M_CELL(1,2)],m[M_CELL(2,0)],m[M_CELL(2,1)],m[M_CELL(2,2)]};
 	scalar mat[]={m[M_CELL(0,0)],m[M_CELL(1,0)],m[M_CELL(2,0)],m[M_CELL(0,1)],m[M_CELL(1,1)],m[M_CELL(2,1)],m[M_CELL(0,2)],m[M_CELL(1,2)],m[M_CELL(2,2)]};
	scalar D=(mat[0]*mat[4]*mat[8] + mat[1]*mat[5]*mat[6] + mat[2]*mat[3]*mat[7]) -
						(mat[0]*mat[5]*mat[7] + mat[1]*mat[3]*mat[8] + mat[2]*mat[4]*mat[6]);
	scalar inv[9];

	inx=mat[4]*mat[8]-mat[5]*mat[7];
	iny=mat[2]*mat[7]-mat[1]*mat[8];
	inz=mat[1]*mat[5]-mat[2]*mat[4];
	inv[3]=mat[5]*mat[6]-mat[3]*mat[8];
	inv[4]=mat[0]*mat[8]-mat[2]*mat[6];
	inv[5]=mat[2]*mat[3]-mat[0]*mat[5];
	inv[6]=mat[3]*mat[7]-mat[4]*mat[6];
	inv[7]=mat[1]*mat[6]-mat[0]*mat[7];
	inv[8]=mat[0]*mat[4]-mat[1]*mat[3];
	if (D==0) return n;

	int i;
	for (i=0;i<9;i++)
		inv[i]/=D;
//		Matrix ret=new Matrix();
	int x,y;
	for (y=0;y<3;y++)
		for (x=0;x<3;x++)
			n.m[M_CELL(x,y)]=inv[y*3+x];
//				ret.data[y][x]=inv[y*3+x];
//				ret.data[y][x]=inv[y*3+x];
	return n;
*/
}

Matrix Matrix::inverse()
{
	Vector trans = getColumn(3);
//	Matrix inv = inverse3x3();
	Matrix inv = transpose3x3();
	Vector c = -(inv*trans);
	inv.setColumn(3, c);

	return inv;
}
#endif

Matrix Matrix::makeScaling(const Vector &scale)
{
	Matrix	n;
	n.m[M_CELL(0,0)] = scale.x;
	n.m[M_CELL(1,1)] = scale.y;
	n.m[M_CELL(2,2)] = scale.z;
	return n;
}

void Matrix::setCell(int i, scalar v)
{
	m[i] = v;
}

Matrix Matrix::makeLookAt(const Vector &zdirection, scalar angle)
{
	Matrix	n;
	Vector	px, py, pz;
	Vector	worldUp = Vector(FPSin(angle),-FPCos(angle),0);
//	Vector	worldUp = Vector(0,FPSin(angle),-FPCos(angle));
//	Vector	worldUp = Vector(0,0,FP_ONE);

	pz = zdirection;
	pz.normalize();
	py = (worldUp - (pz * (pz.dot(worldUp)))).normalize();

	if (!py.nonzero())
	{
#ifdef LOG_H	
		Log::addMessage(Log::Error, "Matrix", "makeLookAt() produced a degenerate matrix.");
#endif		
		py.set(1,0,0);
	}

	px = py.cross(pz);

	n.setColumn(0,px);
	n.setColumn(1,py);
	n.setColumn(2,pz);

	return n;
}

#undef M_CELL

#endif
