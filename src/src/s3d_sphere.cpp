﻿//-------------------------------------------------------------------------------------------------
// File : s3d_sphere.cpp
// Desc : Sphere Shape Module.
// Copyright(c) Project Asura. All right reserved.
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
// Includes
//-------------------------------------------------------------------------------------------------
#include <s3d_sphere.h>


namespace s3d {

///////////////////////////////////////////////////////////////////////////////////////////////////
// Sphere class
///////////////////////////////////////////////////////////////////////////////////////////////////

//-------------------------------------------------------------------------------------------------
//      コンストラクタです.
//-------------------------------------------------------------------------------------------------
Sphere::Sphere(f32 radius, const Vector3& center, IMaterial* pMaterial)
: m_Count       ( 1 )
, m_Radius      ( radius )
, m_Center      ( center )
, m_pMaterial   ( pMaterial )
{
    Vector3 min( m_Center.x - m_Radius, m_Center.y - m_Radius, m_Center.z - m_Radius );
    Vector3 max( m_Center.y + m_Radius, m_Center.y + m_Radius, m_Center.z + m_Radius );
    m_Box = BoundingBox( min, max );
}

//-------------------------------------------------------------------------------------------------
//      デストラクタです.
//-------------------------------------------------------------------------------------------------
Sphere::~Sphere()
{ /* DO_NOTHING */ }

//-------------------------------------------------------------------------------------------------
//      参照カウントを増やします.
//-------------------------------------------------------------------------------------------------
void Sphere::AddRef()
{ m_Count++; }

//-------------------------------------------------------------------------------------------------
//      解放処理を行います.
//-------------------------------------------------------------------------------------------------
void Sphere::Release()
{
    m_Count--;
    if ( m_Count == 0 )
    { delete this; }
}

//-------------------------------------------------------------------------------------------------
//      参照カウントを取得します.
//-------------------------------------------------------------------------------------------------
u32 Sphere::GetCount() const
{ return m_Count; }

//-------------------------------------------------------------------------------------------------
//      交差判定を行います.
//-------------------------------------------------------------------------------------------------
bool Sphere::IsHit(const Ray &ray, HitRecord& record ) const
{
    const auto po = m_Center - ray.pos;
    const auto b  = Vector3::Dot(po, ray.dir);
    const auto D4 = b * b - Vector3::Dot(po, po) + m_Radius * m_Radius;

    if ( D4 < 0.0f )
    { return false; }   // 交差しなかった.

    const auto sqrt_D4 = sqrt(D4);
    const auto t1 = b - sqrt_D4;
    const auto t2 = b + sqrt_D4;

    if (t1 < F_HIT_MIN && t2 < F_HIT_MIN)
    { return false; }   // 交差しなかった.

    auto dist = ( t1 > F_HIT_MIN ) ? t1 : t2;
    if ( dist > record.distance )
    { return false; }

    record.distance  = dist;
    record.position  = ray.pos + record.distance * ray.dir;
    record.pShape    = this;
    record.pMaterial = m_pMaterial;

    auto theta = acosf( record.normal.y );
    auto phi   = atan2f( record.normal.x, record.normal.z );
    if ( phi < 0.0f )
    { phi += F_2PI; }

    record.texcoord = Vector2( phi * F_1DIV2PI, ( F_PI - theta ) * F_1DIVPI );

    // フラットシェーディング.
    record.normal   = Vector3::UnitVector(record.position - m_Center);

    // 交差した.
    return true;
}

//-------------------------------------------------------------------------------------------------
//      バウンディングボックスを取得します.
//-------------------------------------------------------------------------------------------------
BoundingBox Sphere::GetBox() const
{ return m_Box; }

//-------------------------------------------------------------------------------------------------
//      中心座標を取得します.
//-------------------------------------------------------------------------------------------------
Vector3 Sphere::GetCenter() const
{ return m_Center; }

//-------------------------------------------------------------------------------------------------
//      生成処理を行います.
//-------------------------------------------------------------------------------------------------
bool Sphere::Create(f32 radius, const Vector3& center, IMaterial* pMaterial, IShape** ppShape)
{
    auto instance = new(std::nothrow) Sphere(radius, center, pMaterial);
    if ( instance == nullptr )
    { return false; }

    *ppShape = instance;
    return true;
}

} // namespace s3d