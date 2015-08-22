﻿//----------------------------------------------------------------------------------
// File : s3d_texture.h
// Desc : Texture Module.
// Copyright(c) Project Asura. All right reserved.
//----------------------------------------------------------------------------------
#pragma once

//----------------------------------------------------------------------------------
// Includes
//----------------------------------------------------------------------------------
#include <s3d_math.h>


namespace s3d {

////////////////////////////////////////////////////////////////////////////////////
// TEXTURE_ADDRESS_MODE enum
////////////////////////////////////////////////////////////////////////////////////
enum TEXTURE_ADDRESS_MODE
{
    TEXTURE_ADDRESS_WRAP = 0,       //!< 0.0 ～ 1.0 の範囲外の値の場合に，テクスチャ画像を繰り返し適用します.
    TEXTURE_ADDRESS_CLAMP,          //!< テクスチャ座標を 0.0 ～ 1.0 の範囲に制限します。範囲外の部分は淵部分が引き伸ばされます.
    TEXTURE_ADDRESS_BORADER,        //!< テクスチャ座標を 0.0 ～ 1.0 の範囲に制限します。範囲外の部分は境界色になります.
    //TEXTURE_ADDRESS_MIRROR
};

/////////////////////////////////////////////////////////////////////////////////////
// TEXTURE_FILTER_MODE enum
/////////////////////////////////////////////////////////////////////////////////////
enum TEXTURE_FILTER_MODE
{
    TEXTURE_FILTER_NEAREST,     //!< 最近傍法.
    TEXTURE_FILTER_BILINEAR,    //!< バイリニア補間.
};

////////////////////////////////////////////////////////////////////////////////////
// TextureSampler
////////////////////////////////////////////////////////////////////////////////////
struct TextureSampler
{
    TEXTURE_ADDRESS_MODE address;           //!< テクスチャU座標のアドレッシングモードです.
    TEXTURE_FILTER_MODE  filter;            //!< テクスチャフィルタリング.
    Color4               boarderColor;      //!< 境界色です.

    //------------------------------------------------------------------------------
    //! @brief      コンストラクタです.
    //------------------------------------------------------------------------------
    TextureSampler()
    : address       ( TEXTURE_ADDRESS_WRAP )
    , filter        ( TEXTURE_FILTER_BILINEAR )
    , boarderColor  ( 0.0f, 0.0f, 0.0f, 1.0f )
    { /* DO_NOTHING */ }

    //------------------------------------------------------------------------------
    //! @brief      引数付きコンストラクタです.
    //------------------------------------------------------------------------------
    TextureSampler
    ( 
        const TEXTURE_ADDRESS_MODE _address,
        const TEXTURE_FILTER_MODE  _filter,
        const Color4&              _boarderColor
    )
    : address       ( _address )
    , filter        ( _filter )
    , boarderColor  ( _boarderColor )
    { /* DO_NOTHING */ }
};


////////////////////////////////////////////////////////////////////////////////////
// Texture2D class
////////////////////////////////////////////////////////////////////////////////////
class Texture2D
{
    //==============================================================================
    // list of friend classes and methods.
    //==============================================================================
    /* NOTHING */

public:
    //==============================================================================
    // public variables.
    //==============================================================================
    /* NOTHING */

    //==============================================================================
    // public methods.
    //==============================================================================

    //------------------------------------------------------------------------------
    //! @brief      コンストラクタです.
    //------------------------------------------------------------------------------
    Texture2D();

    //------------------------------------------------------------------------------
    //! @brief      引数付きコンストラクタです.
    //------------------------------------------------------------------------------
    Texture2D( const char* );

    //------------------------------------------------------------------------------
    //! @brief      コピーコンストラクタです.
    //------------------------------------------------------------------------------
    Texture2D( const Texture2D& );

    //------------------------------------------------------------------------------
    //! @brief      デストラクタです.
    //------------------------------------------------------------------------------
    virtual ~Texture2D();

    //------------------------------------------------------------------------------
    //! @brief      ファイルからロードします.
    //------------------------------------------------------------------------------
    bool LoadFromFile( const char* );

    //------------------------------------------------------------------------------
    //! @brief      メモリ解放処理を行います.
    //------------------------------------------------------------------------------
    void Release();

    //------------------------------------------------------------------------------
    //! @brief      テクスチャフェッチします.
    //------------------------------------------------------------------------------
    Color4 Sample( const TextureSampler&, const Vector2& ) const;

    //------------------------------------------------------------------------------
    //! @brief      アルファテストを行います.
    //------------------------------------------------------------------------------
    bool AlphaTest( const TextureSampler&, const Vector2&, const f32 value ) const;

protected:
    //==============================================================================
    // protected variables.
    //==============================================================================
    /* NOTHING */

    //==============================================================================
    // protected methods.
    //==============================================================================
    /* NOTHING */

private:
    //==============================================================================
    // private variables.
    //==============================================================================
    u32     m_Width;            //!< 画像の横幅です.
    u32     m_Height;           //!< 画像の縦幅です.
    u32     m_Size;             //!< データサイズです.
    u32     m_ComponentCount;   //!< チャンネル数です(RGB=3, RGBA=4)
    f32*    m_pPixels;          //!< ピクセルデータです.

    //==============================================================================
    // private methods.
    //==============================================================================

    //------------------------------------------------------------------------------
    //! @brief      指定されたピクセルを取得します.
    //------------------------------------------------------------------------------
    Color4 GetPixel( s32 x, s32 y, const TextureSampler& sampler ) const;

    //------------------------------------------------------------------------------
    //! @brief      最近傍フィルタを適用してサンプリングします.
    //------------------------------------------------------------------------------
    Color4 NearestSample ( const TextureSampler&, const Vector2& ) const;

    //------------------------------------------------------------------------------
    //! @brief      バイリニアフィルタを適用してサンプリングします.
    //------------------------------------------------------------------------------
    Color4 BilinearSample( const TextureSampler&, const Vector2& ) const;
};


} // namespace s3d
