#include "AlignSteering.h"
#include "character.h"

CAlignSteering::CAlignSteering()
{
}

CAlignSteering::CAlignSteering(Character * character, const float& weight): CSteering(character,weight)
{
}

CAlignSteering::~CAlignSteering()
{
}

void CAlignSteering::GetSteering(Params * params, USVec2D & outLinearAcceleration, float & outAngularAcceleration)
{
	float characterRotation = mCharacter->GetRot();
	
	SetAngleInBounds(characterRotation);
	USVec2D totalVelocity = params->target_position - mCharacter->GetLoc();
	//Stop rotating if i am too close to target
	if(totalVelocity.LengthSquared() < 50.f)
	{
		Arrive(outAngularAcceleration);
	}
	else
	{
		//if i am inside de destination angle, stop
		params->target_rotation = GetAngle(totalVelocity);
		if (abs(params->target_rotation - characterRotation) < params->dest_angle)
		{
			Arrive(outAngularAcceleration);
		}
		else
		{
			//set desired rotation
			mDesiredVelocity = params->target_rotation - characterRotation;
			SetAngleInBounds(mDesiredVelocity);
			//set desired acceleration
			mDesiredAcceleration = (mDesiredVelocity - mCharacter->GetAngularVelocity()) * mWeight;
			//SCALEFLOAT(mDesiredAcceleration, params->max_angular_acceleration)
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
