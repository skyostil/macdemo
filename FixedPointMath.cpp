// Fixed point routines based on "16:16 fixed point math routines" by Henry Minsky (hqm@alum.mit.edu)

#include "FixedPointMath.h"

const scalar SK1 = 498;
const scalar SK2 = 10882;

// Computes SIN(f), f is a fixed point number in radians.
// 0 <= f <= 2PI

scalar FPSin(scalar f)
{
        // If in range -pi/4 to pi/4: nothing needs to be done.
        // otherwise, we need to get f into that range and account for
        // sign change.

        int sign = 1;
        if ((f > PI_OVER_2) && (f <= PI)) 
        {
                f = PI - f;
        } else if ((f > PI) && (f <= (PI + PI_OVER_2)))
        {
                f = f - PI;
                sign = -1;
        } else if (f > (PI + PI_OVER_2))
        {
                f = (PI<<1)-f;
                sign = -1;
        }

        int sqr = FPMul(f,f);
        int result = SK1;
        result = FPMul(result, sqr);
        result -= SK2;
        result = FPMul(result, sqr);
        result += (1<<16);
        result = FPMul(result, f);
        return sign * result;
}

const scalar CK1 = 2328;
const scalar CK2 = 32551;

// Computes COS(f), f is a fixed point number in radians.
//  0 <= f <= PI/2
scalar FPCos(scalar f)
{
        int sign = 1;
        if ((f > PI_OVER_2) && (f <= PI))
        {
                f = PI - f;
                sign = -1;
        }
        else if ((f > PI_OVER_2) && (f <= (PI + PI_OVER_2)))
        {
                f = f - PI;
                sign = -1;
        }
        else if (f > (PI + PI_OVER_2))
        {
                f = (PI<<1)-f;
        }

        int sqr = FPMul(f,f);
        int result = CK1;
        result = FPMul(result, sqr);
        result -= CK2;
        result = FPMul(result, sqr);
        result += (1<<16);
        return result * sign;
}

const scalar TK1 = 13323;
const scalar TK2 = 20810;

// Computes Tan(f), f is a fixed point number in radians.
// 0 <= f <= PI/4
scalar FPTan(scalar f)
{
        int sqr = FPMul(f,f);
        int result = TK1;
        result = FPMul(result, sqr);
        result += TK2;
        result = FPMul(result, sqr);
        result += (1<<16);
        result = FPMul(result, f);
        return result;
}

// Computes ArcTan(f), f is a fixed point number
// |f| <= 1
//
// For the inverse tangent calls, all approximations are valid for |t| <= 1.
// To compute ATAN(t) for t > 1, use ATAN(t) = PI/2 - ATAN(1/t).  For t < -1,
// use ATAN(t) = -PI/2 - ATAN(1/t).
scalar FPArcTan(scalar f)
{
        int sqr = FPMul(f,f);
        int result = 1365;
        result = FPMul(result, sqr);
        result -= 5579;
        result = FPMul(result, sqr);
        result += 11805;
        result = FPMul(result, sqr);
        result -= 21646;
        result = FPMul(result, sqr);
        result += 65527;
        result = FPMul(result,f);
        return result;
}



const scalar AS1 = -1228;
const scalar AS2 = 4866;
const scalar AS3 = 13901;
const scalar AS4 = 102939;

// Compute ArcSin(f), 0 <= f <= 1
scalar FPArcSin(scalar f)
{
        int fRoot = FPSqrt((1<<16)-f);
        int result = AS1;
        result = FPMul(result, f);
        result += AS2;
        result = FPMul(result, f);
        result -= AS3;
        result = FPMul(result, f);
        result += AS4;
        result = PI_OVER_2 - (FPMul(fRoot,result));
        return result;
}

// Compute ArcCos(f), 0 <= f <= 1
scalar FPArcCos(scalar f)
{
        int fRoot = FPSqrt((1<<16)-f);
        int result = AS1;
        result = FPMul(result, f);
        result += AS2;
        result = FPMul(result, f);
        result -= AS3;
        result = FPMul(result, f);
        result += AS4;
        result = FPMul(fRoot,result);
        return result;
}

scalar FPArcTan2(scalar a, scalar b)
{
        if (a == 0)
        {
                if (b == 0)
                        return 0;
                else
                        return FPSgn(b)*(PI/2);
        }

        if (a > 0)
                return FPArcTan(FPDiv(b,a));
        else
                return FPSgn(b) * (PI - FPArcTan(FPAbs(FPDiv(b,a))));
}

