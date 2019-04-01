#pragma once
#include <stdafx.h>

class Character;
struct Params;


class CSteering
{
public:
	CSteering();
	CSteering(Character* character, const float& weight = 1.f);
	virtual ~CSteering();

	virtual void GetSteering(Params* params, USVec2D &outLinearAcceleration,float &outAngularAcceleration) = 0;
	virtual void DrawDebug() = 0;
	virtual void SetWeight(const float& weight) { mWeight = weight; }

protected:
	//Character
	Character*	mCharacter;
	//Character Location
	USVec2D		mCharacterLocation;
	//Weight of the acceleration
	float		mWeight = 1.f;
};


