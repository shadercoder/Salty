﻿//-------------------------------------------------------------------------------------------------
// File : s3d_leaf.h
// Desc : Leaf Node Module.
// Copyright(c) Project Asura. All right reserved.
//-------------------------------------------------------------------------------------------------
#pragma once

//-------------------------------------------------------------------------------------------------
// Includes
//-------------------------------------------------------------------------------------------------
#include <s3d_shape.h>
#include <atomic>
#include <vector>


namespace s3d {

///////////////////////////////////////////////////////////////////////////////////////////////////
// Leaf class
///////////////////////////////////////////////////////////////////////////////////////////////////
class Leaf : IShape
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
    static bool Create(u32 shapeCount, IShape** ppShape, IShape** ppResult);

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
    bool IsHit(const Ray& ray, HitRecord& record) const override;

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
    std::atomic<u32>        m_Count;
    std::vector<IShape*>    m_pShapes;
    BoundingBox             m_Box;

    //=============================================================================================
    // private methods.
    //=============================================================================================

    //---------------------------------------------------------------------------------------------
    //! @brief      コンストラクタです.
    //---------------------------------------------------------------------------------------------
    Leaf(u32 count, IShape** ppShapes);

    //---------------------------------------------------------------------------------------------
    //! @brief      デストラクタです.
    //---------------------------------------------------------------------------------------------
    ~Leaf();
};

} // namespace s3d