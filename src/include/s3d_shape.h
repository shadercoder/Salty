﻿//-----------------------------------------------------------------------------------
// File : s3d_shape.h
// Desc : Shape Module.
// Copyright(c) Project Asura. All right reserved.
//-----------------------------------------------------------------------------------

#ifndef __S3D_SHAPE_H__
#define __S3D_SHAPE_H__

//-----------------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------------
#include <s3d_math.h>
#include <s3d_idisposable.h>


namespace s3d {

//-----------------------------------------------------------------------------------
// Forward Declarations.
//-----------------------------------------------------------------------------------
struct IShape;
struct IMaterial;


/////////////////////////////////////////////////////////////////////////////////////
// HitRecord structure
/////////////////////////////////////////////////////////////////////////////////////
struct HitRecord
{
    f32                 distance;       //!< 衝突点までの距離.
    Vector3             position;       //!< 衝突点の位置座標.
    Vector3             normal;         //!< 法線ベクトル.
    Vector2             texcoord;       //!< 衝突点のテクスチャ座標です.
    const IShape*       pShape;         //!< オブジェクトへのポインタ.
    const IMaterial*    pMaterial;      //!< マテリアルへのポインタ.

    //-------------------------------------------------------------------------------
    //! @brief      コンストラクタです.
    //-------------------------------------------------------------------------------
    HitRecord()
    : distance   ( F_MAX )
    , position   ( 0.0f, 0.0f, 0.0f )
    , normal     ( 0.0f, 0.0f, 0.0f )
    , texcoord   ( 0.0f, 0.0f )
    , pShape     ( nullptr )
    , pMaterial  ( nullptr )
    { /* DO_NOTHING */ }
};


/////////////////////////////////////////////////////////////////////////////////////
// IShape interface
/////////////////////////////////////////////////////////////////////////////////////
struct IShape
{
    //-------------------------------------------------------------------------------
    //! @brief      交差判定します.
    //-------------------------------------------------------------------------------
    virtual bool IsHit( const Ray&, HitRecord& record ) const = 0;

    //-------------------------------------------------------------------------------
    //! @brief      バウンディングボックスを取得します.
    //-------------------------------------------------------------------------------
    virtual BoundingBox GetBox() const = 0;

    //-------------------------------------------------------------------------------
    //! @brief      基本図形かどうか判定します.
    //-------------------------------------------------------------------------------
    virtual bool IsPrimitive() const = 0;

    //-------------------------------------------------------------------------------
    //! @brief      中心座標を取得します.
    //-------------------------------------------------------------------------------
    virtual Vector3 GetCenter() const = 0;
};


///////////////////////////////////////////////////////////////////////////////////////////////////
// Instance class
///////////////////////////////////////////////////////////////////////////////////////////////////
class Instance : public IShape
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
    //! @brief      コンストラクタです.
    //---------------------------------------------------------------------------------------------
    explicit Instance( const IShape* shape, const Matrix& world );

    //---------------------------------------------------------------------------------------------
    //! @brief      デストラクタです.
    //---------------------------------------------------------------------------------------------
    virtual ~Instance();

    //---------------------------------------------------------------------------------------------
    //! @brief      交差判定を行います.
    //---------------------------------------------------------------------------------------------
    bool IsHit( const Ray& ray, HitRecord& record ) const override;

    //---------------------------------------------------------------------------------------------
    //! @brief      基本図形かどうかチェックします.
    //---------------------------------------------------------------------------------------------
    bool IsPrimitive() const override;

    //---------------------------------------------------------------------------------------------
    //! @brief      バウンディングボックスを取得します.
    //---------------------------------------------------------------------------------------------
    BoundingBox GetBox() const override;

    //---------------------------------------------------------------------------------------------
    //! @brief      中心座標を取得します.
    //---------------------------------------------------------------------------------------------
    Vector3 GetCenter() const override;

private:
    //=============================================================================================
    // private variables.
    //=============================================================================================
    const IShape*   m_pShape;
    Matrix          m_World;
    Matrix          m_InvWorld;
    BoundingBox     m_WorldBox;
    Vector3         m_WorldCenter;

    //=============================================================================================
    // private methods.
    //=============================================================================================
    /* NOTHING */
};


//////////////////////////////////////////////////////////////////////////////////////
// Sphere structure
//////////////////////////////////////////////////////////////////////////////////////
struct Sphere : public IShape
{
    f32                 radius;         //!< 半径です.
    Vector3             position;       //!< 中心位置です.
    const IMaterial*    pMaterial;      //!< マテリアルです.

    //--------------------------------------------------------------------------------
    //! @brief      コンストラクタです.
    //--------------------------------------------------------------------------------
    Sphere
    (
        const f32,
        const Vector3&,
        const IMaterial*
    );

    //-------------------------------------------------------------------------------
    //! @brief      交差判定します.
    //-------------------------------------------------------------------------------
    bool IsHit(const Ray&, HitRecord& ) const override;

    //-------------------------------------------------------------------------------
    //! @brief      バウンディングボックスを取得します.
    //-------------------------------------------------------------------------------
    BoundingBox GetBox() const override;

    //-------------------------------------------------------------------------------
    //! @brief      基本図形であるかどうか判定します.
    //-------------------------------------------------------------------------------
    bool IsPrimitive() const override;

    //-------------------------------------------------------------------------------
    //! @brief      中心座標を取得します.
    //-------------------------------------------------------------------------------
    Vector3 GetCenter() const override;
};


/////////////////////////////////////////////////////////////////////////////////////
// Vertex structure
/////////////////////////////////////////////////////////////////////////////////////
struct Vertex
{
    Vector3     pos;            //!< 位置座標です.
    Vector2     texcoord;       //!< テクスチャ座標です.
    Vector3     normal;         //!< 法線ベクトルです.

    //------------------------------------------------------------------------------
    //! @brief      コンストラクタです.
    //------------------------------------------------------------------------------
    Vertex()
    { /* DO_NOTHING */ }

    //------------------------------------------------------------------------------
    //! @brief      引数付きコンストラクタです.
    //------------------------------------------------------------------------------
    Vertex( const Vector3& _pos )
    : pos( _pos )
    { /* DO_NOTHING */ }

    //------------------------------------------------------------------------------
    //! @brief      引数付きコンストラクタです.
    //------------------------------------------------------------------------------
    Vertex
    (
        const Vector3& _pos,
        const Vector2& _texcoord
    )
    : pos       ( _pos )
    , texcoord  ( _texcoord )
    { /* DO_NOTHING */ }

    //------------------------------------------------------------------------------
    //! @brief      引数付きコンストラクタです.
    //------------------------------------------------------------------------------
    Vertex
    (
        const Vector3& _pos,
        const Vector2& _texcoord,
        const Vector3& _normal
    )
    : pos       ( _pos )
    , texcoord  ( _texcoord )
    , normal    ( _normal )
    { /* DO_NOTHING */ }

};

///////////////////////////////////////////////////////////////////////////////////
// Face3 structure
///////////////////////////////////////////////////////////////////////////////////
struct Face3
{
    Vertex  v0;         //!< 頂点0です.
    Vertex  v1;         //!< 頂点1です.
    Vertex  v2;         //!< 頂点2です.
    Vector3 normal;     //!< 面の法線ベクトルです.

    //-----------------------------------------------------------------------------
    //! @brief      コンストラクタです.
    //-----------------------------------------------------------------------------
    Face3
    (
        const Vertex& _v0,
        const Vertex& _v1,
        const Vertex& _v2
    )
    : v0( _v0 )
    , v1( _v1 )
    , v2( _v2 )
    {
        // 面の法線ベクトルを求めます.
        normal = Vector3::ComputeNormal( v0.pos, v1.pos, v2.pos );
    }
};

///////////////////////////////////////////////////////////////////////////////////
// Face4 structure
///////////////////////////////////////////////////////////////////////////////////
struct Face4
{
    Vertex  v0;         //!< 頂点0です.
    Vertex  v1;         //!< 頂点1です.
    Vertex  v2;         //!< 頂点2です.
    Vertex  v3;         //!< 頂点3です.
    Vector3 normal;     //!< 面の法線ベクトルです.

    //-----------------------------------------------------------------------------
    //! @brief      コンストラクタです.
    //-----------------------------------------------------------------------------
    Face4
    (
        const Vertex& _v0,
        const Vertex& _v1,
        const Vertex& _v2,
        const Vertex& _v3
    )
    : v0( _v0 )
    , v1( _v1 )
    , v2( _v2 )
    , v3( _v3 )
    {
        // 面の法線ベクトルを求めます.
        normal = Vector3::ComputeQuadNormal( v0.pos, v1.pos, v2.pos, v3.pos );
    }
};

/////////////////////////////////////////////////////////////////////////////////////
// Triangle structure
/////////////////////////////////////////////////////////////////////////////////////
struct Triangle : public IShape
{
    Vertex                v0;           //!< 頂点0です.
    Vertex                v1;           //!< 頂点1です.
    Vertex                v2;           //!< 頂点2です.
    const IMaterial*      pMaterial;    //!< マテリアルです.

    //------------------------------------------------------------------------------
    //! @brief      コンストラクタです.
    //------------------------------------------------------------------------------
    Triangle()
    { /* DO_NOTHING */ }

    //------------------------------------------------------------------------------
    //! @brief      引数付きコンストラクタです.
    //------------------------------------------------------------------------------
    Triangle
    (
        const Vertex&,
        const Vertex&,
        const Vertex&,
        const IMaterial*
    );

    //------------------------------------------------------------------------------
    //! @brief      引数付きコンストラクタです.
    //------------------------------------------------------------------------------
    Triangle
    (
        const Face3&,
        const IMaterial*
    );

    //------------------------------------------------------------------------------
    //! @brief      交差判定を行います.
    //------------------------------------------------------------------------------
    bool IsHit ( const Ray&, HitRecord& ) const override;

    //-------------------------------------------------------------------------------
    //! @brief      バウンディングボックスを取得します.
    //-------------------------------------------------------------------------------
    BoundingBox GetBox() const override;

    //-------------------------------------------------------------------------------
    //! @brief      基本図形であるかどうか判定します.
    //-------------------------------------------------------------------------------
    bool IsPrimitive() const override;

    //-------------------------------------------------------------------------------
    //! @brief      中心座標を取得します.
    //-------------------------------------------------------------------------------
    Vector3 GetCenter() const override;
};


////////////////////////////////////////////////////////////////////////////////////
// Quad structure
////////////////////////////////////////////////////////////////////////////////////
struct Quad : public IShape
{
    Vertex                v0;           //!< 頂点0です.
    Vertex                v1;           //!< 頂点1です.
    Vertex                v2;           //!< 頂点2です.
    Vertex                v3;           //!< 頂点3です.
    const IMaterial*      pMaterial;    //!< マテリアルです.

    //------------------------------------------------------------------------------
    //! @brief      コンストラクタです.
    //------------------------------------------------------------------------------
    Quad
    (
        const Vertex&,
        const Vertex&,
        const Vertex&,
        const Vertex&,
        const IMaterial*
    );

    //------------------------------------------------------------------------------
    //! @brief      引数付きコンストラクタです.
    //------------------------------------------------------------------------------
    Quad
    (
        const Face4&,
        const IMaterial*
    );

    //------------------------------------------------------------------------------
    //! @brief      交差判定を行います.
    //------------------------------------------------------------------------------
    bool IsHit ( const Ray&, HitRecord& ) const override;

    //-------------------------------------------------------------------------------
    //! @brief      バウンディングボックスを取得します.
    //-------------------------------------------------------------------------------
    BoundingBox GetBox() const override;

    //-------------------------------------------------------------------------------
    //! @brief      基本図形であるかどうか判定します.
    //-------------------------------------------------------------------------------
    bool IsPrimitive() const override;

    //-------------------------------------------------------------------------------
    //! @brief      中心座標を取得します.
    //-------------------------------------------------------------------------------
    Vector3 GetCenter() const override;

    //------------------------------------------------------------------------------
    //! @brief      三角形の交差判定を行います.
    //------------------------------------------------------------------------------
    bool IsHitTriangle( 
        const Ray&,
        const Vertex&,
        const Vertex&,
        const Vertex&,
        HitRecord&
    ) const;
};


////////////////////////////////////////////////////////////////////////////////
// Leaf structure
////////////////////////////////////////////////////////////////////////////////
struct Leaf : public IShape, public IDisposable
{
public:
    u32         size;        //!< シェイプの数です.
    IShape**    ppShapes;    //!< シェイプです.
    BoundingBox box;         //!< バウンディングボックスです.

    //--------------------------------------------------------------------------
    //! @brief      コンストラクタです.
    //--------------------------------------------------------------------------
    Leaf();

    //--------------------------------------------------------------------------
    //! @brief      引数付きコンストラクタです.
    //--------------------------------------------------------------------------
    Leaf( u32 _size, IShape** _ppShapes );

    //---------------------------------------------------------------------------
    //! @brief      破棄処理を行います.
    //---------------------------------------------------------------------------
    void Dispose() override;

    //--------------------------------------------------------------------------
    //! @brief      交差判定を行います.
    //--------------------------------------------------------------------------
    bool IsHit( const Ray& ray, HitRecord& record ) const override;

    //--------------------------------------------------------------------------
    //! @brief      バウンディングボックスを取得します.
    //--------------------------------------------------------------------------
    BoundingBox GetBox() const override;

    //--------------------------------------------------------------------------
    //! @brief      基本図形であるか判定します.
    //--------------------------------------------------------------------------
    bool IsPrimitive() const override;

    //--------------------------------------------------------------------------
    //! @brief      中心座標を取得します.
    //--------------------------------------------------------------------------
    Vector3 GetCenter() const override;

    //--------------------------------------------------------------------------
    //! @brief      葉ノードの数を取得します.
    //--------------------------------------------------------------------------
    u32 GetSize() const;
};


BoundingBox CreateMergedBox( s3d::IShape** ppShapes, const u32 numShapes );
BoundingBox CreateMergedBox( s3d::Triangle* pTriangles, const u32 numTriangles );

} // namespace s3d

#endif // __S3D_SHAPE_H__

