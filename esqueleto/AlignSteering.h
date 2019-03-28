#pragma once
#include "Steering.h"

class Character;

using namespace std;

class CAlignSteering : public CSteering
{
public:
	CAlignSteering();
	CAlignSteering(Character* character);
	~CAlignSteering();

	void GetSteering(Params* params, USVec2D & outLinearAcceleration, float & outAngularAcceleration);
	void DrawDebug();
	void Arrive(float& outAngularAcceleration);

private:

	float mDesiredVelocity;
	float mDesiredAcceleration;

};
