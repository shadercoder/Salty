﻿//-------------------------------------------------------------------------------------------------
// File : s3d_phong.cpp
// Desc : Phong Material.
// Copyright(c) Project Asura. All right reserved.
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
// Includes
//-------------------------------------------------------------------------------------------------
#include <s3d_phong.h>


namespace s3d {

///////////////////////////////////////////////////////////////////////////////////////////////////
// Phong class
///////////////////////////////////////////////////////////////////////////////////////////////////

//-------------------------------------------------------------------------------------------------
//      コンストラクタです.
//-------------------------------------------------------------------------------------------------
Phong::Phong(const Color4& specular, f32 power, const Color4& emissive)
: m_Count   (1)
, m_Specular(specular)
, m_Power   (power)
, m_Emissive(emissive)
{
    m_Threshold = m_Specular.GetX();
    m_Threshold = s3d::Max( m_Threshold, m_Specular.GetY() );
    m_Threshold = s3d::Max( m_Threshold, m_Specular.GetZ() );
}

//-------------------------------------------------------------------------------------------------
//      デストラクタです.
//-------------------------------------------------------------------------------------------------
Phong::~Phong()
{ /* DO_NOTHING */}

//-------------------------------------------------------------------------------------------------
//      参照カウントを増やします.
//-------------------------------------------------------------------------------------------------
void Phong::AddRef()
{ m_Count++; }

//-------------------------------------------------------------------------------------------------
//      解放処理を行います.
//-------------------------------------------------------------------------------------------------
void Phong::Release()
{
    m_Count--;
    if ( m_Count == 0 )
    { delete this; }
}

//-------------------------------------------------------------------------------------------------
//      参照カウントを取得します.
//-------------------------------------------------------------------------------------------------
u32 Phong::GetCount() const
{ return m_Count; }

//-------------------------------------------------------------------------------------------------
//      シェーディングします.
//-------------------------------------------------------------------------------------------------
Color4 Phong::Shade( ShadingArg& arg ) const
{
    // 補正済み法線データ (レイの入出を考慮済み).
    const Vector3 normalMod = ( Vector3::Dot ( arg.normal, arg.input ) < 0.0 ) ? arg.normal : -arg.normal;

    Vector3 dir;
    f32 dots = 0.0f;

    {
        // インポータンスサンプリング.
        const f32 phi = F_2PI * arg.random.GetAsF32();
        const f32 cosTheta = powf( 1.0f - arg.random.GetAsF32(), 1.0f / ( m_Power + 1.0f ) );
        const f32 sinTheta = SafeSqrt( 1.0f - ( cosTheta * cosTheta ) );
        const f32 x = cosf( phi ) * sinTheta;
        const f32 y = sinf( phi ) * sinTheta;
        const f32 z = cosTheta;

        // 反射ベクトル.
        Vector3 w = Vector3::Reflect( arg.input, normalMod );
        w.Normalize();

        // 基底ベクトルを求める.
        OrthonormalBasis onb;
        onb.InitFromW( w );

        // 出射方向.
        dir = Vector3::UnitVector( onb.u * x + onb.v * y + onb.w * z );

        // 出射方向と法線ベクトルの内積を求める.
        dots = Vector3::Dot( dir, normalMod );
    }

    arg.output = dir;
    arg.dice = (arg.random.GetAsF32() >= m_Threshold);

    return m_Specular * dots / m_Threshold;
}

//-------------------------------------------------------------------------------------------------
//      エミッシブカラーを取得します.
//-------------------------------------------------------------------------------------------------
Color4 Phong::GetEmissive() const
{ return m_Emissive; }

//-------------------------------------------------------------------------------------------------
//      デルタ関数をもつかどうか?
//-------------------------------------------------------------------------------------------------
bool Phong::HasDelta() const
{ return false; }

//-------------------------------------------------------------------------------------------------
//      生成処理です.
//-------------------------------------------------------------------------------------------------
IMaterial* Phong::Create(const Color4& specular, f32 power)
{ return Phong::Create(specular, power, Color4(0.0f, 0.0f, 0.0f, 1.0f)); }

//-------------------------------------------------------------------------------------------------
//      生成処理です.
//-------------------------------------------------------------------------------------------------
IMaterial* Phong::Create(const Color4& specular, f32 power, const Color4& emissive)
{ return new(std::nothrow) Phong(specular, power, emissive); }

} // namespace s3d
