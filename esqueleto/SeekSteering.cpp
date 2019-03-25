#include "SeekSteering.h"
#include "character.h"




void CSeekSteering::GetSteering(Character* character, Params* params,USVec2D &outLinearAcceleration, float &outAngularAcceleration)
{
	mCharacterLocation = character->GetLoc();
	mDesiredVelocity = params->targetPosition - mCharacterLocation;
	if (IsVectorBiggerThan(mDesiredVelocity, params->max_velocity)) 
	{
		mDesiredVelocity.NormSafe();
		mDesiredVelocity.Scale(params->max_velocity);
	}
	mDesiredAcceleration = mDesiredVelocity - character->GetLinearVelocity();
	
	if (IsVectorBiggerThan(mDesiredAcceleration, params->max_acceleration)) {
		mDesiredAcceleration.NormSafe();
		mDesiredAcceleration.Scale(params->max_acceleration);
	}
	//printf("Acceleration: %f , %f \n", mAcceleration.mX,mAcceleration.mY);
	outLinearAcceleration = mDesiredAcceleration;

}

void CSeekSteering::DrawDebug()
{
	MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get();
	gfxDevice.SetPenColor(0.0f, 0.0f, 1.0f, 0.5f);

	MOAIDraw::DrawLine(mCharacterLocation, mCharacterLocation + mDesiredVelocity);

	gfxDevice.SetPenColor(0.0f, 1.0f, 0.0f, 0.5f);

	MOAIDraw::DrawLine(mCharacterLocation, mCharacterLocation + mDesiredAcceleration);
}
