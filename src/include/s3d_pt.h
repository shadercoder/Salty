﻿//-------------------------------------------------------------------------------------------------
// File : s3d_pt.h
// Desc : Path Tracer Module.
// Copyright(c) Project Asura. All right reserved.
//-------------------------------------------------------------------------------------------------
#pragma once

//-------------------------------------------------------------------------------------------------
// Includes
//-------------------------------------------------------------------------------------------------
#include <s3d_math.h>
#include <s3d_scene.h>


namespace s3d {

///////////////////////////////////////////////////////////////////////////////////////////////////
// PathTracer class
///////////////////////////////////////////////////////////////////////////////////////////////////
class PathTracer
{
    //=============================================================================================
    // list of friend classes and methods.
    //=============================================================================================
    /* NOTHING */

public:
    ///////////////////////////////////////////////////////////////////////////////////////////////
    // Config structure
    ///////////////////////////////////////////////////////////////////////////////////////////////
    struct Config
    {
        s32     Width;              //!< レンダーターゲットの横幅です.
        s32     Height;             //!< レンダーターゲットの縦幅です.
        s32     SampleCount;        //!< 1ピクセルあたりのサンプリング数です.
        s32     SubSampleCount;     //!< 1ピクセルあたりのサブサンプリング数です.
        s32     MaxBounceCount;     //!< 打ち切りバウンス数です.
    };

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
    PathTracer();

    //---------------------------------------------------------------------------------------------
    //! @brief      デストラクタです.
    //---------------------------------------------------------------------------------------------
    virtual ~PathTracer();

    //---------------------------------------------------------------------------------------------
    //! @brief      レンダリングを実行します.
    //---------------------------------------------------------------------------------------------
    bool Run( const Config& config );

private:
    //=============================================================================================
    // private variables.
    //=============================================================================================
    Config          m_Config;           //!< コンフィグです.
    Color4*         m_RenderTarget;     //!< レンダーターゲットです.
    Color4*         m_Intermediate;     //!< 中間出力用ターゲット.
    Random          m_Random;           //!< 乱数.
    Scene*          m_pScene;           //!< シーンデータ.
    volatile bool   m_IsFinish;         //!< 正常終了したかどうか？
    volatile bool   m_WatcherEnd;       //!< 時間監視を終了したかどうか.

    //=============================================================================================
    // private methods.
    //=============================================================================================

    //---------------------------------------------------------------------------------------------
    //! @brief      指定方向からの放射輝度を求めます.
    //---------------------------------------------------------------------------------------------
    Color4 Radiance( const Ray& input );

    //---------------------------------------------------------------------------------------------
    //! @brief      経路を追跡します.
    //---------------------------------------------------------------------------------------------
    void  TracePath();

    //---------------------------------------------------------------------------------------------
    //! @brief      レンダリング時間を監視します.
    //---------------------------------------------------------------------------------------------
    void  Watcher();

    //---------------------------------------------------------------------------------------------
    //! @brief      レンダリング結果をキャプチャーします.
    //---------------------------------------------------------------------------------------------
    void  Capture( const char* filename );

    PathTracer      ( const PathTracer& ) = delete;     // アクセス禁止.
    void operator = ( const PathTracer& ) = delete;     // アクセス禁止.

};

} // namespace s3d
