#include "SeekSteering.h"
#include "character.h"
#include "ArriveSteering.h"
#include "AlignSteering.h"
CSeekSteering::CSeekSteering()
{
	cout << "SeekSteering Constructor" << endl;
	
}

CSeekSteering::CSeekSteering(Character * character, const float& weight) : CSteering(character, weight)
{
	mArrive = new CArriveSteering(character,weight);
	mAlign	= new CAlignSteering(character, weight);
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
	mDesiredVelocity.NormSafe();
	mDesiredVelocity.Scale(params->max_velocity);

	mDesiredAcceleration = (mDesiredVelocity - mCharacter->GetLinearVelocity()) * mWeight;

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

void CSeekSteering::SetWeight(const float & weight)
{
	CSteering::SetWeight(weight);
	mArrive->SetWeight(weight);
	mAlign->SetWeight(weight);
}
