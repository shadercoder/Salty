﻿//------------------------------------------------------------------------------
// File : s3d_color3.inl
// Desc : RGB Color Module.
// Copyright(c) Project Asura. All right reserved.
//------------------------------------------------------------------------------

#ifndef __S3D_COLOR3_INL__
#define __S3D_COLOR3_INL__

namespace s3d {

S3D_INLINE
Color3::Color3()
{ /* DO_NOTHING */ }

S3D_INLINE
Color3::Color3( const f64 nr, const f64 ng, const f64 nb )
: r( nr )
, g( nb )
, b( nb )
{ /* DO_NOTHING */ }

S3D_INLINE
Color3::Color3( const Color3& value )
: r( value.r )
, g( value.g )
, b( value.b )
{ /* DO_NOTHING */ }

S3D_INLINE
Color3& Color3::operator = ( const Color3& value )
{
    r = value.r;
    g = value.g;
    b = value.b;
    return (*this);
}

S3D_INLINE
Color3& Color3::operator += ( const Color3& value )
{
    r += value.r;
    g += value.g;
    b += value.b;
    return (*this);
}

S3D_INLINE
Color3& Color3::operator -= ( const Color3& value )
{
    r -= value.r;
    g -= value.g;
    b -= value.b;
    return (*this);
}

S3D_INLINE
Color3& Color3::operator *= ( const Color3& value )
{
    r *= value.r;
    g *= value.g;
    b *= value.b;
    return (*this);
}

S3D_INLINE
Color3& Color3::operator /= ( const Color3& value )
{
    r /= value.r;
    g /= value.g;
    b /= value.b;
    return (*this);
}

S3D_INLINE
Color3& Color3::operator *= ( const f64 value )
{
    r *= value;
    g *= value;
    b *= value;
    return (*this);
}

S3D_INLINE
Color3& Color3::operator /= ( const f64 value )
{
    r /= value;
    g /= value;
    b /= value;
    return (*this);
}

S3D_INLINE
Color3 Color3::operator + () const
{ return (*this); }

S3D_INLINE
Color3 Color3::operator - () const
{ return Color3( -r, -g, -b ); }

S3D_INLINE
Color3 Color3::operator + ( const Color3& value ) const
{ return Color3( r + value.r, g + value.g, b + value.b ); }

S3D_INLINE
Color3 Color3::operator - ( const Color3& value ) const
{ return Color3( r - value.r, g - value.g, b - value.b ); }

S3D_INLINE
Color3 Color3::operator * ( const Color3& value ) const
{ return Color3( r * value.r, g * value.g, b * value.b ); }

S3D_INLINE
Color3 Color3::operator / ( const Color3& value ) const
{ return Color3( r / value.r, g / value.g, b / value.b ); }

S3D_INLINE
Color3 Color3::operator * ( const f64 value ) const
{ return Color3( r * value, g * value, b * value ); }

S3D_INLINE
Color3 Color3::operator / ( const f64 value ) const
{ return Color3( r / value, g / value, b / value ); }

S3D_INLINE
void Color3::Clamp()
{
    if ( r > 1.0f )    { r = 1.0f; }
    if ( g > 1.0f )    { g = 1.0f; }
    if ( b > 1.0f )    { b = 1.0f; }
    
    if ( r < 0.0f )    { r = 0.0f; }
    if ( g < 0.0f )    { g = 0.0f; }
    if ( b < 0.0f )    { b = 0.0f; }
}

} // namespace s3d


#endif//__S3D_COLOR3_INL__