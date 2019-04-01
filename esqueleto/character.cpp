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

	
	AddSteeringBehavior(new CPathSteering(this));
	AddSteeringBehavior(new CAvoidanceSteering(this,2.5f));

}

void Character::OnStop()
{
	for(CSteering* Steer: steeringBehaviors)
	{
		delete Steer;
	}
	steeringBehaviors.empty();
}

void Character::OnUpdate(float step)
{
	USVec2D LinearAcceleration(0.f,0.f);
	float AngularAcceleration = 0.f;

	for(CSteering* steering: steeringBehaviors)
	{
		steering->GetSteering(&mParams, LinearAcceleration, AngularAcceleration);
	}
	SCALEVECTOR(LinearAcceleration, mParams.max_acceleration);
	SCALEFLOAT(AngularAcceleration, mParams.max_angular_acceleration);

	SetLinearVelocity	(GetLinearVelocity()  + LinearAcceleration * step);
	SetAngularVelocity	(GetAngularVelocity() + AngularAcceleration * step);

	SCALEVECTOR(mLinearVelocity, mParams.max_velocity);
	SCALEFLOAT(mAngularVelocity, mParams.max_angular_velocity);
	
	SetLoc(GetLoc() + GetLinearVelocity()  * step);
	SetRot(GetRot() + GetAngularVelocity() * step);
	
	cout << "Current Velocity: " << mLinearVelocity.Length() << " || Current Acceleration: " << LinearAcceleration.Length() << endl;
	cout << "Current Angular Velocity: " << mAngularVelocity << " || Current Angular Acceleration: " << AngularAcceleration << endl;

}

void Character::DrawDebug()
{
	MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get();
	gfxDevice.SetPenColor(RED);
	//gfxDevice.SetPenWidth(1.f);
	MOAIDraw::DrawPoint(mParams.targetPosition);
	for (CSteering* steering : steeringBehaviors)
	{
		steering->DrawDebug();
	}
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
	