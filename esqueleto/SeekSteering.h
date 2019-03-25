#pragma once
#include "Steering.h"

class Character;


class CSeekSteering : public CSteering
{
public:
	CSeekSteering();
	~CSeekSteering();

	void GetSteering(Character* character, Params* params , USVec2D & outLinearAcceleration, float & outAngularAcceleration);
	void DrawDebug();

	
private:
	
	USVec2D mCharacterLocation;
	USVec2D mDesiredVelocity;
	USVec2D mDesiredAcceleration;

};

CSeekSteering::CSeekSteering()
{
}

CSeekSteering::~CSeekSteering()
{
}

