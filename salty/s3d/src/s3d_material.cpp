﻿//----------------------------------------------------------------------------
// File : s3d_material.cpp
// Desc : Material Module.
// Copyright(c) Project Asura. All right reserved.
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Includes
//----------------------------------------------------------------------------
#include <s3d_material.h>


namespace s3d {

//////////////////////////////////////////////////////////////////////////////
// Matte class
//////////////////////////////////////////////////////////////////////////////
Matte::Matte( const Color3& color )
: m_Color( color )
{
}

Matte::Matte( const Matte& value )
: m_Color( value.m_Color )
{
}

Color3 Matte::Shade( const Vector3&, const Vector3&, Vector3&  )
{
    return m_Color;
}


//////////////////////////////////////////////////////////////////////////////
// Clay class
//////////////////////////////////////////////////////////////////////////////
Clay::Clay( const Color3& color, const f64 roughness )
: m_Color    ( color )
, m_Roughness( roughness )
{
}

Clay::Clay( const Clay& value )
: m_Color( value.m_Color )
, m_Roughness( value.m_Roughness )
{
}

Color3 Clay::Shade( const Vector3&, const Vector3&, Vector3& )
{
    return m_Color;
}


//////////////////////////////////////////////////////////////////////////////
// Plastic class
//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
// Metal class
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// Mirror class
//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
// Glass class
//////////////////////////////////////////////////////////////////////////////


} // namespace s3d
