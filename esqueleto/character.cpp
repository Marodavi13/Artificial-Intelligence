#include <stdafx.h>
#include "character.h"
#include <tinyxml.h>
#include "SeekSteering.h"
#include "ArriveSteering.h"
#include "AlignSteering.h"
#include "PathSteering.h"
#include "AvoidanceSteering.h"
Character::Character() : mLinearVelocity(0.0f, 0.0f), mAngularVelocity(0.0f)
{
	RTTI_BEGIN
		RTTI_EXTEND (MOAIEntity2D)
	RTTI_END
}

Character::~Character()
{

}

void Character::OnStart()
{
    ReadParams("params.xml", mParams);
	///mSeekSteering = new CSeekSteering(this);
	//mPathSteering = new CPathSteering(this);
	//mPathSteering->SetPath("path.xml");
	//AddSteeringBehavior(mPathSteering);
	CAvoidanceSteering* Avoid = new CAvoidanceSteering(this);
	AddSteeringBehavior(Avoid);
}

void Character::OnStop()
{
	for(CSteering* Steer: steeringBehaviors)
	{
		delete Steer;
	}
	steeringBehaviors.empty();
	//delete mSeekSteering;
	//delete mArriveSteering;
	//delete mAlignSteering;
	 //delete mPathSteering;
}

void Character::OnUpdate(float step)
{
	USVec2D LinearAcceleration(0.f,0.f);
	float AngularAcceleration = 0.f;

	//mSeekSteering->GetSteering	(&mParams, LinearAcceleration, AngularAcceleration);
	for(CSteering* steering: steeringBehaviors)
	{
		steering->GetSteering(&mParams, LinearAcceleration, AngularAcceleration);
	}
	
	SetLinearVelocity	(GetLinearVelocity()  + LinearAcceleration * step);
	SetAngularVelocity	(GetAngularVelocity() + AngularAcceleration * step);

	SetLoc(GetLoc() + GetLinearVelocity()  * step);
	SetRot(GetRot() + GetAngularVelocity() * step);
	
}

void Character::DrawDebug()
{
	MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get();
	gfxDevice.SetPenColor(1.0f, 0.0f, 0.0f, 1.f);
	//gfxDevice.SetPenWidth(1.f);
	MOAIDraw::DrawPoint(mParams.targetPosition);
	for(CSteering* steering : steeringBehaviors)
	{
		steering->DrawDebug();
	}
	//mPathSteering->DrawDebug();
	//mSeekSteering->DrawDebug();
	//mArriveSteering->DrawDebug();
}





// Lua configuration

void Character::RegisterLuaFuncs(MOAILuaState& state)
{
	MOAIEntity2D::RegisterLuaFuncs(state);
	
	luaL_Reg regTable [] = {
		{ "setLinearVel",			_setLinearVel},
		{ "setAngularVel",			_setAngularVel},
		{ NULL, NULL }
	};

	luaL_register(state, 0, regTable);
}

int Character::_setLinearVel(lua_State* L)
{
	MOAI_LUA_SETUP(Character, "U")
	
	float pX = state.GetValue<float>(2, 0.0f);
	float pY = state.GetValue<float>(3, 0.0f);
	self->SetLinearVelocity(USVec2D(pX, pY));
	return 0;	
}

int Character::_setAngularVel(lua_State* L)
{
	MOAI_LUA_SETUP(Character, "U")
	
	float angle = state.GetValue<float>(2, 0.0f);
	self->SetAngularVelocity(angle);

	return 0;
}
	