﻿//-------------------------------------------------------------------------------------------------
// File : s3d_bvh2.h
// Desc : Binary BVH Modle.
// Copyright(c) Project Asura. All right reserved.
//-------------------------------------------------------------------------------------------------
#pragma once

//-------------------------------------------------------------------------------------------------
// Includes
//-------------------------------------------------------------------------------------------------
#include <s3d_math.h>
#include <s3d_shape.h>
#include <atomic>


namespace s3d {

///////////////////////////////////////////////////////////////////////////////////////////////////
// BVH2 class
///////////////////////////////////////////////////////////////////////////////////////////////////
class BVH2 : IShape
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
    //! @brief      BVHを構築します.
    //---------------------------------------------------------------------------------------------
    static IShape* Create( size_t count, IShape** ppShapes );

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
    //! @brief      交差判定を行います.
    //---------------------------------------------------------------------------------------------
    bool IsHit(const Ray& ray, HitRecord& record ) const override;

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
    std::atomic<u32>    m_Count;        //!< 参照カウントです.
    BoundingBox         m_Box;          //!< バウンディングボックスです.
    IShape*             m_pNode[2];     //!< 子ノードです.

    //=============================================================================================
    // private methods.
    //=============================================================================================

    //---------------------------------------------------------------------------------------------
    //! @brief      コンストラクタです.
    //---------------------------------------------------------------------------------------------
    BVH2( IShape* pShape0, IShape* pShape1, const BoundingBox& box );

    //---------------------------------------------------------------------------------------------
    //! @brief      デストラクタです.
    //---------------------------------------------------------------------------------------------
    ~BVH2();
};

} // namespace s3d
