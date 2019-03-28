#include "ArriveSteering.h"
#include "character.h"
//#include "CSeekArrive.h"

/*void CSeekArrive::setArrivalVelocity(Character* character, Params params) {
	float distanceToTarget = (character->GetLoc() - params.targetPosition).Length();

	if (distanceToTarget <= params.dest_radius) {
		USVec2D desiredSpeed = character->GetLinearVelocity();
		desiredSpeed.Lerp(params.targetPosition, distanceToTarget / params.dest_radius);
		character->SetLinearVelocity(desiredSpeed.mX, desiredSpeed.mY);
	}
}*/

CArriveSteering::CArriveSteering()
{
	cout << "ArriveSteering Constructor" << endl;
}

CArriveSteering::CArriveSteering(Character * character): CSteering(character)
{
}

CArriveSteering::~CArriveSteering()
{
	cout << "ArriveSteering Destructor" << endl;

}

void CArriveSteering::GetSteering(Params * params, USVec2D & outLinearAcceleration, float & outAngularAcceleration)
{
	//Check Arrival distance
	mDesiredVelocity = params->targetPosition - mCharacter->GetLoc();
	float distanceSquared = 0.f;
	if (!IsVectorBiggerThan(mDesiredVelocity, params->arrive_radius, &distanceSquared))
	{
		bIsArriving = true;
		//Set desired Velocity
		mDesiredVelocity.NormSafe();
		mDesiredVelocity.Scale(mCharacter->GetMaxSpeed());
		mDesiredVelocity = mDesiredVelocity * Sqrt(distanceSquared) / params->arrive_radius;;
		//Calculate linear acceleration
		mDesiredAcceleration = mDesiredVelocity - mCharacter->GetLinearVelocity();
		if(IsVectorBiggerThan(mDesiredAcceleration,params->max_acceleration))
		{
			mDesiredAcceleration.NormSafe();
			mDesiredAcceleration.Scale(params->max_acceleration);
		}
		outLinearAcceleration = mDesiredAcceleration;
	}
	else
	{
		bIsArriving = false;

	}
}

void CArriveSteering::DrawDebug()
{
	MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get();
	if (bIsArriving)
	{
		gfxDevice.SetPenColor(1.0f, 0.0f, 0.0f, 1.f);
		MOAIDraw::DrawLine(static_cast<USVec2D>(mCharacter->GetLoc()), static_cast<USVec2D>(mCharacter->GetLoc()) + mDesiredAcceleration);
	}

}
