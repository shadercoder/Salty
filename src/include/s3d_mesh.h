﻿//----------------------------------------------------------------------------------------
// File : s3d_mesh.h
// Desc : Mesh Module.
// Copyright(c) Project Asura. All right reserved.
//----------------------------------------------------------------------------------------
#pragma once

//----------------------------------------------------------------------------------------
// Includes
//----------------------------------------------------------------------------------------
#include <vector>
#include <s3d_math.h>
#include <s3d_shape.h>
#include <s3d_material.h>


namespace s3d {

////////////////////////////////////////////////////////////////////////////////////
// MeshMaterial structure
////////////////////////////////////////////////////////////////////////////////////
struct MeshMaterial : IMaterial
{
    Color           Diffuse;        //!< 拡散反射成分です.
    Color           Emissive;       //!< 自己照明成分です.
    Texture2D*      pDiffuseMap;    //!< ディフューズマップです.
    TextureSampler* pDiffuseSmp;    //!< ディフューズマップのサンプラーです.
    f32             Threshold;      //!< 閾値です.

    //------------------------------------------------------------------------------
    //! @brief      コンストラクタです.
    //------------------------------------------------------------------------------
    MeshMaterial( )
    { /* DO_NOThiNG */ }

    //------------------------------------------------------------------------------
    //! @brief      引数付きコンストラクタです.
    //------------------------------------------------------------------------------
    MeshMaterial( const Color& diffuse, const Color& emissive );

    //------------------------------------------------------------------------------
    //! @brief      自己照明成分を取得します.
    //------------------------------------------------------------------------------
    Color   GetEmissive( ) const;

    //------------------------------------------------------------------------------
    //! @brief      ロシアンルーレットの閾値を取得します.
    //------------------------------------------------------------------------------
    f32     GetThreshold( ) const;

    //------------------------------------------------------------------------------
    //! @brief      色を計算します.
    //------------------------------------------------------------------------------
    Color   ComputeColor( ShadingArg& arg ) const;

#if 1
    Color   GetDebugColor() const;
#endif
};

/////////////////////////////////////////////////////////////////////////////////////////
// Mesh structure
/////////////////////////////////////////////////////////////////////////////////////////
class Mesh : public IShape
{
public:
    //==================================================================================
    // public variables.
    //==================================================================================
    /* NOTHING */

    //==================================================================================
    // public methods.
    //==================================================================================

    //----------------------------------------------------------------------------------
    //! @brief      コンストラクタです.
    //----------------------------------------------------------------------------------
    Mesh();

    //----------------------------------------------------------------------------------
    //! @brief      デストラクタです.
    //----------------------------------------------------------------------------------
    virtual ~Mesh();

    //----------------------------------------------------------------------------------
    //! @brief      ファイルからロードします.
    //----------------------------------------------------------------------------------
    bool LoadFromFile( const char* filename );

    //----------------------------------------------------------------------------------
    //! @brief      メモリ解放処理を行います.
    //----------------------------------------------------------------------------------
    void Release();

    //----------------------------------------------------------------------------------
    //! @brief      交差判定します.
    //----------------------------------------------------------------------------------
    bool IsHit(const Ray&, HitRecord&) const;

    //----------------------------------------------------------------------------------
    //! @brief      バウンディングボックスを取得します.
    //----------------------------------------------------------------------------------
    BoundingBox GetBox() const;

    //----------------------------------------------------------------------------------
    //! @brief      中心座標を取得します.
    //----------------------------------------------------------------------------------
    Vector3 GetCenter() const;

    //----------------------------------------------------------------------------------
    //! @brief      基本図形かどうか判定します.
    //----------------------------------------------------------------------------------
    bool IsPrimitive() const;

protected:
    //==================================================================================
    // protected variables.
    //==================================================================================
    /* NOTHING */

    //==================================================================================
    // protected methods.
    //==================================================================================
    /* NOTHING */

private:
    //==================================================================================
    // private variables.
    //==================================================================================
    TextureSampler              m_DiffuseSmp;       //!< ディフューズマップのサンプラーです.
    IShape*                     m_pBVH;             //!< BVHです.
    Vector3                     m_Center;           //!< 中心座標.
    std::vector<IShape*>        m_Triangles;
    std::vector<MeshMaterial>   m_Materials;
    std::vector<Texture2D>      m_Textures;

    //==================================================================================
    // private methods.
    //==================================================================================
    Mesh            ( const Mesh& ) = delete;
    void operator = ( const Mesh& ) = delete;
};


} // namespace s3d
