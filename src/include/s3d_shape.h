﻿//-------------------------------------------------------------------------------------------------
// File : s3d_shape.h
// Desc : Shape Module.
// Copyright(c) Project Asura. All right reserved.
//-------------------------------------------------------------------------------------------------
#pragma once

//-------------------------------------------------------------------------------------------------
// Includes
//-------------------------------------------------------------------------------------------------
#include <s3d_math.h>
#include <s3d_reference.h>


namespace s3d {

//-------------------------------------------------------------------------------------------------
// Forward Declarations.
//-------------------------------------------------------------------------------------------------
struct IShape;
struct IMaterial;


///////////////////////////////////////////////////////////////////////////////////////////////////
// Vertex structure
///////////////////////////////////////////////////////////////////////////////////////////////////
struct Vertex
{
    Vector3     Position;       //!< 位置座標です.
    Vector3     Normal;         //!< 法線ベクトルです.
    Vector2     TexCoord;       //!< テクスチャ座標です.
};


///////////////////////////////////////////////////////////////////////////////////////////////////
// HitRecord structure
///////////////////////////////////////////////////////////////////////////////////////////////////
struct HitRecord
{
    f32                 distance;       //!< 衝突点までの距離.
    Vector3             position;       //!< 衝突点の位置座標.
    Vector3             normal;         //!< 法線ベクトル.
    Vector2             texcoord;       //!< 衝突点のテクスチャ座標です.
    const IShape*       pShape;         //!< オブジェクトへのポインタ.
    const IMaterial*    pMaterial;      //!< マテリアルへのポインタ.

    //---------------------------------------------------------------------------------------------
    //! @brief      コンストラクタです.
    //---------------------------------------------------------------------------------------------
    HitRecord()
    : distance   ( F_MAX )
    , position   ( 0.0f, 0.0f, 0.0f )
    , normal     ( 0.0f, 0.0f, 0.0f )
    , texcoord   ( 0.0f, 0.0f )
    , pShape     ( nullptr )
    , pMaterial  ( nullptr )
    { /* DO_NOTHING */ }
};


///////////////////////////////////////////////////////////////////////////////////////////////////
// IShape interface
///////////////////////////////////////////////////////////////////////////////////////////////////
struct IShape : IReference
{
    virtual ~IShape() {}
    virtual bool        IsHit    ( const RaySet&, HitRecord& ) const = 0;
    virtual BoundingBox GetBox   () const = 0;
    virtual Vector3     GetCenter() const = 0;
};

} // namespace s3d


