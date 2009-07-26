/**
 * Copyright (C) 2009 Sami Kyostila <sami.kyostila@unrealvoodoo.org>
 */
#ifndef FIXEDPOINTMATH_H
#define FIXEDPOINTMATH_H

#define FP      16      // don't touch this, m'kay

#define FP_ONE          (1<<FP)
#define FP_INTMASK      (~((1<<FP)-1))
#define FP_FRACMASK     ((1<<FP)-1)
#define FP_MIN_DIVISOR  (1<<6)

typedef signed int scalar;

#ifdef _MSC_VER
#if (_MSC_VER < 1300)
// sorry, no 64 bit ints on msvc 6
typedef signed long scalar64;
#else
typedef signed __int64 scalar64;
#endif
#else
// typedef signed long long scalar64;
#endif

const scalar PI = 205887;
const scalar PI_OVER_2 = (PI/2);
const scalar E = 178145;
const scalar HALF = 2<<15;

inline scalar FPInt(int i);
inline scalar FPMul(scalar a, scalar b);
inline scalar FPDiv(scalar a, scalar b);
inline scalar FPSqrt(scalar a);
scalar FPSin(scalar f);
scalar FPCos(scalar f);
scalar FPTan(scalar f);
scalar FPArcTan(scalar f);
scalar FPArcSin(scalar f);
scalar FPArcCos(scalar f);
scalar FPArcTan2(scalar a, scalar b);

inline scalar FPInt(int i)
{
        return i << FP;
}

inline scalar FPMul(scalar a, scalar b)
{
        return ((a>>6) * (b>>6))>>4;
//      return ((a>>7) * (b>>5))>>4;
//      return (a * b)>>FP;
}

inline scalar FPDiv(scalar a, scalar b)
{
#if 0 // make sure we crash on zero division
        if (b < (1<<6) && b > -(1>>6))
        {
                *((char*)(0)) = 0xdeadbeef;
                return 0x80000000;
        }
#endif  
        return ((a<<6) / (b>>6))<<4;
//      return ((a<<7) / (b>>5))<<4;
//      return (a / b)<<FP;
}

inline scalar FPHighPrecDiv(scalar a, scalar b)
{
		// hack: this seems to do the trick
		return ((a<<8) / (b>>4))<<4;

#if 0
        // don't crash on zero division
        if (b < (1<<6) && b > -(1<<6))
        {
                return 0x80000000;
        }
#endif

// sorry, no 64 bit division on msvc 6 
//#if (defined(_MSC_VER) && _MSC_VER < 1300)
#if 1
        return FPDiv(a,b);
#else
        return (scalar)((((scalar64)(a))<<FP) / (b));
#endif
}

inline scalar FPSqrt(scalar a)
{
        int r = (a + (1<<FP))>>1;
        int i;

        for (i=0; i<8; i++)
        {
                r = (r + FPDiv(a, r)) >> 1;
        }
        return r;
}

// signed modulo
inline scalar FPMod(scalar a, scalar m)
{
        scalar s = a % m;
        
        if (a<0)
                s+=m;
        
        return s;
}

inline scalar FPAbs(scalar a)
{
	return (a<0)?-a:a;
}

inline scalar FPSgn(scalar a)
{
	return (a>0)?1:-1;
}

#endif
