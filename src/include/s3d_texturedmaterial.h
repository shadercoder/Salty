﻿//-------------------------------------------------------------------------------------------------
// File : s3d_texturedmaterial.h
// Desc : Textured Material.
// Copyright(c) Project Asura. All right reserved.
//-------------------------------------------------------------------------------------------------
#pragma once

//-------------------------------------------------------------------------------------------------
// Includes
//-------------------------------------------------------------------------------------------------
#include <s3d_material.h>
#include <s3d_texture.h>
#include <atomic>


namespace s3d {

///////////////////////////////////////////////////////////////////////////////////////////////////
// TexturedMaterial class
///////////////////////////////////////////////////////////////////////////////////////////////////
class TexturedMaterial : IMaterial
{
    //=============================================================================================
    // list of friend classes and methods.
    //=============================================================================================
    /* NOTHING */

public:
    //=============================================================================================
    // public variables.
    //=============================================================================================
    /* NOTHING */

    //=============================================================================================
    // public methods.
    //=============================================================================================

    //---------------------------------------------------------------------------------------------
    //! @brief      生成処理を行います.
    //---------------------------------------------------------------------------------------------
    static IMaterial* Create(
        const Texture2D*        pTexture,
        const TextureSampler*   pSampler,
        IMaterial*              pMaterial);

    //---------------------------------------------------------------------------------------------
    //! @brief      参照カウントを増やします.
    //---------------------------------------------------------------------------------------------
    void AddRef() override;

    //---------------------------------------------------------------------------------------------
    //! @brief      解放処理を行います.
    //---------------------------------------------------------------------------------------------
    void Release() override;

    //---------------------------------------------------------------------------------------------
    //! @brief      参照カウントを取得します.
    //---------------------------------------------------------------------------------------------
    u32 GetCount() const override;

    //---------------------------------------------------------------------------------------------
    //! @brief      シェーディングします.
    //---------------------------------------------------------------------------------------------
    Color4 Shade( ShadingArg& arg ) const override;

    //---------------------------------------------------------------------------------------------
    //! @brief      エミッシブカラーを取得します.
    //---------------------------------------------------------------------------------------------
    Color4 GetEmissive() const override;

    //---------------------------------------------------------------------------------------------
    //! @brief      デルタ関数をもつかどうか?
    //---------------------------------------------------------------------------------------------
    bool HasDelta() const override;

private:
    //=============================================================================================
    // private variables.
    //=============================================================================================
    std::atomic<u32>        m_Count;        //!< 参照カウントです.
    const Texture2D*        m_pTexture;     //!< テクスチャです.
    const TextureSampler*   m_pSampler;     //!< サンプラーです.
    IMaterial*              m_pMaterial;    //!< マテリアルです.

    //=============================================================================================
    // private methods.
    //=============================================================================================

    //---------------------------------------------------------------------------------------------
    //! @brief      コンストラクタです.
    //---------------------------------------------------------------------------------------------
    TexturedMaterial(
        const Texture2D*        pTexture,
        const TextureSampler*   pSampler,
        IMaterial*              pMaterial);

    //---------------------------------------------------------------------------------------------
    //! @brief      デストラクタです.
    //---------------------------------------------------------------------------------------------
    ~TexturedMaterial();
};

} // namespace s3d