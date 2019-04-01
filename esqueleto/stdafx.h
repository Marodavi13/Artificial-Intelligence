#pragma once
#include <moaicore/pch.h>
#include <moaicore/MOAIGfxDevice.h>
#include <moaicore/MOAIDraw.h>
#include <moaicore/MOAIEntity2D.h>
#include "uslscore\USVec2D.h"
#define RAD2DEG 180.f/PI
#define SCALEVECTOR(vector,max)	if(IsVectorBiggerThan(vector,max)){vector.NormSafe();vector.Scale(max);}
#define SCALEFLOAT(number,max)	if(abs(number)> max){number = (signbit(number) * -2.f + 1.f) * max;}
#define RED		1.f,0.f,0.f,1.f
#define BLUE	0.f,0.f,1.f,1.f
#define GREEN	0.f,1.f,0.f,1.f
#define WHITE	1.f,1.f,1.f,1.f

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

static void SetAngleInBounds(float &angle)
{
	while(angle > 180.f)
	{
		angle -= 360.f;
	}
	while(angle < -180.f)
	{
		angle += 360.f;
	}
}
static float GetAngle(const USVec2D vector)
{
	USVec2D tempVector = vector;
	tempVector.NormSafe();
	float angle = ACos(tempVector.Dot(USVec2D(1.0f, 0.f))) * RAD2DEG;
	SetAngleInBounds(angle);
	return angle;
}