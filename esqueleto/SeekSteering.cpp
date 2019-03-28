#include "SeekSteering.h"
#include "character.h"


CSeekSteering::CSeekSteering()
{
	cout << "SeekSteering Constructor" << endl;
}

CSeekSteering::CSeekSteering(Character * character) : CSteering(character)
{
}

CSeekSteering::~CSeekSteering()
{
	cout << "SeekSteering Destructor" << endl;
}



void CSeekSteering::GetSteering(Params* params,USVec2D &outLinearAcceleration, float &outAngularAcceleration)
{
	mCharacterLocation = mCharacter->GetLoc();

	mDesiredVelocity = params->targetPosition - mCharacterLocation;
	SCALEVECTOR(mDesiredVelocity, params->max_velocity)

	mDesiredAcceleration = mDesiredVelocity - mCharacter->GetLinearVelocity();
	SCALEVECTOR(mDesiredAcceleration, params->max_acceleration)

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
