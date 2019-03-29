#pragma once
#include "Steering.h"

class Character;
class CArriveSteering;
class CAlignSteering;
using namespace std;

class CSeekSteering : public CSteering
{
public:
	CSeekSteering();
	CSeekSteering(Character* character);
	~CSeekSteering();

	void GetSteering(Params* params , USVec2D & outLinearAcceleration, float & outAngularAcceleration);
	void DrawDebug();

	
private:
	CArriveSteering* mArrive;
	CAlignSteering* mAlign;
	USVec2D mDesiredVelocity;
	USVec2D mDesiredAcceleration;

};

