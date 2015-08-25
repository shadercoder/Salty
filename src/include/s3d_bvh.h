﻿//---------------------------------------------------------------------------
// File : s3d_bvh.h
// Desc : Bounding Volume Hierarchy Module.
// Copyright(c) Project Asura. All right reserved.
//---------------------------------------------------------------------------

#ifndef __S3D_BVH_H__
#define __S3D_BVH_H__

//----------------------------------------------------------------------------
// Includes
//----------------------------------------------------------------------------
#include <s3d_math.h>
#include <s3d_shape.h>
#include <vector>
#include <array>


namespace s3d {

//////////////////////////////////////////////////////////////////////////////
// BVH structure
//////////////////////////////////////////////////////////////////////////////
struct BVH : public IShape, public IDisposable
{
public:
    BoundingBox box;                    //!< バウンディングボックスです.
    IShape*     pShape[2];              //!< 子供.

    //-------------------------------------------------------------------------
    //! @brief      コンストラクタです.
    //-------------------------------------------------------------------------
    BVH();

    //-------------------------------------------------------------------------
    //! @brief        破棄処理を行います.
    //-------------------------------------------------------------------------
    void Dispose();

    //-------------------------------------------------------------------------
    //! @brief      交差判定を行います.
    //-------------------------------------------------------------------------
    bool IsHit( const Ray&, HitRecord& ) const;

    //-------------------------------------------------------------------------
    //! @brief      マテリアルを取得します.
    //-------------------------------------------------------------------------
    IMaterial* GetMaterial() const;

    //-------------------------------------------------------------------------
    //! @brief      バウンディングボックスを取得します.
    //-------------------------------------------------------------------------
    BoundingBox GetBox() const;

    //-------------------------------------------------------------------------
    //! @brief      基本図形であるか判定します.
    //-------------------------------------------------------------------------
    bool IsPrimitive() const;

    //-------------------------------------------------------------------------
    //! @brief      中心座標を取得します.
    //-------------------------------------------------------------------------
    Vector3 GetCenter() const;

    //-------------------------------------------------------------------------
    //! @brief      ブランチを構築します.
    //-------------------------------------------------------------------------
    static IShape* BuildBranch( IShape**, const u32 );

    //-------------------------------------------------------------------------
    //! @brief      ブランチを構築します.
    //-------------------------------------------------------------------------
    static IShape* Build(std::vector<IShape*>& shapes);

private:
    //-------------------------------------------------------------------------
    //! @brief      引数付きコンストラクタです.
    //-------------------------------------------------------------------------
    BVH( IShape*, IShape* );

    //-------------------------------------------------------------------------
    //! @brief      引数付きコンストラクタです.
    //-------------------------------------------------------------------------
    BVH( IShape*, IShape*, const BoundingBox& );
};


////////////////////////////////////////////////////////////////////////////////
// QBVH structure
////////////////////////////////////////////////////////////////////////////////
struct QBVH : public IShape, public IDisposable
{
public:
    IShape*         pShape[4];          //!< 子ノードです.
    BoundingBox4    box;                //!< 子ノードのバウンディングボックスです.
    s32             axisTop;
    s32             axisLeft;
    s32             axisRight;

    //--------------------------------------------------------------------------
    //! @brief      コンストラクタです.
    //--------------------------------------------------------------------------
    QBVH();

    //--------------------------------------------------------------------------
    //! @brief      破棄処理を行います.
    //--------------------------------------------------------------------------
    void Dispose();

    //--------------------------------------------------------------------------
    //! @brief      交差判定を行います.
    //--------------------------------------------------------------------------
    bool IsHit(const Ray&, HitRecord&) const;

    //--------------------------------------------------------------------------
    //! @brief      マテリアルを取得します.
    //--------------------------------------------------------------------------
    IMaterial* GetMaterial() const;

    //--------------------------------------------------------------------------
    //! @brief      バウンディングボックスを取得します.
    //--------------------------------------------------------------------------
    BoundingBox GetBox() const;

    //--------------------------------------------------------------------------
    //! @brief      基本図形かどうか判定します.
    //--------------------------------------------------------------------------
    bool IsPrimitive() const;

    //-------------------------------------------------------------------------
    //! @brief      中心座標を取得します.
    //-------------------------------------------------------------------------
    Vector3 GetCenter() const;

    //--------------------------------------------------------------------------
    //! @brief      ブランチを構築します.
    //--------------------------------------------------------------------------
    static IShape* BuildBranch(IShape**, const u32);

    static IShape* Build(std::vector<IShape*>& shapes);

private:

    QBVH( IShape* shape0, IShape* shape1, IShape* shape2, IShape* shape3, s32 top, s32 left, s32 right);

    //--------------------------------------------------------------------------
    //! @brief      引数付きコンストラクタです
    //--------------------------------------------------------------------------
    QBVH( IShape** ppShapes, const BoundingBox4& box, s32 top, s32 left, s32 right );
};


////////////////////////////////////////////////////////////////////////////////
// OBVH structure
////////////////////////////////////////////////////////////////////////////////
struct OBVH : public IShape, public IDisposable
{
public:
    IShape*         pShape[8];          //!< 子ノードです.
    BoundingBox8    box;                //!< 子ノードのバウンディングボックスです.
    s32             axisTop;
    s32             axisL;
    s32             axisR;
    s32             axisA;
    s32             axisB;
    s32             axisC;
    s32             axisD;

    //--------------------------------------------------------------------------
    //! @brief      コンストラクタです.
    //--------------------------------------------------------------------------
    OBVH();

    //--------------------------------------------------------------------------
    //! @brief      破棄処理を行います.
    //--------------------------------------------------------------------------
    void Dispose();

    //--------------------------------------------------------------------------
    //! @brief      交差判定を行います.
    //--------------------------------------------------------------------------
    bool IsHit(const Ray&, HitRecord&) const;

    //--------------------------------------------------------------------------
    //! @brief      マテリアルを取得します.
    //--------------------------------------------------------------------------
    IMaterial* GetMaterial() const;

    //--------------------------------------------------------------------------
    //! @brief      バウンディングボックスを取得します.
    //--------------------------------------------------------------------------
    BoundingBox GetBox() const;

    //--------------------------------------------------------------------------
    //! @brief      基本図形かどうか判定します.
    //--------------------------------------------------------------------------
    bool IsPrimitive() const;

    //-------------------------------------------------------------------------
    //! @brief      中心座標を取得します.
    //-------------------------------------------------------------------------
    Vector3 GetCenter() const;

    //--------------------------------------------------------------------------
    //! @brief      ブランチを構築します.
    //--------------------------------------------------------------------------
    static IShape* BuildBranch(IShape**, const u32);

    //--------------------------------------------------------------------------
    //! @brief      ブランチを構築します.
    //--------------------------------------------------------------------------
    static IShape* Build(std::vector<IShape*>& shapes);

private:
    //--------------------------------------------------------------------------
    //! @brief      引数付きコンストラクタです.
    //--------------------------------------------------------------------------
    OBVH( IShape** ppShapes );

    //--------------------------------------------------------------------------
    //! @brief      引数付きコンストラクタです.
    //--------------------------------------------------------------------------
    OBVH( 
        IShape* shape0,
        IShape* shape1,
        IShape* shape2,
        IShape* shape3,
        IShape* shape4,
        IShape* shape5,
        IShape* shape6,
        IShape* shape7,
        s32 top,
        s32 left,
        s32 right,
        s32 a,
        s32 b,
        s32 c,
        s32 d);

    //--------------------------------------------------------------------------
    //! @brief      引数付きコンストラクタです
    //--------------------------------------------------------------------------
    OBVH( IShape** ppShapes, const BoundingBox8& octBox );
};

} // namespace s3d

#endif//__S3D_BVH_H__
