﻿//---------------------------------------------------------------------------------
// File : s3d_app.cpp
// Desc : Application Module.
// Copyright(c) Project Asura. All right reserved.
//----------------------------------------------------------------------------------

//----------------------------------------------------------------------------------
// Includes
//----------------------------------------------------------------------------------
#include <s3d_app.h>
#include <s3d_bmp.h>
#include <s3d_math.h>
#include <s3d_rand.h>
#include <s3d_camera.h>
#include <s3d_shape.h>
#include <s3d_material.h>
#include <s3d_timer.h>
#include <s3d_mutex.h>
#include <s3d_onb.h>
#include <s3d_bvh.h>

#include <iostream>
#include <direct.h>
#include <ctime>
#include <process.h>


namespace s3d {

//----------------------------------------------------------------------------------
// Macro
//----------------------------------------------------------------------------------

// デバッグログ.
#ifndef DLOG
    #if defined(DEBUG) || defined(_DEBUG)
        #define DLOG( x, ... ) printf_s( "[File: %s, Line: %d] "x"\n", __FILE__, __LINE__, ##__VA_ARGS__ )
    #else
        #define DLOG( x, ... )
    #endif
#endif//DLOG

// 情報ログ.
#ifndef ILOG
#define ILOG( x, ... ) printf_s( x"\n", ##__VA_ARGS__ )
#endif//ILOG

// エラーログ.
#ifndef ELOG
#define ELOG( x, ... ) fprintf_s( stderr, "[File: %s, Line: %d] "x"\n", __FILE__, __LINE__, ##__VA_ARGS__ )
#endif//ELOG


//----------------------------------------------------------------------------------
// Forward Declarations.
//----------------------------------------------------------------------------------
void TimeWatch( void* );


//----------------------------------------------------------------------------------
// Constant Values
//----------------------------------------------------------------------------------
static const s32 MAX_DEPTH = 32;        //!< 打ち切り深度.


//----------------------------------------------------------------------------------
// Global Varaibles.
//----------------------------------------------------------------------------------
bool    g_WatcherEnd    = false;        //!< ウォッチーの終了フラグ.
bool    g_IsFinished    = false;        //!< レイトレ終了フラグ.
u32     g_Width         = 0;            //!< 画像の横幅.
u32     g_Height        = 0;            //!< 画像の縦幅.
u32     g_NumSample     = 0;            //!< サンプル数.
u32     g_NumSubSample  = 0;            //!< サブサンプル数.
Color*  g_pRT           = nullptr;      //!< レンダーターゲット.
Mutex   g_Mutex;                        //!< ミューテックス.

// Lambert
Matte g_Matte[] = {
    Matte( Color( 0.75, 0.75, 0.75 ), "./res/texture/wall.bmp" ),
    Matte( Color( 0.75, 0.75, 0.75 ), "./res/texture/tile.bmp" ),
    Matte( Color( 0.0, 0.0, 0.0 ), Color( 36.0, 36.0, 36.0 ) ),
};

// Oren-Nayer
Clay g_Clay[] = {
    Clay( Color( 0.25, 0.75, 0.25 ), 0.85 ),
};

// Mirror
Mirror g_Mirror[] = {
    Mirror( Color( 0.25, 0.25, 0.75 ) ),
    Mirror( Color( 0.75, 0.75, 0.25 ) ),
};

// Refraction (Crystal)
Crystal g_Crystal[] = {
    Crystal( Color( 0.75, 0.25, 0.25 ) ),
};

// Refraction (Diamond)
Diamond g_Diamond[] = {
    Diamond( Color( 1.0, 1.0, 1.0 ) ),
};

// Materials
IMaterial* g_pMaterials[] = {
    &g_Matte[0],        // 0 : 白.
    &g_Matte[1],        // 1 : タイル.
    &g_Matte[2],        // 2 : 照明.
    &g_Mirror[0],       // 3 : ミラー.
    &g_Mirror[1],       // 4 : 黄色ミラー.
    &g_Crystal[0],      // 5 : 水晶.
    &g_Clay[0],         // 6 : 粘土.

};

// レンダリングするシーンデータ
Sphere g_Spheres[] = {
    Sphere( 16.5,  Vector3( 20.0, 16.5,  27.0 ), g_pMaterials[3] ),    // 鏡
    Sphere( 16.5,  Vector3( 77.0, 16.5,  78.0 ), g_pMaterials[5] ),    // 水晶.
    Sphere( 15.0,  Vector3( 50.0, 100.0, 81.6 ), g_pMaterials[2] ),    // 照明
};

// トライアングル.
Triangle g_Triangles[] = {

    // 上.
    Triangle( 
        Vector3( 70.0, 50.0, 20.0 ),
        Vector3( 50.0, 80.0, 10.0 ),
        Vector3( 30.0, 50.0, 20.0 ),
        g_pMaterials[4],
        Vector2( 0.0, 0.0 ),
        Vector2( 0.5, 1.0 ),
        Vector2( 1.0, 0.0 )
    ), 

    // 左.
    Triangle( 
        Vector3( 70.0, 30.0, 20.0 ),
        Vector3( 50.0, 70.0, 10.0 ),
        Vector3( 30.0, 30.0, 20.0 ),
        g_pMaterials[4],
        Vector2( 0.0, 0.0 ),
        Vector2( 0.5, 1.0 ),
        Vector2( 1.0, 0.0 )
    ), 

};

// 矩形.
Quad g_Quads[] = {

    // 左.
    Quad( 
            Vector3( 0,  0.0,  250.0 ),
            Vector3( 0, 100.0, 250.0 ),
            Vector3( 0, 100.0, 0.0 ),
            Vector3( 0,  0.0,  0.0 ),
            g_pMaterials[0],
            Vector2( 0.0, 0.0 ),
            Vector2( 0.0, 2.0 ),
            Vector2( 2.0, 2.0 ),
            Vector2( 2.0, 0.0 )
    ),

    // 奥.
    Quad(
            Vector3( 0,   0.0,  0.0 ),
            Vector3( 0, 100.0,  0.0 ),
            Vector3( 100, 100.0,  0.0 ),
            Vector3( 100,   0.0,  0.0 ),
            g_pMaterials[0],
            Vector2( 0.0, 0.0 ),
            Vector2( 0.0, 2.0 ),
            Vector2( 2.0, 2.0 ),
            Vector2( 2.0, 0.0 )
    ),

    // 手前.
    Quad(
            Vector3(  100,    0.0, 250.0 ),
            Vector3(  100,  100.0, 250.0 ),
            Vector3(  0,  100.0,  250.0 ),
            Vector3(  0,    0.0,  250.0 ),
            g_pMaterials[0],
            Vector2( 0.0, 0.0 ),
            Vector2( 0.0, 2.0 ),
            Vector2( 2.0, 2.0 ),
            Vector2( 2.0, 0.0 )
    ),

    // 右.
    Quad(
            Vector3( 100,   0.0,  0.0 ),
            Vector3( 100, 100.0,  0.0 ),
            Vector3( 100, 100.0, 250.0 ),
            Vector3( 100,  0.0, 250.0 ),
            g_pMaterials[0],
            Vector2( 0.0, 0.0 ),
            Vector2( 0.0, 2.0 ),
            Vector2( 2.0, 2.0 ),
            Vector2( 2.0, 0.0 )
    ),

    // 上
    Quad(
            Vector3( 100, 100.0, 250.0 ),
            Vector3( 100, 100.0,  0.0 ),
            Vector3( 0, 100.0,  0.0 ),
            Vector3( 0, 100.0, 250.0 ),
            g_pMaterials[0],
            Vector2( 2.0, 0.0 ),
            Vector2( 2.0, 2.0 ),
            Vector2( 0.0, 2.0 ),
            Vector2( 0.0, 0.0 )
   ),

    // 下.
    Quad(
            Vector3( 0, 0.0, 250.0 ),
            Vector3( 0, 0.0,  0.0 ),
            Vector3( 100, 0.0,  0.0 ),
            Vector3( 100, 0.0, 250.0 ),
            g_pMaterials[1],
            Vector2( 0.0, 0.0 ),
            Vector2( 0.0, 3.0 ),
            Vector2( 3.0, 3.0 ),
            Vector2( 3.0, 0.0 )
   ),
};

// シェイプリスト.
IShape* g_pShapes[] = {
    &g_Quads[0],
    &g_Quads[1],
    &g_Quads[2],
    &g_Quads[3],
    &g_Quads[4],
    &g_Quads[5],

    &g_Spheres[0],
    &g_Spheres[1],
    &g_Spheres[2],
    &g_Triangles[0],
};

// 境界ボリューム階層.
IShape* g_pBVH = nullptr;


////////////////////////////////////////////////////////////////////////////////////
// Functions
////////////////////////////////////////////////////////////////////////////////////

//----------------------------------------------------------------------------------
//! @brief      ロシアンルーレットに用いる閾値を求めます.
//----------------------------------------------------------------------------------
S3D_INLINE
f64 ComputeThreshold( const Color& value )
{
    f64 result = value.x;
    result = ( value.y > result ) ? value.y : result;
    result = ( value.z > result ) ? value.z : result;

    // 無限ループ対策
    result = Min( result, 0.99 );

    // ゼロ除算対策.
    result = Max( result, DBL_EPSILON );

    return result;
}

//----------------------------------------------------------------------------------
//! @brief      シーンとの交差判定をおこないます.
//----------------------------------------------------------------------------------
S3D_INLINE
bool Intersect(const Ray &ray, HitRecord& record)
{
    HitRecord temp;

    // 交差判定.
    if ( g_pBVH->IsHit( ray, temp ) )
    {
        // 更新.
        record = temp;
    }

    return (record.pShape != nullptr);
}

//---------------------------------------------------------------------------------
//! @brief      指定方向からの放射輝度を求めます.
//!
//! @note       このメソッドは edupt を基にしています.
//!             edupt の解説記事は，http://www.slideshare.net/h013/edupt-kaisetsu-22852235
//!             ソースコードは, https://github.com/githole/edupt
//!             をそれぞれ参照してください.
//---------------------------------------------------------------------------------
Color Radiance(const Ray &inRay, s3d::Random &rnd)
{
    HitRecord record = HitRecord();
    Ray ray( inRay );

    //========================================================
    // レンダリング方程式を展開していくと...
    //  L[0] = Le[0] + Lr[0]
    //       = Le[0] + Wr[0] * L[1]
    //       = Le[0] + Wr[0] * ( Le[1] + Wr[1] * L[2] )
    //       = Le[0] + Wr[0] * ( Le[1] + Wr[1] * ( Le[2] + Wr[2] * L[3] )
    //       = Le[0] + Wr[0] * ( Le[1] + Wr[1] * ( Le[2] + Wr[2] * ( Le[3] + Wr[3] * L[4] )
    //       = ...
    //
    // のようになる.
    //
    // 上記をまじめに解こうとすると, 再帰を使うことになるが
    // プログラムだと, スタックに乗っからなくなる(=スタックオーバーフロー)になる恐れがある.
    // そのため再帰を使わずに, for文でぐーるぐる回して求める.
    // 
    // 少し式をまとめると...
    //  L[0] = Le[0]
    //       + ( Wr[0] ) * Le[0] 
    //       + ( Wr[0] * Wr[1] ) * Le[2]
    //       + ( Wr[0] * Wr[1] * Wr[2] ) * Le[3]
    //       + ( Wr[0] * Wr[1] * Wr[2] * Wr[3] ) * Le[4]
    //       + ...
    //
    // うまくfor文にできるようにさらに式変形.
    // L[0] =   Wr[-1] * Le[0]
    //      + ( Wr[-1] * Wr[0] ) * Le[0]
    //      + ( Wr[-1] * Wr[0] * Wr[1] ) * Le[2]
    //      + ( Wr[-1] * Wr[0] * Wr[1] * Wr[2] ) * Le[3]
    //      + ...
    // ただし， Wr[-1] = 1.0とする.
    // 上記式をfor文に落とし込むと.
    //
    // W = 1.0;
    // L = 0.0;
    // for( i=0; ; ++i )
    // {
    //      L += W * Le[i];
    //      W *= Wr[i];
    // }
    //
    // ... のようになる.
    //========================================================

    Color W( 1.0, 1.0, 1.0 );
    Color L( 0.0, 0.0, 0.0 );

    for( s32 depth=0; /* NOTHING */; ++depth )
    {
        // シーンと交差判定
        if ( !Intersect( ray, record ) )
        { break; }

        // 衝突物体へのポインタ.
        const IShape* pShape = record.pShape;

        // マテリアルへのポインタ.
        const IMaterial* pMaterial = pShape->GetMaterial();

        // 無補正法線データ.
        const Vector3 normalOrg = record.normal;

        // 補正済み法線データ (レイの入出を考慮済み).
        const Vector3 normalMod = ( Vector3::Dot ( normalOrg, ray.dir ) < 0.0 ) ? normalOrg : -normalOrg;

        // 自己発光による放射輝度.
        Color emission = Color::Mul( pMaterial->GetEmissive(), pMaterial->GetTextureColor( record.texcoord ) );
        L += Color::Mul( W, emission );

        // 色の反射率最大のものを得る。ロシアンルーレットで使う。
        // ロシアンルーレットの閾値は任意だが色の反射率等を使うとより良い ... らしい。
        // Memo : 閾値を平均とかにすると，うまい具合にばらけず偏ったりしたので上記を守るのが一番良さげ.
        f64 prob = ComputeThreshold( pMaterial->GetColor() );

        // 最大深度以上になったら，打ち切るために閾値を急激に下げる.
        if ( depth > MAX_DEPTH )
        { prob *= pow( 0.5, depth - MAX_DEPTH ); }

        // ロシアンルーレット!
        if ( rnd.GetAsF64() >= prob )
        { break; }

        // マテリアル計算.
        // TODO : 関数化で分岐処理をなくして，コードをすっきりさせる.
        switch ( pMaterial->GetType() )
        {
            // 完全拡散面
            case MATERIAL_TYPE_MATTE: 
            {
                #pragma region Lambert

                // normalModの方向を基準とした正規直交基底(w, u, v)を作る。
                // この基底に対する半球内で次のレイを飛ばす。
                OrthonormalBasis onb;
                onb.InitFromW( normalMod );

                // コサイン項を使った重点的サンプリング
                const f64 r1  = D_2PI * rnd.GetAsF64();
                const f64 r2  = rnd.GetAsF64();
                const f64 r2s = sqrt(r2);
                Vector3 dir = Vector3::UnitVector(
                    onb.u * cos(r1) * r2s
                  + onb.v * sin(r1) * r2s
                  + onb.w * sqrt(1.0 - r2) );

                //====================================================================
                // レンダリング方程式に対するモンテカルロ積分を考えると、
                // outgoing_radiance = weight * incoming_radiance。
                // ここで、weight = (ρ/π) * cosθ / pdf(ω) / R になる。
                // ρ/πは完全拡散面のBRDFでρは反射率、cosθはレンダリング方程式におけるコサイン項、
                // pdf(ω)はサンプリング方向についての確率密度関数。
                // Rはロシアンルーレットの確率。
                // 今、コサイン項に比例した確率密度関数によるサンプリングを行っているため、pdf(ω) = cosθ/π
                // よって、weight = ρ/ R。
                //=====================================================================

                // 重み更新.
                Color weight = Vector3::Mul( pMaterial->GetColor(), pMaterial->GetTextureColor( record.texcoord ) ) / prob;
                W = Vector3::Mul( W, weight );

                // レイを更新.
                ray.Update( record.position, dir );

                #pragma endregion
            }
            break;

            case MATERIAL_TYPE_CLAY:
            {
                #pragma region Oren-Nayer

                const Clay* pClay = reinterpret_cast<const Clay*>( pMaterial );

                // normalModの方向を基準とした正規直交基底(w, u, v)を作る。
                // この基底に対する半球内で次のレイを飛ばす。
                OrthonormalBasis onb;
                onb.InitFromW( normalMod );

                // コサイン項を使った重点的サンプリング
                const f64 r1  = D_2PI * rnd.GetAsF64();
                const f64 r2  = rnd.GetAsF64();
                const f64 r2s = sqrt(r2);
                Vector3 dir = Vector3::UnitVector(
                    onb.u * cos(r1) * r2s
                  + onb.v * sin(r1) * r2s
                  + onb.w * sqrt(1.0 - r2) );

                //========================================================================
                // レンダリング方程式に対するモンテカルロ積分をLambertと同様に考えると,
                // 従って Wr = color * ( A + B * cosφ * sinα * tanβ ) / q.
                // ただし, α = min( θi, θr ), β = max( θi, θr )とする.
                //========================================================================

                f64 s2 = pClay->GetRoughness() * pClay->GetRoughness();
                f64 A = 1.0 - ( 0.5 * ( s2 / ( s2 + 0.33 ) ) );
                f64 B = 0.45 * ( s2 / ( s2 + 0.09 ) );

                f64 NV = Vector3::Dot( normalMod, ray.dir );
                f64 NL = Vector3::Dot( normalMod, dir );

                Vector3 projI = Vector3::UnitVector( ray.dir  - ( normalMod * NV ) );
                Vector3 projR = Vector3::UnitVector( dir - ( normalMod * NL ) );

                f64 cosPhai = Max( Vector3::Dot( projI, projR ), 0.0 );

                f64 ti    = acos( NV );
                f64 to    = acos( NL );
                f64 alpha = Max( ti, to );
                f64 beta  = Min( ti, to );
                f64 f     = A + B * cosPhai * sin( alpha ) * tan( beta );

                Color weight = Color::Mul( pMaterial->GetColor(), pMaterial->GetTextureColor( record.texcoord ) ) * f / prob;
                W = Color::Mul( W, weight );

                ray.Update( record.position, dir );

                #pragma endregion
            }
            break;

            // 完全鏡面
            case MATERIAL_TYPE_MIRROR:
            {
                #pragma region Mirror
                // ====================================================
                // 完全鏡面なのでレイの反射方向は決定的。
                // ロシアンルーレットの確率で除算するのは上と同じ。
                // ====================================================

                // 反射ベクトルを求める.
                Vector3 reflect = Vector3::Reflect( ray.dir, normalMod );
                reflect.Normalize();

                // 重み更新.
                Color weight = Vector3::Mul( pMaterial->GetColor(), pMaterial->GetTextureColor( record.texcoord ) );
                W = Color::Mul( W, weight );

                // レイを更新.
                ray.Update( record.position, reflect );

                #pragma endregion
            }
            break;

            // 屈折系.
            case MATERIAL_TYPE_REFRACT:
            {
                #pragma region Refraction

                const RefractionMaterial* pRefractionMat = reinterpret_cast<const RefractionMaterial*>( pMaterial );

                // 反射ベクトルを求める.
                Vector3 reflect = Vector3::Reflect( ray.dir, normalOrg );
                reflect.Normalize();

                // レイがオブジェクトから出るのか? 入るのか?
                const bool into = ( Vector3::Dot( normalOrg, normalMod ) > 0.0 );

                // ===============
                // Snellの法則
                // ===============
                
                // 真空の屈折率
                const f64 nc    = 1.0;

                // オブジェクトの屈折率
                const f64 nt    = pRefractionMat->GetRefractivity();

                const f64 nnt   = ( into ) ? ( nc / nt ) : ( nt / nc );
                const f64 ddn   = Vector3::Dot( ray.dir, normalMod );
                const f64 cos2t = 1.0 - nnt * nnt * (1.0 - ddn * ddn);

                // 全反射
                if ( cos2t < 0.0 )
                {
                    // 重み更新.
                    Color weight = Vector3::Mul( pMaterial->GetColor(), pMaterial->GetTextureColor( record.texcoord ) );
                    W = Vector3::Mul( W, weight );

                    // レイを更新.
                    ray.pos = record.position;
                    ray.dir = reflect;

                    // swith-case文脱出.
                    break;
                }

                // 屈折ベクトル.
                Vector3 refract = Vector3::UnitVector(
                    ray.dir * nnt - normalOrg * ( ( into ) ? 1.0 : -1.0 ) * ( ddn * nnt + sqrt(cos2t) ) );

                // SchlickによるFresnelの反射係数の近似を使う
                const f64 a = nt - nc;
                const f64 b = nt + nc;
                const f64 R0 = (a * a) / (b * b);

                const f64 c = 1.0 - ( ( into ) ? -ddn : Vector3::Dot( refract, normalOrg ) );
                const f64 Re = R0 + (1.0 - R0) * pow(c, 5.0); // 反射方向の光が反射してray.dirの方向に運ぶ割合。同時に屈折方向の光が反射する方向に運ぶ割合。
                const f64 Tr = ( 1.0 - Re );

                // 一定以上レイを追跡したら屈折と反射のどちらか一方を追跡する
                // ロシアンルーレットで決定する。
                const f64 P = 0.25 + 0.5 * Re;      // フレネルのグラフを参照.
                
                // 反射の場合.
                if ( rnd.GetAsF64() < P )
                {
                    // 重み更新.
                    Color weight = Vector3::Mul( pMaterial->GetColor(), pMaterial->GetTextureColor( record.texcoord ) ) * Re / ( P * prob );
                    W = Vector3::Mul( W, weight );

                    // レイを更新.
                    ray.pos = record.position;
                    ray.dir = reflect;
                }
                // 屈折の場合.
                else
                {
                    // 重み更新.
                    Color weight = Vector3::Mul( pMaterial->GetColor(), pMaterial->GetTextureColor( record.texcoord ) ) * Tr / ( ( 1.0 - P ) * prob );
                    W = Vector3::Mul( W, weight );

                    // レイを更新.
                    ray.pos = record.position;
                    ray.dir = refract;
                }

                #pragma endregion
            }
            break;

#if 0
            //// プラスチック.
            //case MATERIAL_TYPE_PLASTIC :
            //{
            //    /* NOT_IMPLEMENT */
            //}
            //break;
#endif
        }

        // 重みがゼロなら，以降の結果はゼロとなり無駄な処理になるので打ち切り.
        if ( W == Color( 0.0, 0.0, 0.0 ) )
        { break; }
    }

    // 計算結果を返却.
    return L;
}


//----------------------------------------------------------------------------------
//! @brief      経路追跡法を実行します.
//----------------------------------------------------------------------------------
void PathTrace
(
    const s32 width,
    const s32 height,
    const s32 samples,
    const s32 supersamples
) 
{
    // カメラ更新.
    Camera camera;
    camera.Update( 
        Vector3( 50.0, 52.0, 220.0 ),
        Vector3( 50.0, 50.0, 180.0 ),
        Vector3( 0.0, 1.0, 0.0 ),
        width,
        height,
        D_PIDIV4,
        1.0 );

    // レンダーターゲットのメモリを確保.
    g_pRT = new Color[ width * height ];

    // レンダーターゲットをクリア.
    for( s32 i=0; i<width * height; ++i )
    { g_pRT[i] = Color( 0.0, 0.0, 0.0 ); }

    // 全サンプル数.
    const s32 numSamples = samples * supersamples * supersamples;

    // 1サブサンプルあたり.
    const f64 rate = (1.0 / supersamples);

    // 時間監視スレッドを走らせる.
    uintptr_t ret = _beginthread( TimeWatch, 0, nullptr );
    assert( ret != -1 );    // 失敗しちゃだめよ.

    // 縦方向のループ.
    for (s32 y = 0; y < height; y ++) 
    {
        // 乱数
        s3d::Random rnd(y + 1);

        // 何%完了したか表示する.
        printf_s( "process %lf completed.\n", (100.0 * y / (height - 1)) );

    #if _OPENMP
        #pragma omp parallel for schedule(dynamic, 1) num_threads(8)
    #endif
        // 横方向のループ.
        for (s32 x = 0; x < width; x ++) 
        {
            // ピクセルインデックス.
            const s32 idx = ( ( height - 1 - y ) * width ) + x;

            // 蓄積放射輝度.
            Color accRadiance = Color(0.0, 0.0, 0.0);

            // supersamples x supersamples のスーパーサンプリング
            for (s32 sy = 0; sy < supersamples; sy ++) 
            for (s32 sx = 0; sx < supersamples; sx ++) 
            {
                // 一つのサブピクセルあたりsamples回サンプリングする
                for (s32 s = 0; s < samples; s ++) 
                {
                    const f64 r1 = sx * rate + rate / 2.0;
                    const f64 r2 = sy * rate + rate / 2.0;

                    // ぶっ飛ばすレイを取得.
                    Ray ray = camera.GetRay(
                        ( r1 + x ) / width  - 0.5,
                        ( r2 + y ) / height - 0.5 );

                    // 加算.
                    accRadiance += Radiance( ray, rnd );
                }
            }

            // ピクセルカラーを加算.
            g_pRT[ idx ] += accRadiance / numSamples;
        }
    }

    g_Mutex.Lock();
    {
        // 終了フラグを立てる.
        g_IsFinished = true;
    }
    g_Mutex.Unlock();

    // スレッドの終了を待機する.
    for( u32 i=0; i<(UINT_MAX-10); ++i )
    {
        // ウォッチャーが終了するまで待ち.
        if ( g_WatcherEnd )
        { break; }

        // オネンネしな！
        Sleep( 10 );
    }

    char filename[256];
    tm      local_time;
    time_t  t = time( nullptr );
    errno_t err = localtime_s( &local_time, &t );

    if ( err == 0 )
    {
        // output_yyyymmdd_hhmmss.bmpという形式の名前にする.
        // ex) output_20130805_153034.bmp →　2013/08/05 15:30 34sec
        sprintf_s( filename, "img/output_%04d%02d%02d_%02d%02d%02d.bmp",
            local_time.tm_year + 1900,
            local_time.tm_mon + 1,
            local_time.tm_mday,
            local_time.tm_hour,
            local_time.tm_min,
            local_time.tm_sec );

        // 最終結果をBMPファイルに出力.
        SaveToBMP( filename, width, height, &g_pRT[0].x );
    }
    else
    {
        // 最終結果をBMPファイルに出力.
        SaveToBMP( "img/output.bmp", width, height, &g_pRT[0].x );
    }

    // メモリ解放.
    if ( g_pRT )
    {
        delete[] g_pRT;
        g_pRT = nullptr;
    }
}

//-----------------------------------------------------------------------------
//      時間監視メソッド.
//-----------------------------------------------------------------------------
void TimeWatch( void* )
{
    // レンダリング開始時刻を記録.
    Timer timer;
    timer.Start();

    // 定期監視を開始.
    Timer captureTimer;
    captureTimer.Start();

    // 1時間以上経過するか, レンダリングが先に終了するまでループ.
    while( 1 )
    {
        // 経過時間を取得.
        captureTimer.Stop();
        f64 sec  = captureTimer.GetElapsedTimeSec();

        // 59.9秒以上立ったらキャプチャー.
        if ( sec > 59.9 )
        {
            char filename[256];
            tm local_time;
            time_t t = time( nullptr );
            errno_t err = localtime_s( &local_time, &t );

            if ( err == 0 )
            {
                // frame_yyyymmdd_hhmmss.bmpという形式の名前にする.
                // ex) result_20130805_153034.bmp →　2013/08/05 15:30 34sec
                sprintf_s( filename, "img/frame/frame_%04d%02d%02d_%02d%02d%02d.bmp",
                    local_time.tm_year + 1900,
                    local_time.tm_mon + 1,
                    local_time.tm_mday,
                    local_time.tm_hour,
                    local_time.tm_min,
                    local_time.tm_sec );

                // 結果をBMPファイルに出力.
                SaveToBMP( filename, g_Width, g_Height, &g_pRT[0].x );
            }
            else
            {
                // 最終結果をBMPファイルに出力.
                SaveToBMP( "img/frame/frame.bmp", g_Width, g_Height, &g_pRT[0].x );
            }

            // タイマーを再スタート.
            captureTimer.Start();
        }

        // レンダリング開始してからの時間を取得.
        timer.Stop();
        f64 hour = timer.GetElapsedTimeHour();

#if 1
        // 1時間以上たった
        if ( hour >= 1.0 )
        {
            // 最後のフレームをキャプチャー.
            SaveToBMP( "img/final_frame.bmp", g_Width, g_Height, &g_pRT[0].x );

            g_Mutex.Lock();
            {
                g_WatcherEnd = true;
            }
            g_Mutex.Unlock();

            // ループ脱出.
            //break;
        }
#endif

        // レンダリングが正常終了している場合.
        if ( g_IsFinished )
        {
            printf_s( "Finished Rendering!!\n" );

            FILE* pFile;
            errno_t err = fopen_s( &pFile, "result.txt", "w" );

            if ( err == 0 )
            {
                fprintf( pFile, "Setting : \n" );
                fprintf( pFile, "    width      = %d\n", g_Width );
                fprintf( pFile, "    height     = %d\n", g_Height );
                fprintf( pFile, "    sample     = %d\n", g_NumSample );
                fprintf( pFile, "    sub sumple = %d\n", g_NumSubSample );
                fprintf( pFile, "Rendering Time %lf (sec)\n", timer.GetElapsedTimeSec() );
                fprintf( pFile, "               %lf (min)\n", timer.GetElapsedTimeMin() );
                fprintf( pFile, "               %lf (hour)\n", timer.GetElapsedTimeHour() );
                fprintf( pFile, "Per Pixel      %lf (msec)\n", timer.GetElapsedTimeMsec() / ( g_Width * g_Height ) );

                fclose( pFile );
            }

            g_Mutex.Lock();
            {
                g_WatcherEnd = true;
            }
            g_Mutex.Unlock();

            // ループ脱出.
            break;
        }

        // 100 msec 寝かせる.
        Sleep( 100 );
    }
}

//////////////////////////////////////////////////////////////////////////////////
// App class
//////////////////////////////////////////////////////////////////////////////////

//--------------------------------------------------------------------------------
//      コンストラクタです.
//--------------------------------------------------------------------------------
App::App()
{ /* DO_NOTHING */ }

//--------------------------------------------------------------------------------
//      デストラクタです.
//--------------------------------------------------------------------------------
App::~App()
{ /* DO_NOTHING */ }

//--------------------------------------------------------------------------------
//      アプリケーションを実行します.s
//--------------------------------------------------------------------------------
void App::Run( Config& config )
{
    // 起動画面.
    ILOG( "//=================================================================" );
    ILOG( "//  File   : s3d.exe" );
    ILOG( "//  Desc   : Path Tarcer \"Salty\"" );
    ILOG( "//  Author : Pocol" );
    ILOG( "//=================================================================" );
    ILOG( " Configuration : " );
    ILOG( "     width      = %d", config.width );
    ILOG( "     height     = %d", config.height );
    ILOG( "     sample     = %d", config.numSamples );
    ILOG( "     sub sumple = %d", config.numSubSamples );
    ILOG( "--------------------------------------------------------------------" );

    // 画像出力用ディレクトリ作成.
    _mkdir( "./img" );
    _mkdir( "./img/frame" );

    // かっこ悪いけど, グローバルに格納.
    g_Width        = config.width;
    g_Height       = config.height;
    g_NumSample    = config.numSamples;
    g_NumSubSample = config.numSubSamples;

    // 物体の数を算出.
    u32 numShapes = sizeof( g_pShapes ) / sizeof( g_pShapes[0] );

    // BVH構築.
    g_pBVH = BVH::BuildBranch( g_pShapes, numShapes );
    assert( g_pBVH != nullptr );

    // レイトレ！
    PathTrace( config.width, config.height, config.numSamples, config.numSubSamples );

    // メモリ解放.
    if ( g_pBVH )
    {
        delete g_pBVH;
        g_pBVH = nullptr;
    }

}


} // namespace s3d

