#include <stdafx.h>
#include "CSeekSteering.h"





USVec2D CSeekSteering::getSteering(Character* character, USVec2D target)
{
	mLocation = character->GetLoc();
	mSpeed = target - mLocation;
	
	mAcceleration = mSpeed - character->GetLinearVelocity();
	
	if (mAcceleration.Length() > character->getMaxAcceleration()) {
		mAcceleration = mAcceleration / mAcceleration.Length() * character->getMaxAcceleration();
	}
	printf("Acceleration: %f , %f \n", mAcceleration.mX,mAcceleration.mY);

	realSpeed = character->GetLinearVelocity();
	return mAcceleration;
}

void CSeekSteering::DrawDebug()
{
	MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get();
	gfxDevice.SetPenColor(0.0f, 0.0f, 1.0f, 0.5f);

	MOAIDraw::DrawLine(mLocation, mLocation+ realSpeed);

	gfxDevice.SetPenColor(0.0f, 1.0f, 0.0f, 0.5f);

	MOAIDraw::DrawLine(mLocation + realSpeed, mLocation+mAcceleration + realSpeed);

	gfxDevice.SetPenColor(1.0f, 1.0f, 1.0f, 0.5f);

	//MOAIDraw::DrawPoint()

}
