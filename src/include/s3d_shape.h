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
#include <s3d_typedef.h>
#include <s3d_math.h>
#include <s3d_box.h>
#include <s3d_texture.h>


namespace s3d {

//-----------------------------------------------------------------------------------
// Forward Declarations.
//-----------------------------------------------------------------------------------
struct IShape;


//-----------------------------------------------------------------------------------
// Constant Values
//-----------------------------------------------------------------------------------
const f64 REFRACTIVITY_WATER   = 1.33;  // 水の屈折率 (1.3)
const f64 REFRACTIVITY_CRYSTAL = 1.54;  // 水晶の屈折率 (1.54).
const f64 REFRACTIVITY_DIAMOND = 2.42;  // ダイアモンドの屈折率 (2.42)


/////////////////////////////////////////////////////////////////////////////////////
// MATERIAL_TYPE enum
/////////////////////////////////////////////////////////////////////////////////////
enum MATERIAL_TYPE
{
    MATERIAL_TYPE_MATTE,    // つやけし.
    MATERIAL_TYPE_MIRROR,   // 鏡.
    MATERIAL_TYPE_CRYSTAL,  // 水晶.
    MATERIAL_TYPE_CLAY,     // 粘土.
    MATERIAL_TYPE_DIAMOND,  // ダイアモンド.
    //MATERIAL_TYPE_PLASTIC,  // プラスチック.
};


/////////////////////////////////////////////////////////////////////////////////////
// HitRecord structure
/////////////////////////////////////////////////////////////////////////////////////
struct HitRecord
{
    f64             distance;       //!< 衝突点までの距離.
    Vector3         position;       //!< 衝突点の位置座標.
    Vector3         normal;         //!< 法線ベクトル.
    Vector2         texcoord;       //!< 衝突点のテクスチャ座標です.
    const IShape*   pShape;         //!< オブジェクトへのポインタ.

    //-------------------------------------------------------------------------------
    //! @brief      コンストラクタです.
    //-------------------------------------------------------------------------------
    HitRecord()
    : distance   ( D_MAX )
    , position   ( 0.0, 0.0, 0.0 )
    , normal     ( 0.0, 0.0, 0.0 )
    , texcoord   ( 0.0, 0.0 )
    , pShape     ( nullptr )
    { /* DO_NOTHING */ }
};


/////////////////////////////////////////////////////////////////////////////////////
// IMaterial interface
/////////////////////////////////////////////////////////////////////////////////////
struct IMaterial
{
    //-------------------------------------------------------------------------------
    //! @brief      マテリアルタイプを取得します.
    //-------------------------------------------------------------------------------
    virtual MATERIAL_TYPE GetType() const = 0;

    //-------------------------------------------------------------------------------
    //! @brief      自己発光カラーを取得します.
    //-------------------------------------------------------------------------------
    virtual Color GetEmissive() const = 0;

    //-------------------------------------------------------------------------------
    //! @brief      マテリアルカラーを取得します.
    //-------------------------------------------------------------------------------
    virtual Color GetColor() const = 0;

    //-------------------------------------------------------------------------------
    //! @brief      テクスチャカラーを取得します.
    //-------------------------------------------------------------------------------
    virtual Color GetTextureColor( const Vector2& ) const = 0;
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
    //! @brief      マテリアルを取得します.
    //-------------------------------------------------------------------------------
    virtual const IMaterial* GetMaterial() const = 0;

    //-------------------------------------------------------------------------------
    //! @brief      バウンディングボックスを取得します.
    //-------------------------------------------------------------------------------
    virtual BoundingBox GetBox() const = 0;

    //-------------------------------------------------------------------------------
    //! @brief      基本図形かどうか判定します.
    //-------------------------------------------------------------------------------
    virtual bool IsPrimitive() const = 0;
};


/////////////////////////////////////////////////////////////////////////////////////
// MaterialBase structure
/////////////////////////////////////////////////////////////////////////////////////
struct MaterialBase : public IMaterial
{
    Color           emissive;       //!< 自己発光カラーです.
    Color           color;          //!< マテリアルカラーです.
    MATERIAL_TYPE   type;           //!< マテリアルタイプです.
    Texture2D       texture;        //!< 2次元テクスチャです.
    TextureSampler  sampler;        //!< テクスチャサンプラーです.

    //---------------------------------------------------------------------------------
    //! @brief      コンストラクタです.
    //---------------------------------------------------------------------------------
    MaterialBase()
    : emissive  ( 0.0, 0.0, 0.0 )
    , color     ( 0.0, 0.0, 0.0 )
    , type      ( MATERIAL_TYPE_MATTE )
    , texture   ()
    , sampler   ()
    { /* DO_NOTHING */ }

    //---------------------------------------------------------------------------------
    //! @brief      引数付きコンストラクタです.
    //---------------------------------------------------------------------------------
    MaterialBase
    (
        const MATERIAL_TYPE _type,
        const Color&        _color    = Color( 0.0, 0.0, 0.0 ),
        const Color&        _emissive = Color( 0.0, 0.0, 0.0 )
    )
    : emissive  ( _emissive )
    , color     ( _color )
    , type      ( _type )
    , texture   ()
    , sampler   ()
    { /* DO_NOTHING */ }

    //---------------------------------------------------------------------------------
    //! @brief      引数付きコンストラクタです.
    //---------------------------------------------------------------------------------
    MaterialBase
    (
        const MATERIAL_TYPE _type, 
        const Color&        _color,
        const Color&        _emissive,
        const char*         _filename,
        const TextureSampler& _sampler = TextureSampler()
    )
    : emissive  ( _emissive )
    , color     ( _color )
    , type      ( _type )
    , texture   ( _filename )
    , sampler   ( _sampler )
    { /* DO_NOTHING */ }

    //--------------------------------------------------------------------------------
    //! @brief      デストラクタです.
    //--------------------------------------------------------------------------------
    virtual ~MaterialBase()
    {
        texture.Release();
    }

    //--------------------------------------------------------------------------------
    //! @brief      マテリアルタイプを取得します.
    //--------------------------------------------------------------------------------
    virtual MATERIAL_TYPE GetType() const
    { return type; }

    //--------------------------------------------------------------------------------
    //! @brief      自己発行カラーを取得します.
    //--------------------------------------------------------------------------------
    virtual Color GetEmissive() const
    { return emissive; }

    //--------------------------------------------------------------------------------
    //! @brief      マテリアルカラーを取得します.
    //--------------------------------------------------------------------------------
    virtual Color GetColor() const
    { return color; }

    //--------------------------------------------------------------------------------
    //! @brief      テクスチャカラーを取得します.
    //--------------------------------------------------------------------------------
    virtual Color GetTextureColor( const Vector2& texcoord ) const
    { return texture.Sample( sampler, texcoord );  }
};


//////////////////////////////////////////////////////////////////////////////////////
// Matte structure
//////////////////////////////////////////////////////////////////////////////////////
struct Matte: public MaterialBase
{
    //--------------------------------------------------------------------------------
    //! @brief      コンストラクタです.
    //--------------------------------------------------------------------------------
    Matte()
    : MaterialBase( MATERIAL_TYPE_MATTE )
    { /* DO_NOTHING */ }

    //--------------------------------------------------------------------------------
    //! @brief      引数付きコンストラクタです.
    //--------------------------------------------------------------------------------
    Matte
    (
        const Color& _color,
        const Color& _emissive = Color( 0.0, 0.0, 0.0 )
    )
    : MaterialBase( MATERIAL_TYPE_MATTE, _color, _emissive )
    { /* DO_NOTHING */ }

    //--------------------------------------------------------------------------------
    //! @brief      引数付きコンストラクタです.
    //--------------------------------------------------------------------------------
    Matte
    (
        const Color&         _color,
        const char*          _filename,
        const TextureSampler _sampler = TextureSampler(),
        const Color&         _emissive = Color( 0.0, 0.0, 0.0 )
    )
    : MaterialBase( MATERIAL_TYPE_MATTE, _color, _emissive, _filename, _sampler )
    { /* DO_NOTHING */ }
};



//////////////////////////////////////////////////////////////////////////////////////
// Clay structure
//////////////////////////////////////////////////////////////////////////////////////
struct Clay : public MaterialBase
{
    f64 roughness;      //!< 面の粗さです.

    //--------------------------------------------------------------------------------
    //! @brief      コンストラクタです.
    //--------------------------------------------------------------------------------
    Clay()
    : MaterialBase( MATERIAL_TYPE_CLAY )
    , roughness( 0.0 )
    { /* DO_NOTHING */ }

    //--------------------------------------------------------------------------------
    //! @brief      引数付きコンストラクタです.
    //--------------------------------------------------------------------------------
    Clay
    (
        const Color& _color,
        const f64    _roughness,
        const Color& _emissive = Color( 0.0, 0.0, 0.0 )
    )
    : MaterialBase( MATERIAL_TYPE_CLAY, _color, _emissive )
    , roughness( _roughness )
    { /* DO_NOTHING */ }

    //--------------------------------------------------------------------------------
    //! @brief      引数付きコンストラクタです.
    //--------------------------------------------------------------------------------
    Clay
    (
        const Color&        _color,
        const f64           _roughness,
        const char*         _filename,
        const Color&        _emissive  = Color( 0.0, 0.0, 0.0 ),
        const TextureSampler& _sampler = TextureSampler()
    )
    : MaterialBase( MATERIAL_TYPE_CLAY, _color, _emissive, _filename, _sampler )
    , roughness( _roughness )
    { /* DO_NOTHING */ }

    //--------------------------------------------------------------------------------
    //! @brief
    //--------------------------------------------------------------------------------
    virtual f64 GetRoughness() const
    { return roughness; }
};



//////////////////////////////////////////////////////////////////////////////////////
// Mirror structure
//////////////////////////////////////////////////////////////////////////////////////
struct Mirror : public MaterialBase
{
    //--------------------------------------------------------------------------------
    //! @brief      コンストラクタです.
    //--------------------------------------------------------------------------------
    Mirror()
    : MaterialBase( MATERIAL_TYPE_MIRROR )
    { /* DO_NOTHING */ }

    //--------------------------------------------------------------------------------
    //! @brief      引数付きコンストラクタです.
    //--------------------------------------------------------------------------------
    Mirror
    (
        const Color& _color,
        const Color& _emissive = Color( 0.0, 0.0, 0.0 )
    )
    : MaterialBase( MATERIAL_TYPE_MIRROR, _color, _emissive )
    { /* DO_NOTHING */ }

    //--------------------------------------------------------------------------------
    //! @brief      引数付きコンストラクタです.
    //--------------------------------------------------------------------------------
    Mirror
    (
        const Color&         _color,
        const char*          _filename,
        const TextureSampler _sampler = TextureSampler(),
        const Color&         _emissive = Color( 0.0, 0.0, 0.0 )
    )
    : MaterialBase( MATERIAL_TYPE_MATTE, _color, _emissive, _filename, _sampler )
    { /* DO_NOTHING */ }
};


//////////////////////////////////////////////////////////////////////////////////////
// RefractionMaterial structure
//////////////////////////////////////////////////////////////////////////////////////
struct RefractionMaterial : public MaterialBase
{
    f64     refractivity;       //!< 屈折率です.

    //--------------------------------------------------------------------------------
    //! @brief      コンストラクタです.
    //--------------------------------------------------------------------------------
    RefractionMaterial
    ( 
        const MATERIAL_TYPE _type,
        const f64           _refractivity
    )
    : MaterialBase( _type )
    , refractivity( _refractivity )
    { /* DO_NOTHING */ }

    //--------------------------------------------------------------------------------
    //! @brief      引数付きコンストラクタです.
    //--------------------------------------------------------------------------------
    RefractionMaterial
    (
        const MATERIAL_TYPE _type,
        const Color&        _color    = Color( 0.0, 0.0, 0.0 ),
        const Color&        _emissive = Color( 0.0, 0.0, 0.0 ),
        const f64           _refraction = 1.0
    )
    : MaterialBase( _type, _color, _emissive )
    , refractivity( _refraction )
    { /* DO_NOTHING */ }

    //--------------------------------------------------------------------------------
    //! @brief      引数付きコンストラクタです.
    //--------------------------------------------------------------------------------
    RefractionMaterial
    (
        const MATERIAL_TYPE _type, 
        const Color&        _color,
        const Color&        _emissive,
        const f64           _refraction,
        const char*         _filename,
        const TextureSampler& _sampler = TextureSampler()
    )
    : MaterialBase( _type, _color, _emissive, _filename, _sampler )
    , refractivity( _refraction )
    { /* DO_NOTHING */ }

    //--------------------------------------------------------------------------------
    //! @brief      屈折率を取得します.
    //--------------------------------------------------------------------------------
    virtual f64 GetRefractivity() const
    { return refractivity; }
};


//////////////////////////////////////////////////////////////////////////////////////
// Crystal structure
//////////////////////////////////////////////////////////////////////////////////////
struct Crystal : public RefractionMaterial
{
    //--------------------------------------------------------------------------------
    //! @brief      コンストラクタです.
    //--------------------------------------------------------------------------------
    Crystal()
    : RefractionMaterial( MATERIAL_TYPE_CRYSTAL, REFRACTIVITY_CRYSTAL )
    { /* DO_NOTHING */ }

    //--------------------------------------------------------------------------------
    //! @brief      引数付きコンストラクタです.
    //--------------------------------------------------------------------------------
    Crystal
    (
        const Color& _color,
        const Color& _emissive = Color( 0.0, 0.0, 0.0 )
    )
    : RefractionMaterial( MATERIAL_TYPE_CRYSTAL, _color, _emissive, REFRACTIVITY_CRYSTAL )
    { /* DO_NOTHING */ }

    //--------------------------------------------------------------------------------
    //! @brief      引数付きコンストラクタです.
    //--------------------------------------------------------------------------------
    Crystal
    (
        const Color&         _color,
        const char*          _filename,
        const TextureSampler _sampler = TextureSampler(),
        const Color&         _emissive = Color( 0.0, 0.0, 0.0 )
    )
    : RefractionMaterial( MATERIAL_TYPE_CRYSTAL, _color, _emissive, REFRACTIVITY_CRYSTAL, _filename, _sampler )
    { /* DO_NOTHING */ }
};


//////////////////////////////////////////////////////////////////////////////////////
// Diamon structure
//////////////////////////////////////////////////////////////////////////////////////
struct Diamond : public RefractionMaterial
{
    //--------------------------------------------------------------------------------
    //! @brief      コンストラクタです.
    //--------------------------------------------------------------------------------
    Diamond()
    : RefractionMaterial( MATERIAL_TYPE_DIAMOND, REFRACTIVITY_DIAMOND )
    { /* DO_NOTHING */ }

    //--------------------------------------------------------------------------------
    //! @brief      引数付きコンストラクタです.
    //--------------------------------------------------------------------------------
    Diamond
    (
        const Color& _color,
        const Color& _emissive = Color( 0.0, 0.0, 0.0 )
    )
    : RefractionMaterial( MATERIAL_TYPE_DIAMOND, _color, _emissive, REFRACTIVITY_DIAMOND )
    { /* DO_NOTHING */ }

    //--------------------------------------------------------------------------------
    //! @brief      引数付きコンストラクタです.
    //--------------------------------------------------------------------------------
    Diamond
    (
        const Color&         _color,
        const char*          _filename,
        const TextureSampler _sampler = TextureSampler(),
        const Color&         _emissive = Color( 0.0, 0.0, 0.0 )
    )
    : RefractionMaterial( MATERIAL_TYPE_DIAMOND, _color, _emissive, REFRACTIVITY_DIAMOND, _filename, _sampler )
    { /* DO_NOTHING */ }
};

#if 0
////////////////////////////////////////////////////////////////////////////////////////
//// PlasticMaterial structure
////////////////////////////////////////////////////////////////////////////////////////
//struct PlasticMaterial : public MaterialBase
//{
//    f64     power;      //!< 鏡面反射強度です.
//
//    //--------------------------------------------------------------------------------
//    //! @brief
//    //--------------------------------------------------------------------------------
//    PlasticMaterial()
//    : MaterialBase( MATERIAL_TYPE_PLASTIC )
//    , power       ( 0.0 )
//    {
//    }
//
//    //--------------------------------------------------------------------------------
//    //! @brief
//    //--------------------------------------------------------------------------------
//    PlasticMaterial
//    (
//        const Color& _color,
//        const f64    _power,
//        const Color& _emissive
//    )
//    : MaterialBase( MATERIAL_TYPE_PLASTIC, _color, _emissive )
//    , power( _power )
//    {
//    }
//
//    //--------------------------------------------------------------------------------
//    //! @brief
//    //--------------------------------------------------------------------------------
//    PlasticMaterial
//    (
//        const Color&        _color,
//        const f64           _power,
//        const char*         _filename,
//        const Color&        _emissive  = Color( 0.0, 0.0, 0.0 ),
//        const TextureSampler& _sampler = TextureSampler()
//    )
//    : MaterialBase( MATERIAL_TYPE_CLAY, _color, _emissive, _filename, _sampler )
//    , power( _power )
//    {
//    }
//
//    //--------------------------------------------------------------------------------
//    //! @brief
//    //--------------------------------------------------------------------------------
//    virtual f64 GetPower() const
//    { return power; }
//};
#endif


//////////////////////////////////////////////////////////////////////////////////////
// Sphere structure
//////////////////////////////////////////////////////////////////////////////////////
struct Sphere : public IShape
{
    f64                 radius;         //!< 半径です.
    Vector3             position;       //!< 中心位置です.
    const IMaterial*    pMaterial;      //!< マテリアルです.

    //--------------------------------------------------------------------------------
    //! @brief      コンストラクタです.
    //--------------------------------------------------------------------------------
    Sphere
    (
        const f64,
        const Vector3&,
        const IMaterial*
    );

    //-------------------------------------------------------------------------------
    //! @brief      交差判定します.
    //-------------------------------------------------------------------------------
    bool IsHit(const Ray&, HitRecord& ) const;

    //-------------------------------------------------------------------------------
    //! @brief      マテリアルを取得します.
    //-------------------------------------------------------------------------------
    const IMaterial* GetMaterial() const;

    //-------------------------------------------------------------------------------
    //! @brief      バウンディングボックスを取得します.
    //-------------------------------------------------------------------------------
    BoundingBox GetBox() const;

    //-------------------------------------------------------------------------------
    //! @brief      基本図形であるかどうか判定します.
    //-------------------------------------------------------------------------------
    bool IsPrimitive() const;
};


/////////////////////////////////////////////////////////////////////////////////////
// Triangle structure
/////////////////////////////////////////////////////////////////////////////////////
struct Triangle : public IShape
{
    Vector3         p0;         //!< 頂点座標0
    Vector3         p1;         //!< 頂点座標1
    Vector3         p2;         //!< 頂点座標2
    Vector3         normal;     //!< 法線ベクトル.
    Vector2         uv0;        //!< テクスチャ座標0
    Vector2         uv1;        //!< テクスチャ座標1
    Vector2         uv2;        //!< テクスチャ座標2
    const IMaterial*      pMaterial;  //!< マテリアルを取得します.

    //------------------------------------------------------------------------------
    //! @brief      コンストラクタです.
    //------------------------------------------------------------------------------
    Triangle
    (
        const Vector3&,
        const Vector3&,
        const Vector3&,
        const IMaterial*,
        const Vector2& = Vector2( 0.0, 0.0 ),
        const Vector2& = Vector2( 0.0, 0.0 ),
        const Vector2& = Vector2( 0.0, 0.0 )
    );

    //------------------------------------------------------------------------------
    //! @brief      交差判定を行います.
    //------------------------------------------------------------------------------
    bool IsHit ( const Ray&, HitRecord& ) const;

    //-------------------------------------------------------------------------------
    //! @brief      マテリアルを取得します.
    //-------------------------------------------------------------------------------
    const IMaterial* GetMaterial() const;

    //-------------------------------------------------------------------------------
    //! @brief      バウンディングボックスを取得します.
    //-------------------------------------------------------------------------------
    BoundingBox GetBox() const;

    //-------------------------------------------------------------------------------
    //! @brief      基本図形であるかどうか判定します.
    //-------------------------------------------------------------------------------
    bool IsPrimitive() const;
};


////////////////////////////////////////////////////////////////////////////////////
// Quad structure
////////////////////////////////////////////////////////////////////////////////////
struct Quad : public IShape
{
    Vector3         p0;         //!< 頂点座標0です.
    Vector3         p1;         //!< 頂点座標1です.
    Vector3         p2;         //!< 頂点座標2です.
    Vector3         p3;         //!< 頂点座標3です.
    Vector3         normal;     //!< 法線ベクトルです.
    Vector2         uv0;        //!< テクスチャ座標0です.
    Vector2         uv1;        //!< テクスチャ座標1です.
    Vector2         uv2;        //!< テクスチャ座標2です.
    Vector2         uv3;        //!< テクスチャ座標3です.
    const IMaterial*      pMaterial;  //!< マテリアルです.

    //------------------------------------------------------------------------------
    //! @brief      コンストラクタです.
    //------------------------------------------------------------------------------
    Quad
    (
        const Vector3&,
        const Vector3&,
        const Vector3&,
        const Vector3&,
        const IMaterial*,
        const Vector2& = Vector2( 0.0, 0.0 ),
        const Vector2& = Vector2( 0.0, 0.0 ),
        const Vector2& = Vector2( 0.0, 0.0 ),
        const Vector2& = Vector2( 0.0, 0.0 )
    );

    //------------------------------------------------------------------------------
    //! @brief      交差判定を行います.
    //------------------------------------------------------------------------------
    bool IsHit ( const Ray&, HitRecord& ) const;

    //-------------------------------------------------------------------------------
    //! @brief      マテリアルを取得します.
    //-------------------------------------------------------------------------------
    const IMaterial* GetMaterial() const;

    //-------------------------------------------------------------------------------
    //! @brief      バウンディングボックスを取得します.
    //-------------------------------------------------------------------------------
    BoundingBox GetBox() const;

    //-------------------------------------------------------------------------------
    //! @brief      基本図形であるかどうか判定します.
    //-------------------------------------------------------------------------------
    bool IsPrimitive() const;

    //------------------------------------------------------------------------------
    //! @brief      三角形の交差判定を行います.
    //------------------------------------------------------------------------------
    bool IsHitTriangle( 
        const Ray&,
        const Vector3&,
        const Vector3&,
        const Vector3&,
        const Vector2&,
        const Vector2&,
        const Vector2&,
       HitRecord&
    ) const;
};

} // namespace s3d

#endif // __S3D_SHAPE_H__

