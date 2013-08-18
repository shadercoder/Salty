﻿//--------------------------------------------------------------------------------------
// File : s3d_camera.h
// Desc : Camera Module.
// Copyright(c) Project Asura. All right reserved.
//--------------------------------------------------------------------------------------

#ifndef __S3D_CAMERA_H__
#define __S3D_CAMERA_H__


//--------------------------------------------------------------------------------------
// Includes
//--------------------------------------------------------------------------------------
#include <s3d_math.h>


namespace s3d {

////////////////////////////////////////////////////////////////////////////////////////
// Camera class
////////////////////////////////////////////////////////////////////////////////////////
class Camera
{
    //==================================================================================
    // list of friend classes and methods.
    //==================================================================================
    /* NOTHING */

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
    Camera()
    { /* DO_NOTHING */ }

    //----------------------------------------------------------------------------------
    //! @brief      デストラクタです.
    //----------------------------------------------------------------------------------
    virtual ~Camera()
    { /* DO_NOTHING */ }

    //----------------------------------------------------------------------------------
    //! @brief      更新処理を行います.
    //----------------------------------------------------------------------------------
    void Update
    (
        const Vector3 position,
        const Vector3 target,
        const Vector3 upward,
        const s32     width,
        const s32     height,
        const f64     fov,
        const f64     nearClip
    )
    {
        m_Position  = position;
        m_Target    = target;
        m_Upward    = upward;

        m_Width    = width;
        m_Height   = height;
        m_Fov      = fov;
        m_NearClip = nearClip;


        // 視線ベクトルを求める.
        m_Direction = Vector3::UnitVector( m_Target - m_Position );

        // スクリーンを張るベクトル.
        m_CX = Vector3::UnitVector( Vector3::Cross( m_Upward, m_Direction ) ) * m_Fov * m_Width / m_Height;
        m_CY = Vector3::UnitVector( Vector3::Cross( m_CX, m_Direction ) ) * m_Fov;

        // スクリーンの中心へのベクトル.
        m_CZ = m_Position + ( m_Direction * m_NearClip );
    }

    //----------------------------------------------------------------------------------
    //! @brief      レイを取得します.
    //----------------------------------------------------------------------------------
    S3D_INLINE
    Ray GetRay( const f64 x, const f64 y )
    {
        Vector3 pos = ( m_CX * x ) + ( m_CY * y ) + m_CZ;
        Vector3 dir = Vector3::UnitVector( pos - m_Position );
        return Ray( m_Position, dir );
    }

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
    Vector3 m_Position;     //!< カメラ位置です.
    Vector3 m_Target;       //!< カメラの注視点です.
    Vector3 m_Upward;       //!< カメラの上向きベクトルです.
    Vector3 m_Direction;    //!< カメラの視線ベクトルです.

    f64 m_Width;            //!< スクリーンの横幅です.
    f64 m_Height;           //!< スクリーンの縦幅です.
    f64 m_Fov;              //!< 垂直画角です.
    f64 m_NearClip;         //!< スクリーンまでの距離です.

    Vector3 m_CX;           //!< スクリーンX方向を構成するベクトルです.
    Vector3 m_CY;           //!< スクリーンY方向を構成するベクトルです.
    Vector3 m_CZ;           //!< カメラ位置とスクリーン中心を結ぶベクトルです.

    //==================================================================================
    // private methods.
    //==================================================================================
    /* NOTHING */
};


} // namespace s3d

#endif // __S3D_CAMERA_H__
