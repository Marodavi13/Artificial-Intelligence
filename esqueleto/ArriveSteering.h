#pragma once
#include "Steering.h"


class Character;

class CArriveSteering :  public CSteering
{
public:
	CArriveSteering();
	CArriveSteering(Character* character, const float& weight = 1.f);

	~CArriveSteering();

	virtual void GetSteering(Params* params, USVec2D &outLinearAcceleration, float &outAngularAcceleration);
	virtual void DrawDebug();
	void Arrive(USVec2D& LinearAcceleration);
private:
	USVec2D mDesiredVelocity;
	USVec2D mDesiredAcceleration;

	bool bIsArriving = false;
};

