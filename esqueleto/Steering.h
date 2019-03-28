#pragma once
#include <stdafx.h>

class Character;
struct Params;


class CSteering
{
public:
	CSteering();
	CSteering(Character* character);
	virtual ~CSteering();

	virtual void GetSteering(Params* params, USVec2D &outLinearAcceleration,float &outAngularAcceleration) = 0;
	virtual void DrawDebug() = 0;
protected:
	Character* mCharacter;
};


