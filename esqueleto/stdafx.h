#pragma once
#include <moaicore/pch.h>
#include <moaicore/MOAIGfxDevice.h>
#include <moaicore/MOAIDraw.h>
#include <moaicore/MOAIEntity2D.h>
#include "uslscore\USVec2D.h"
//Math
#define RAD2DEG 180.f/3.1416f
//Colors
#define RED		1.f,    0.f,    0.f,    0.f
#define BLUE	0.f,    0.f,    1.f,    0.f
#define GREEN	0.f,    1.f,    0.f,    0.f
#define WHITE	1.f,    1.f,    1.f,    0.f
#define YELLOW	0.f,    1.f,    1.f,    0.f

#define BROWN   0.65f,  0.165f, 0.165f, 0.f
//Screen and map
#define SCREEN_WIDTH  1024
#define SCREEN_HEIGHT 1024
#define MAP_ROWS    10
#define MAP_COLUMNS 10
#define GRID_SIZE   50
#define GRID_RECT(grid) grid.mX - GRID_SIZE * 0.5f, grid.mY - GRID_SIZE * 0.5f, grid.mX + GRID_SIZE * 0.5f, grid.mY + GRID_SIZE * 0.5f
//Chars
#define NORMAL    'o'
#define MUD       'S'
#define WATER     'W'
#define OBSTACLE  'X'

//Costs
#define C_NORMAL    1.f
#define C_MUD       2.f
#define C_WATER     3.f
#define C_OBSTACLE -1.f
//Grid frontiers
//Clamp vector and float
#define SCALEVECTOR(vector,max)	if(IsVectorBiggerThan(vector,max)){vector.NormSafe();vector.Scale(max);}
#define SCALEFLOAT(number,max)	if(abs(number)> max){number = (signbit(number) * -2.f + 1.f) * max;}
//Positions
#define SAME_ROW  0
#define UP_ROW      1
#define DOWN_ROW    2
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
static bool IsLocationInCircle(const USVec2D& location, const USVec2D& circleOrigin, const float& circleRadius)
{
	return !IsVectorBiggerThan(location - circleOrigin, circleRadius);
}

template<typename T>
static bool IsValidIndex(const T& index, const T& size)
{
    return (index < size) && index >= 0;
}

