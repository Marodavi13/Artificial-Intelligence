#include "AlignSteering.h"
#include "character.h"

CAlignSteering::CAlignSteering()
{
}

CAlignSteering::CAlignSteering(Character * character): CSteering(character)
{
}

CAlignSteering::~CAlignSteering()
{
}

void CAlignSteering::GetSteering(Params * params, USVec2D & outLinearAcceleration, float & outAngularAcceleration)
{
	float characterRotation = mCharacter->GetRot();
	
	SetAngleInBounds(characterRotation);
	USVec2D totalVelocity = params->targetPosition - mCharacter->GetLoc();
	//Stop rotating if i am too close to target
	if(totalVelocity.LengthSquared() < 100.f)
	{
		Arrive(outAngularAcceleration);
	}
	else
	{
		//if i am inside de destination angle, stop
		float targetAngle = GetAngle(totalVelocity);
		if (abs(targetAngle - characterRotation) < params->dest_angle)
		{
			Arrive(outAngularAcceleration);
		}
		else
		{
			//set desired rotation
			mDesiredVelocity = targetAngle - characterRotation;
			SetAngleInBounds(mDesiredVelocity);
			SCALEFLOAT(mDesiredVelocity, params->max_angular_velocity)
			//set desired acceleration
			mDesiredAcceleration = mDesiredVelocity - mCharacter->GetAngularVelocity();
			SCALEFLOAT(mDesiredAcceleration, params->max_angular_acceleration)
			outAngularAcceleration = mDesiredAcceleration;
		}
	}
}

void CAlignSteering::DrawDebug()
{
}

void CAlignSteering::Arrive(float& outAngularAcceleration)
{
	mCharacter->SetAngularVelocity(0.f);
	outAngularAcceleration = 0.f;
}
