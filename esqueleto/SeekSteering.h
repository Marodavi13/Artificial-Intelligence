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
	CSeekSteering(Character* character, const float& weight = 1.f);
	~CSeekSteering();

	void GetSteering(Params* params , USVec2D & outLinearAcceleration, float & outAngularAcceleration) override;
	void DrawDebug() const override;
	void SetWeight(const float& weight);
private:
	CArriveSteering* mArrive;
	CAlignSteering * mAlign;
	USVec2D mDesiredVelocity;
	USVec2D mDesiredAcceleration;

};

