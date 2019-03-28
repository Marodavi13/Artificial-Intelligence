#pragma once
#include <moaicore/pch.h>
#include <moaicore/MOAIGfxDevice.h>
#include <moaicore/MOAIDraw.h>
#include <moaicore/MOAIEntity2D.h>
#include "uslscore\USVec2D.h"

static bool IsVectorBiggerThan(const USVec2D vector, const float otherParam, float* lengthSquared = nullptr)  
{
	if(lengthSquared)
	{
		*lengthSquared = vector.LengthSquared();
		return *lengthSquared > pow(otherParam, 2);

	}
	else
	{
		return vector.LengthSquared() > pow(otherParam, 2);
	}
}