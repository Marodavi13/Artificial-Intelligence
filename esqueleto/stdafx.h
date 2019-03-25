#pragma once
#include <moaicore/pch.h>
#include <moaicore/MOAIGfxDevice.h>
#include <moaicore/MOAIDraw.h>
#include <moaicore/MOAIEntity2D.h>
#include "uslscore\USVec2D.h"

static bool IsVectorBiggerThan(const USVec2D Vector, const float OtherParam)  
{
	return Vector.LengthSquared() > pow(OtherParam, 2);
}