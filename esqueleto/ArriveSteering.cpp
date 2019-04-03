#include "ArriveSteering.h"
#include "character.h"
//#include "CSeekArrive.h"



CArriveSteering::CArriveSteering()
{
	cout << "ArriveSteering Constructor" << endl;
}

CArriveSteering::CArriveSteering(Character * character, const float& weight): CSteering(character, weight)
{
}

CArriveSteering::~CArriveSteering()
{
	cout << "ArriveSteering Destructor" << endl;

}

void CArriveSteering::GetSteering(Params * params, USVec2D & outLinearAcceleration, float & outAngularAcceleration)
{
	//Check Arrival distance
	mCharacterLocation = mCharacter->GetLoc();
	mDesiredVelocity = params->target_position - mCharacter->GetLoc();
	float distanceSquared = 0.f;
	if (!IsVectorBiggerThan(mDesiredVelocity, params->arrive_radius, &distanceSquared))
	{
		if(distanceSquared < pow(params->dest_radius,2.f))
		{
			Arrive(outLinearAcceleration);
		}
		else
		{
			bIsArriving = true;
			//Set desired Velocity
			mDesiredVelocity.NormSafe();
			mDesiredVelocity.Scale(mCharacter->GetMaxSpeed());
			float distScaler = (Sqrt(distanceSquared) - params->dest_radius);
			if(distScaler < 0.f)
			{
				distScaler = 0.f;
				Arrive(outLinearAcceleration);
			}
			else
			{
				mDesiredVelocity = mDesiredVelocity * distScaler / (params->arrive_radius - params->dest_radius);
				//Calculate linear acceleration
				mDesiredAcceleration = (mDesiredVelocity - mCharacter->GetLinearVelocity());
				//Calculate desired acceleration
				if (mDesiredAcceleration.LengthSquared() > 0.f)
				{
					mDesiredAcceleration.NormSafe();
					mDesiredAcceleration = mDesiredAcceleration * params->max_deceleration;
				}
				//Don't accelerate if desired velocity and current velocity are very similar
				else {
					mDesiredAcceleration = USVec2D(0.0f, 0.0f);
				}
				outLinearAcceleration = mDesiredAcceleration * mWeight;;
			}
		}
	}
	else
	{
		bIsArriving = false;

	}
}

void CArriveSteering::DrawDebug() const
{
	MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get();
	if (bIsArriving)
	{
		gfxDevice.SetPenColor(RED);
		MOAIDraw::DrawLine(mCharacterLocation, mCharacterLocation + mDesiredAcceleration);
	}
}

void CArriveSteering::Arrive(USVec2D & LinearAcceleration)
{
	LinearAcceleration = USVec2D(0.f, 0.f);
	mDesiredAcceleration = LinearAcceleration;
	mCharacter->SetLinearVelocity(LinearAcceleration);
}
