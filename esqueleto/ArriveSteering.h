#pragma once
#include "Steering.h"


class Character;

class CArriveSteering :  public CSteering
{
public:
	CArriveSteering();
	CArriveSteering(Character* character, const float& weight = 1.f);

	~CArriveSteering();

	void GetSteering(Params* params, USVec2D &outLinearAcceleration, float &outAngularAcceleration) override;
	void DrawDebug() const override;
	void Arrive(USVec2D& LinearAcceleration);
	void CleanVariables() { mDesiredVelocity = USVec2D(0.f, 0.f); mDesiredAcceleration = mDesiredVelocity; }
private:
	USVec2D mDesiredVelocity;
	USVec2D mDesiredAcceleration;

	bool bIsArriving = false;
};

