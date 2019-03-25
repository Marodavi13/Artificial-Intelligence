#pragma once
#include <stdafx.h>

class Character;
struct Params;


class CSteering
{
public:
	CSteering();
	virtual ~CSteering();

	virtual void GetSteering(Character* character, Params* params, USVec2D &outLinearAcceleration,float &outAngularAcceleration) = 0;
	virtual void DrawDebug() = 0;

private:


};


