﻿//-------------------------------------------------------------------------------------------------
// File : s3d_bucket.h
// Desc : Bucket Module.
// Copyright(c) Project Asura. All right reserved.
//-------------------------------------------------------------------------------------------------
#pragma once

//-------------------------------------------------------------------------------------------------
// Includes
//-------------------------------------------------------------------------------------------------
#include <s3d_math.h>
#include <array>


namespace s3d {

///////////////////////////////////////////////////////////////////////////////////////////////////
// Bucket structure
///////////////////////////////////////////////////////////////////////////////////////////////////
struct Bucket
{
    u32         count;
    BoundingBox box;
};

//-------------------------------------------------------------------------------------------------
// Type definitions.
//-------------------------------------------------------------------------------------------------
typedef std::array<Bucket, 12>  BucketSet;

} // namespace s3d
