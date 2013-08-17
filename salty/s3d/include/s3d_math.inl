﻿//---------------------------------------------------------------------
// File : s3d_math.inl
// Desc : Math Module.
// Copyright(c) Project Asura. All right reserved.
//---------------------------------------------------------------------

#ifndef __S3D_MATH_INL_
#define __S3D_MATH_INL__

namespace s3d {

//---------------------------------------------------------------------
//      最小値を求めます.
//---------------------------------------------------------------------
S3D_INLINE
f64 Min( const f64 a, const f64 b )
{ return ( a < b ) ? a : b; }

//---------------------------------------------------------------------
//      最大値を求めます.
//---------------------------------------------------------------------
S3D_INLINE
f64 Max( const f64 a, const f64 b )
{ return ( a > b ) ? a : b; }

//---------------------------------------------------------------------
//      ラジアンに変換します.
//---------------------------------------------------------------------
S3D_INLINE
f64 ToRadian( const f64 deg )
{ return deg * ( D_PI / 180.0 ); }

//---------------------------------------------------------------------
//      度に変換します.
//---------------------------------------------------------------------
S3D_INLINE
f64 ToDegree( const f64 rad )
{ return rad * ( 180.0 / D_PI ); }

//---------------------------------------------------------------------
//      ゼロとみなせるかチェックします.
//---------------------------------------------------------------------
S3D_INLINE
bool IsZero( const f64 value )
{ return ( -D_EPSILON <= value && value <= D_EPSILON ); }

//---------------------------------------------------------------------
//      非数であるかチェックします.
//---------------------------------------------------------------------
S3D_INLINE
bool IsNan( const f64 value )
{ return ( value != value ); }

//---------------------------------------------------------------------
//      フレネル項を求めます.
//---------------------------------------------------------------------
S3D_INLINE
f64 Fresnel( const f64 n1, const f64 n2, const f64 cosTheta )
{
    register f64 a = n1 + n2;
    register f64 b = n1 - n2;
    register f64 R = ( a * a ) / ( b * b );
    return R + ( 1.0 - R ) * pow( 1.0 - cosTheta, 5.0 );
}

} // namespace s3d


#endif//__S3D_MATH_INL__