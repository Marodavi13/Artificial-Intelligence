#pragma once
#ifndef CHARACTER
#include "character.h"
#endif // !CHARACTER




class Character;

class CSeekSteering
{
public:
	CSeekSteering();
	~CSeekSteering();

	USVec2D getSteering(Character* character,  Params params);
	void DrawDebug();

	
private:
	
	USVec2D mLocation;
	USVec2D mSpeed;
	USVec2D mAcceleration;
	USVec2D realSpeed;
};

CSeekSteering::CSeekSteering()
{
}

CSeekSteering::~CSeekSteering()
{
}

