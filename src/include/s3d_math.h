﻿//------------------------------------------------------------------------------------------
// File : s3d_math.h.
// Desc : Math Module.
// Copyright(c) Project Asura. All right reserved.
//------------------------------------------------------------------------------------------

#ifndef __S3D_MATH__
#define __S3D_MATH__

//------------------------------------------------------------------------------------------
// Includes
//------------------------------------------------------------------------------------------
#include <s3d_typedef.h>
#include <s3d_rand.h>
#include <cmath>
#include <cassert>


namespace s3d {

//------------------------------------------------------------------------------------------
// Forward Declarations.
//------------------------------------------------------------------------------------------
struct  Vector3;
struct  Ray;


//------------------------------------------------------------------------------------------
// Type Definitions.
//------------------------------------------------------------------------------------------
typedef Vector3 Color;


//------------------------------------------------------------------------------------------
// Constant Values
//------------------------------------------------------------------------------------------
const f64   D_INF       = 1e12;                                  //!< Inifity.
const f64   D_EPS       = 1e-6;                                  //!< セルフヒット防止閾値.
const f64   D_PI        = 3.1415926535897932384626433832795;     //!< πです.
const f64   D_2PI       = 6.283185307179586476925286766559;      //!< 2πです.
const f64   D_1DIVPI    = 0.31830988618379067153776752674503;    //!< 1/πです.
const f64   D_1DIV2PI   = 0.15915494309189533576888376337251;    //!< 1/2πです.
const f64   D_PIDIV2    = 1.5707963267948966192313216916398;     //!< π/2です.
const f64   D_PIDIV3    = 1.0471975511965977461542144610932;     //!< π/3です.
const f64   D_PIDIV4    = 0.78539816339744830961566084581988;    //!< π/4です.
const f64   D_MAX       = 1.7976931348623158e+308;               //!< f64型の最大値です.
const f64   D_MIN       = 2.2250738585072014e-308;               //!< f64型の最小値です.


//------------------------------------------------------------------------------------------
//! @brief      最大値を求めます.
//------------------------------------------------------------------------------------------
S3D_INLINE
f64 Max( const f64 a, const f64 b )
{ return ( a > b ) ? a : b; }

//------------------------------------------------------------------------------------------
//! @brief      最小値を求めます.
//------------------------------------------------------------------------------------------
S3D_INLINE
f64 Min( const f64 a, const f64 b )
{ return ( a < b ) ? a : b; }

//------------------------------------------------------------------------------------------
//! @brief      ラジアンに変換します.
//------------------------------------------------------------------------------------------
S3D_INLINE
f64 ToRad( const f64 deg )
{ return deg * ( D_PI / 180.0 ); }

//------------------------------------------------------------------------------------------
//! @brief      度に変換します.
//------------------------------------------------------------------------------------------
S3D_INLINE
f64 ToDeg( const f64 rad )
{ return rad * ( 180.0 / D_PI ); }

//------------------------------------------------------------------------------------------
//! @brief      非数であるかチェックします.
//------------------------------------------------------------------------------------------
S3D_INLINE
bool IsNan( const f64 value )
{ return ( value != value ); }


/////////////////////////////////////////////////////////////////////////////////////////////
// Vector2 structure
/////////////////////////////////////////////////////////////////////////////////////////////
struct Vector2
{
public:
    union
    {
        struct
        {
            f64 x;      //!< X成分です.
            f64 y;      //!< Y成分です.
        };
        f64 v[2];       //!< 各成分を表す配列です;
    };

    //--------------------------------------------------------------------------------------
    //! @brief      コンストラクタです.
    //--------------------------------------------------------------------------------------
    Vector2()
    { /* DO_NOTHING */ }

    //--------------------------------------------------------------------------------------
    //! @brief      引数付きコンストラクタです.
    //--------------------------------------------------------------------------------------
    Vector2( const f64 nx, const f64 ny )
    : x( nx )
    , y( ny )
    { /* DO_NOTHING */ }

    //--------------------------------------------------------------------------------------
    //! @brief      コピーコンストラクタです.
    //--------------------------------------------------------------------------------------
    Vector2( const Vector2& value )
    : x( value.x )
    , y( value.y )
    { /* DO_NOTHING */ }

    //--------------------------------------------------------------------------------------
    //! @brief      等価演算子です.
    //--------------------------------------------------------------------------------------
    S3D_INLINE
    bool operator == ( const Vector2& value ) const
    {
        return ( x == value.x )
            && ( y == value.y );
    }

    //--------------------------------------------------------------------------------------
    //! @brief      非等価演算子です.
    //--------------------------------------------------------------------------------------
    S3D_INLINE
    bool operator != ( const Vector2& value ) const
    {
        return ( x != value.x )
            || ( y != value.y );
    }

    //--------------------------------------------------------------------------------------
    //! @brief      代入演算子です.
    //--------------------------------------------------------------------------------------
    S3D_INLINE
    Vector2& operator = ( const Vector2& value )
    {
        x = value.x;
        y = value.y;
        return (*this);
    }

    //--------------------------------------------------------------------------------------
    //! @brief      加算代入演算子です.
    //--------------------------------------------------------------------------------------
    S3D_INLINE
    Vector2& operator += ( const Vector2& b )
    {
        x += b.x;
        y += b.y;
        return (*this);
    }

    //--------------------------------------------------------------------------------------
    //! @brief      減算代入演算子です.
    //--------------------------------------------------------------------------------------
    S3D_INLINE
    Vector2& operator -= ( const Vector2& b )
    {
        x -= b.x;
        y -= b.y;
        return (*this);
    }

    //--------------------------------------------------------------------------------------
    //! @brief      乗算代入演算子です.
    //--------------------------------------------------------------------------------------
    S3D_INLINE
    Vector2& operator *= ( const f64 b )
    {
        x *= b;
        y *= b;
        return (*this);
    }

    //--------------------------------------------------------------------------------------
    //! @brief      除算代入演算子です.
    //--------------------------------------------------------------------------------------
    S3D_INLINE
    Vector2& operator /= ( const f64 b )
    {
        assert( b != 0.0 );
        x /= b;
        y /= b;
        return (*this);
    }

    //--------------------------------------------------------------------------------------
    //! @brief      正符号演算子です.
    //--------------------------------------------------------------------------------------
    S3D_INLINE
    Vector2  operator + () const
    { return Vector2( x, y ); }

    //--------------------------------------------------------------------------------------
    //! @brief      負符号演算子です.
    //--------------------------------------------------------------------------------------
    S3D_INLINE
    Vector2 operator - () const
    { return Vector2( -x, -y ); }

    //--------------------------------------------------------------------------------------
    //! @brief      加算演算子です.
    //--------------------------------------------------------------------------------------
    S3D_INLINE
    Vector2 operator + (const Vector2 &b) const
    {
        return Vector2(
            x + b.x,
            y + b.y );
    }

    //--------------------------------------------------------------------------------------
    //! @brief      減算演算子です.
    //--------------------------------------------------------------------------------------
    S3D_INLINE
    Vector2 operator - (const Vector2 &b) const
    { 
        return Vector2(
            x - b.x,
            y - b.y );
    }

    //--------------------------------------------------------------------------------------
    //! @brief      乗算演算子です.
    //--------------------------------------------------------------------------------------
    S3D_INLINE
    Vector2 operator * (const f64 b) const
    { 
        return Vector2(
            x * b,
            y * b );
    }

    //--------------------------------------------------------------------------------------
    //! @brief      除算演算子です.
    //--------------------------------------------------------------------------------------
    S3D_INLINE
    Vector2 operator / (const f64 b) const
    {
        assert( b != 0.0 );
        return Vector2(
            x / b,
            y / b );
    }

    //--------------------------------------------------------------------------------------
    //! @brief      長さの2乗値を求めます.
    //--------------------------------------------------------------------------------------
    S3D_INLINE
    f64 LengthSq() const
    { return ( x * x ) + ( y * y ); }

    //--------------------------------------------------------------------------------------
    //! @brief      長さを求めます.
    //--------------------------------------------------------------------------------------
    S3D_INLINE 
    f64 Length() const
    { return sqrt( ( x * x ) + ( y * y ) ); }

    //--------------------------------------------------------------------------------------
    //! @brief      正規化します.
    //--------------------------------------------------------------------------------------
    S3D_INLINE
    void Normalize()
    {
        register f64 mag = sqrt( x * x + y * y );
        assert( mag != 0.0 );
        x /= mag;
        y /= mag;
    }

    //--------------------------------------------------------------------------------------
    //! @brief      単位ベクトルを求めます.
    //--------------------------------------------------------------------------------------
    static S3D_INLINE
    Vector2 UnitVector (const Vector2 &v)
    {
        register f64 mag = sqrt( v.x * v.x + v.y * v.y );
        assert( mag != 0.0 );
        return Vector2(
            v.x / mag,
            v.y / mag );
    }

    //--------------------------------------------------------------------------------------
    //! @brief      各成分ごとに乗算します.
    //--------------------------------------------------------------------------------------
    static S3D_INLINE
    Vector2 Mul (const Vector2 &v1, const Vector2 &v2)
    { 
        return Vector2(
            v1.x * v2.x,
            v1.y * v2.y );
    }

    //--------------------------------------------------------------------------------------
    //! @brief      内積を求めます.
    //--------------------------------------------------------------------------------------
    static S3D_INLINE
    f64 Dot (const Vector2 &v1, const Vector2 &v2) 
    { return ( v1.x * v2.x ) + ( v1.y * v2.y ); }

    //--------------------------------------------------------------------------------------
    //! @brief      反射ベクトルを求めます.
    //--------------------------------------------------------------------------------------
    static S3D_INLINE
    Vector2 Reflect( const Vector2& i, const Vector2& n )
    {
        register f64 dot = ( n.x * i.x ) + ( n.y * i.y );
        register f64 _2dot = 2.0 * dot;

        return Vector2(
            i.x - ( _2dot * n.x ),
            i.y - ( _2dot * n.y ) );
    }

    //---------------------------------------------------------------------------------------
    //! @brief      各成分の最小値を求めます.
    //---------------------------------------------------------------------------------------
    static S3D_INLINE
    Vector2 Min( const Vector2& a, const Vector2& b )
    {
        return Vector2( 
            ( a.x < b.x ) ? a.x : b.x,
            ( a.y < b.y ) ? a.y : b.y );
    }

    //---------------------------------------------------------------------------------------
    //! @brief      各成分の最大値を求めます.
    //---------------------------------------------------------------------------------------
    static S3D_INLINE
    Vector2 Max( const Vector2& a, const Vector2& b )
    {
        return Vector2(
            ( a.x > b.x ) ? a.x : b.x,
            ( a.y > b.y ) ? a.y : b.y );
    }
};


////////////////////////////////////////////////////////////////////////////////////////////
// Vector3 structure
////////////////////////////////////////////////////////////////////////////////////////////
struct Vector3
{
public:
    union 
    {
        struct
        {
            f64 x;      //!< X成分です.
            f64 y;      //!< Y成分です.
            f64 z;      //!< Z成分です.
        };
        f64 v[3];       //!< 各成分を表す配列です.
    };

    //--------------------------------------------------------------------------------------
    //! @brief      コンストラクタです.
    //--------------------------------------------------------------------------------------
    Vector3()
    { /* DO_NOTHING */ }

    //--------------------------------------------------------------------------------------
    //! @brief      引数付きコンストラクタです.
    //--------------------------------------------------------------------------------------
    Vector3( const f64 nx, const f64 ny, const f64 nz ) 
    : x( nx )
    , y( ny )
    , z( nz )
    { /* DO_NOTHING */ }

    //--------------------------------------------------------------------------------------
    //! @brief      コピーコンストラクタです.
    //--------------------------------------------------------------------------------------
    Vector3( const Vector3& value )
    : x( value.x )
    , y( value.y )
    , z( value.z )
    { /* DO_NOTHING */ }

    //--------------------------------------------------------------------------------------
    //! @brief      等価比較演算子です.
    //--------------------------------------------------------------------------------------
    S3D_INLINE
    bool operator == ( const Vector3& b ) const
    {
        return ( x == b.x )
            && ( y == b.y )
            && ( z == b.z );
    }

    //--------------------------------------------------------------------------------------
    //! @brief      非等価比較演算子です.
    //--------------------------------------------------------------------------------------
    S3D_INLINE
    bool operator != ( const Vector3& b ) const
    {
        return ( x != b.x )
            || ( y != b.y )
            || ( z != b.z );
    }

    //--------------------------------------------------------------------------------------
    //! @brief      代入演算子です.
    //--------------------------------------------------------------------------------------
    S3D_INLINE
    Vector3& operator = ( const Vector3& b )
    {
        x = b.x;
        y = b.y;
        z = b.z;
        return (*this);
    }

    //--------------------------------------------------------------------------------------
    //! @brief      加算代入演算子です.
    //--------------------------------------------------------------------------------------
    S3D_INLINE
    Vector3& operator += ( const Vector3& b )
    {
        x += b.x;
        y += b.y;
        z += b.z;
        return (*this);
    }

    //--------------------------------------------------------------------------------------
    //! @brief      減算代入演算子です.
    //--------------------------------------------------------------------------------------
    S3D_INLINE
    Vector3& operator -= ( const Vector3& b )
    {
        x -= b.x;
        y -= b.y;
        z -= b.z;
        return (*this);
    }

    //--------------------------------------------------------------------------------------
    //! @brief      乗算代入演算子です.
    //--------------------------------------------------------------------------------------
    S3D_INLINE
    Vector3& operator *= ( const f64 b )
    {
        x *= b;
        y *= b;
        z *= b;
        return (*this);
    }

    //--------------------------------------------------------------------------------------
    //! @brief      除算代入演算子です.
    //--------------------------------------------------------------------------------------
    S3D_INLINE
    Vector3& operator /= ( const f64 b )
    {
        assert( b != 0.0 );
        x /= b;
        y /= b;
        z /= b;
        return (*this);
    }

    //--------------------------------------------------------------------------------------
    //! @brief      正符号演算子です.
    //--------------------------------------------------------------------------------------
    S3D_INLINE
    Vector3  operator + () const
    { return Vector3( x, y, z ); }

    //--------------------------------------------------------------------------------------
    //! @brief      負符号演算子です.
    //--------------------------------------------------------------------------------------
    S3D_INLINE
    Vector3 operator - () const
    { return Vector3( -x, -y, -z ); }

    //--------------------------------------------------------------------------------------
    //! @brief      加算演算子です.
    //--------------------------------------------------------------------------------------
    S3D_INLINE
    Vector3 operator + (const Vector3 &b) const
    {
        return Vector3(
            x + b.x,
            y + b.y,
            z + b.z);
    }

    //--------------------------------------------------------------------------------------
    //! @brief      減算演算子です.
    //--------------------------------------------------------------------------------------
    S3D_INLINE
    Vector3 operator - (const Vector3 &b) const
    { 
        return Vector3(
            x - b.x,
            y - b.y,
            z - b.z);
    }

    //--------------------------------------------------------------------------------------
    //! @brief      乗算演算子です.
    //--------------------------------------------------------------------------------------
    S3D_INLINE
    Vector3 operator * (const f64 b) const
    { 
        return Vector3(
            x * b,
            y * b,
            z * b);
    }

    //--------------------------------------------------------------------------------------
    //! @brief      除算演算子です.
    //--------------------------------------------------------------------------------------
    S3D_INLINE
    Vector3 operator / (const f64 b) const
    {
        assert( b != 0.0 );
        return Vector3(
            x / b,
            y / b,
            z / b);
    }

    //--------------------------------------------------------------------------------------
    //! @brief      長さの2乗値を求めます.
    //--------------------------------------------------------------------------------------
    S3D_INLINE
    f64 LengthSq() const
    { return ( x * x ) + ( y * y ) + ( z * z ); }

    //--------------------------------------------------------------------------------------
    //! @brief      長さを求めます.
    //--------------------------------------------------------------------------------------
    S3D_INLINE 
    f64 Length() const
    { return sqrt( ( x * x ) + ( y * y ) + ( z * z ) ); }

    //--------------------------------------------------------------------------------------
    //! @brief      正規化します.
    //--------------------------------------------------------------------------------------
    S3D_INLINE
    void Normalize()
    {
        register f64 mag = sqrt( x * x + y * y + z * z );
        assert( mag != 0.0 );
        x /= mag;
        y /= mag;
        z /= mag;
    }

    //--------------------------------------------------------------------------------------
    //! @brief      単位ベクトルを求めます.
    //--------------------------------------------------------------------------------------
    static S3D_INLINE
    Vector3 UnitVector (const Vector3 &v)
    {
        register f64 mag = sqrt( v.x * v.x + v.y * v.y + v.z * v.z );
        assert( mag != 0.0 );
        return Vector3(
            v.x / mag,
            v.y / mag,
            v.z / mag );
    }

    //--------------------------------------------------------------------------------------
    //! @brief      各成分ごとに乗算します.
    //--------------------------------------------------------------------------------------
    static S3D_INLINE
    Vector3 Mul (const Vector3 &v1, const Vector3 &v2)
    { 
        return Vector3(
            v1.x * v2.x,
            v1.y * v2.y,
            v1.z * v2.z);
    }

    //--------------------------------------------------------------------------------------
    //! @brief      内積を求めます.
    //--------------------------------------------------------------------------------------
    static S3D_INLINE
    f64 Dot (const Vector3 &v1, const Vector3 &v2) 
    { return ( v1.x * v2.x ) + ( v1.y * v2.y ) + ( v1.z * v2.z ); }

    //--------------------------------------------------------------------------------------
    //! @brief      外積を求めます.
    //--------------------------------------------------------------------------------------
    static S3D_INLINE
    Vector3 Cross (const Vector3 &v1, const Vector3 &v2) 
    {
        return Vector3(
            (v1.y * v2.z) - (v1.z * v2.y),
            (v1.z * v2.x) - (v1.x * v2.z),
            (v1.x * v2.y) - (v1.y * v2.x)
        );
    }

    //--------------------------------------------------------------------------------------
    //! @brief      反射ベクトルを求めます.
    //--------------------------------------------------------------------------------------
    static S3D_INLINE
    Vector3 Reflect( const Vector3& i, const Vector3& n )
    {
        register f64 dot = ( n.x * i.x ) + ( n.y * i.y ) + ( n.z * i.z );
        register f64 _2dot = 2.0 * dot;

        return Vector3(
            i.x - ( _2dot * n.x ),
            i.y - ( _2dot * n.y ),
            i.z - ( _2dot * n.z ) );
    }

    //---------------------------------------------------------------------------------------
    //! @brief      各成分の最小値を求めます.
    //---------------------------------------------------------------------------------------
    static S3D_INLINE
    Vector3 Min( const Vector3& a, const Vector3& b )
    {
        return Vector3( 
            ( a.x < b.x ) ? a.x : b.x,
            ( a.y < b.y ) ? a.y : b.y,
            ( a.z < b.z ) ? a.z : b.z );
    }

    //---------------------------------------------------------------------------------------
    //! @brief      各成分の最大値を求めます.
    //---------------------------------------------------------------------------------------
    static S3D_INLINE
    Vector3 Max( const Vector3& a, const Vector3& b )
    {
        return Vector3(
            ( a.x > b.x ) ? a.x : b.x,
            ( a.y > b.y ) ? a.y : b.y,
            ( a.z > b.z ) ? a.z : b.z );
    }

    //--------------------------------------------------------------------------------------
    //! @brief      法線ベクトルを求めます.
    //--------------------------------------------------------------------------------------
    static S3D_INLINE
    Vector3 ComputeNormal( const Vector3& a, const Vector3& b, const Vector3& c )
    {
        Vector3 e1 = b - a;
        Vector3 e2 = c - a;
        return Vector3::UnitVector( Vector3::Cross( e1, e2 ) );
    }

    //--------------------------------------------------------------------------------------
    //! @brief      矩形の法線ベクトルを求めます.
    //--------------------------------------------------------------------------------------
    static S3D_INLINE
    Vector3 ComputeQuadNormal( const Vector3& a, const Vector3& b, const Vector3& c, const Vector3& d )
    {
        Vector3 n1a = ComputeNormal( a, b, c );
        Vector3 n1b = ComputeNormal( a, c, d );
        Vector3 n2a = ComputeNormal( b, c, d );
        Vector3 n2b = ComputeNormal( b, d, c );

        if ( Vector3::Dot( n1a, n1b ) > Vector3::Dot( n2a, n2b ) )
        { return Vector3::UnitVector( n1a + n1b ); }
        else
        { return Vector3::UnitVector( n2a + n2b ); }
    }
};

//------------------------------------------------------------------------------------------
//! @brief      乗算演算子です.
//------------------------------------------------------------------------------------------
S3D_INLINE 
Vector3 operator * (const f64 f, const Vector3 &v)
{ return v * f; }


////////////////////////////////////////////////////////////////////////////////////////////
// Ray structure
////////////////////////////////////////////////////////////////////////////////////////////
struct Ray
{
    Vector3 pos;            //!< 位置座標です.
    Vector3 dir;            //!< 方向ベクトルです.
    Vector3 invDir;         //!< 方向ベクトルの各成分の逆数です.
    s32     sign[3];        //!< 方向ベクトルの符号です.

    //--------------------------------------------------------------------------------------
    //! @brief      コンストラクタです.
    //--------------------------------------------------------------------------------------
    Ray( const Vector3& p, const Vector3& d )
    { Update( p, d ); }

    //--------------------------------------------------------------------------------------
    //! @brief      コピーコンストラクタです.
    //--------------------------------------------------------------------------------------
    Ray( const Ray& value )
    { Update( value.pos, value.dir ); }

    //--------------------------------------------------------------------------------------
    //! @brief      レイを更新します.
    //--------------------------------------------------------------------------------------
    void Update( const Vector3& p, const Vector3& d )
    {
        pos = p;
        dir = d;
        invDir = Vector3( 1.0 / dir.x, 1.0 / dir.y, 1.0 / dir.z );
        sign[0] = ( dir.x > 0.0 ) ? 0 : 1;
        sign[1] = ( dir.y > 0.0 ) ? 0 : 1;
        sign[2] = ( dir.z > 0.0 ) ? 0 : 1;
    }
};


} // namespace s3d



#endif//__S3D_MATH__