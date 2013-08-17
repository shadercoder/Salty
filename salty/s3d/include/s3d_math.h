﻿//--------------------------------------------------------------------
// File : s3d_math.h
// Desc : Math Module.
// Copyright(c) Project Asura. All right reserved.
//--------------------------------------------------------------------

#ifndef __S3D_MATH_H__
#define __S3D_MATH_H__

//--------------------------------------------------------------------
// Includes
//--------------------------------------------------------------------
#include <s3d_typedef.h>
#include <cmath>


namespace s3d {

//--------------------------------------------------------------------
// Constant Values
//--------------------------------------------------------------------
const f64     D_PI        = 3.1415926535897932384626433832795;     //!< πです.
const f64     D_2PI       = 6.283185307179586476925286766559;      //!< 2πです.
const f64     D_1DIVPI    = 0.31830988618379067153776752674503;    //!< 1/πです.
const f64     D_PIDIV2    = 1.5707963267948966192313216916398;     //!< π/2です.
const f64     D_PIDIV3    = 1.0471975511965977461542144610932;     //!< π/3です.
const f64     D_PIDIV4    = 0.78539816339744830961566084581988;    //!< π/4です.
const f64     D_EPSILON   = 2.2204460492503131e-016;

f64     Max     ( const f64, const f64 );
f64     Min     ( const f64, const f64 );
f64     ToRadian( const f64 );
f64     ToDegree( const f64 );
bool    IsZero  ( const f64 );
bool    IsNan   ( const f64 );
f64     Fresnel ( const f64, const f64, const f64 );

}// namespace s3d


//-------------------------------------------------------------------
// Inlines
//-------------------------------------------------------------------
#include <s3d_math.inl>

//-------------------------------------------------------------------
// Include Module
//-------------------------------------------------------------------
#include <s3d_vector3.h>
#include <s3d_matrix.h>
#include <s3d_onb.h>
#include <s3d_rand.h>


#endif//__S3D_MATH_H__