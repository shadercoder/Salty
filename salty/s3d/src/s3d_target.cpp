﻿//------------------------------------------------------------------------------
// File : s3d_target.cpp
// Desc : Render Target Module.
// Copyright(c) Project Asura. All right reserved.
//-------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
// Includes
//-------------------------------------------------------------------------------
#include <s3d_target.h>
#include <cassert>
#include <cmath>


namespace s3d {

/////////////////////////////////////////////////////////////////////////////////
// RenderTarget class
/////////////////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------------------
//      コンストラクタです.
//-----------------------------------------------------------------------------
RenderTarget::RenderTarget()
: m_Width   ( 0 )
, m_Height  ( 0 )
, m_pFB     ( nullptr )
{ /* DO_NOTHING */ }

//-----------------------------------------------------------------------------
//      デストラクタです.
//-----------------------------------------------------------------------------
RenderTarget::~RenderTarget()
{
    Term();
}

//-----------------------------------------------------------------------------
//      初期化処理です.
//-----------------------------------------------------------------------------
void RenderTarget::Init( const u32 width, const u32 height )
{
    Color3 clearColor( 0.0, 0.0, 0.0 );
    Init( width, height, clearColor );
}

//-----------------------------------------------------------------------------
//      初期化処理です.
//-----------------------------------------------------------------------------
void RenderTarget::Init( const u32 width, const u32 height, const Color3& clearColor )
{
    m_Width  = width;
    m_Height = height;
    m_pFB    = new Color3[ m_Width * m_Height ];
    Clear( clearColor);
}

//-----------------------------------------------------------------------------
//      終了処理です.
//-----------------------------------------------------------------------------
void RenderTarget::Term()
{
    if ( m_pFB )
    {
        delete [] m_pFB;
        m_pFB = nullptr;
    }
}

//-----------------------------------------------------------------------------
//      フレームバッファをクリアします.
//-----------------------------------------------------------------------------
void RenderTarget::Clear( const Color3& clearColor )
{
    if ( m_pFB != nullptr )
    {
        for( u32 i=0; i<m_Height; ++i )
        {
            for( u32 j=0; j<m_Width; ++j )
            {
                m_pFB[ i * m_Width + j ] = clearColor;
            }
        }
    }
}

//-----------------------------------------------------------------------------
//      フレームバッファのピクセルカラーを設定します.
//-----------------------------------------------------------------------------
void RenderTarget::SetPixel( const u32 x, const u32 y, const Color3& value )
{
    assert( x >= m_Width );
    assert( y >= m_Height);
    assert( m_pFB != nullptr );

    m_pFB[ y * m_Width + x ] = value;
}

//-----------------------------------------------------------------------------
//      フレームバッファのピクセルカラーを取得します.
//-----------------------------------------------------------------------------
Color3 RenderTarget::GetPixel( const u32 x, const u32 y )
{
    assert( x >= m_Width );
    assert( y >= m_Height );
    assert( m_pFB != nullptr );

    return m_pFB[ y * m_Width + x ];
}

//-----------------------------------------------------------------------------
//      フレームバッファを取得します.
//-----------------------------------------------------------------------------
Color3* RenderTarget::GetFrameBuffer()
{ return m_pFB; }

//-----------------------------------------------------------------------------
//      横幅を取得します.
//-----------------------------------------------------------------------------
u32 RenderTarget::GetWidth() const
{ return m_Width; }

//-----------------------------------------------------------------------------
//      縦幅を取得します.
//-----------------------------------------------------------------------------
u32 RenderTarget::GetHeight() const
{ return m_Height; }


} // namespace s3d

