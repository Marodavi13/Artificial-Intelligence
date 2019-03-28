#pragma once
#include "Steering.h"


class Character;

class CArriveSteering :  public CSteering
{
public:
	CArriveSteering();
	CArriveSteering(Character* character);

	~CArriveSteering();

	virtual void GetSteering(Params* params, USVec2D &outLinearAcceleration, float &outAngularAcceleration);
	virtual void DrawDebug();
private:
	USVec2D mDesiredVelocity;
	USVec2D mDesiredAcceleration;

	bool bIsArriving;
};

