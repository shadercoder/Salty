﻿//----------------------------------------------------------------------------------------
// File : s3d_mesh.h
// Desc : Mesh Module.
// Copyright(c) Project Asura. All right reserved.
//----------------------------------------------------------------------------------------

#ifndef __S3D_MESH_H__
#define __S3D_MESH_H__

//----------------------------------------------------------------------------------------
// Includes
//----------------------------------------------------------------------------------------
#include <s3d_math.h>
#include <s3d_shape.h>
#include <s3d_material.h>
#include <s3d_bvh.h>


namespace s3d {

/////////////////////////////////////////////////////////////////////////////////////////
// ResMesh structure
/////////////////////////////////////////////////////////////////////////////////////////
class ResMesh
{
public:
    /////////////////////////////////////////////////////////////////////////////////////
    // Vertex structure
    /////////////////////////////////////////////////////////////////////////////////////
    struct Vertex
    {
        Vector3     position;       //!< 位置座標です.
        Vector3     normal;         //!< 法線ベクトルです.
        Vector2     texcoord;       //!< テクスチャ座標です.
    };

    ////////////////////////////////////////////////////////////////////////////////////
    // Material structure
    ////////////////////////////////////////////////////////////////////////////////////
    struct Material
    {
        Vector3     diffuse;        //!< 拡散反射色です.
        Vector3     emissive;       //!< 自己放射色です.
        f64         refractivity;   //!< 屈折率です.
        f64         roughness;      //!< 面の粗さです.
        char        diffuseMap[256];//!< ディフューズマップ名です.
    };

    ////////////////////////////////////////////////////////////////////////////////////
    // Subset structure
    ////////////////////////////////////////////////////////////////////////////////////
    struct Subset
    {
        u32         indexOffset;    //!< インデックス開始番号です.
        u32         indexCount;     //!< インデックス数です.
        u32         materialID;     //!< マテリアル番号です.
    };

    //==================================================================================
    // public variables.
    //==================================================================================
    u32         m_VertexCount;      //!< 頂点数です.
    u32         m_IndexCount;       //!< インデックス数です.
    u32         m_MaterialCount;    //!< マテリアル数です.
    u32         m_SubsetCount;      //!< サブセット数です.

    Vertex*     m_pVertex;          //!< 頂点データです.
    u32*        m_pIndex;           //!< インデックスデータです.
    Material*   m_pMaterial;        //!< マテリアルデータです.
    Subset*     m_pSubset;          //!< サブセットデータです.


    //==================================================================================
    // public methods.
    //==================================================================================

    //----------------------------------------------------------------------------------
    //! @brief      コンストラクタです.
    //----------------------------------------------------------------------------------
    ResMesh();

    //----------------------------------------------------------------------------------
    //! @brief      デストラクタです.
    //----------------------------------------------------------------------------------
    virtual ~ResMesh();

    //----------------------------------------------------------------------------------
    //! @brief      ファイルからロードします.
    //----------------------------------------------------------------------------------
    bool LoadFromFile( const char* filename );

    //----------------------------------------------------------------------------------
    //! @brief      メモリ解放処理を行います.
    //----------------------------------------------------------------------------------
    void Release();

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
    /* NOTHING */

    //==================================================================================
    // private methods.
    //==================================================================================
    ResMesh         ( const ResMesh& );
    void operator = ( const ResMesh& );
};


} // namespace s3d


#endif//__S3D_MESH_H__