#include "SeekSteering.h"
#include "character.h"
#include "ArriveSteering.h"
#include "AlignSteering.h"
CSeekSteering::CSeekSteering()
{
	cout << "SeekSteering Constructor" << endl;
	
}

CSeekSteering::CSeekSteering(Character * character) : CSteering(character)
{
	mArrive = new CArriveSteering(character);
	mAlign	= new CAlignSteering(character);
}

CSeekSteering::~CSeekSteering()
{
	delete mArrive;
	delete mAlign;
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

	mArrive->GetSteering(params, outLinearAcceleration, outAngularAcceleration);
	mAlign->GetSteering	(params, outLinearAcceleration, outAngularAcceleration);
}

void CSeekSteering::DrawDebug()
{
	MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get();
	gfxDevice.SetPenColor(0.0f, 0.0f, 1.0f, 0.5f);

	MOAIDraw::DrawLine(mCharacterLocation, mCharacterLocation + mDesiredVelocity);

	gfxDevice.SetPenColor(0.0f, 1.0f, 0.0f, 0.5f);

	MOAIDraw::DrawLine(mCharacterLocation, mCharacterLocation + mDesiredAcceleration);

	mArrive->DrawDebug();
}
