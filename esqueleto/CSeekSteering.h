#pragma once
#include "character.h"
#include "uslscore\USVec2D.h"


class Character;

class CSeekSteering
{
public:
	CSeekSteering();
	~CSeekSteering();

	USVec2D getSteering(Character* character,  USVec2D target);
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

