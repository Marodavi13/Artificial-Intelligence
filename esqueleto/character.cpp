#include <stdafx.h>
#include "character.h"
#include <tinyxml.h>



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
	mSeekSteering = new CSeekSteering();
//	mSeekArrive = new CSeekArrive();
}

void Character::OnStop()
{
	delete mSeekSteering;
}

void Character::OnUpdate(float step)
{
	USVec2D velocity = GetLinearVelocity();

	USVec2D acceleration = mSeekSteering->getSteering(this, mParams);

	SetLinearVelocity(velocity.mX + acceleration.mX * step, velocity.mY + acceleration.mY * step);

	
	USVec2D position = USVec2D(GetLoc().mX, GetLoc().mY);
	position += velocity * step;
	
	SetLoc(position);
}

void Character::DrawDebug()
{
	mSeekSteering->DrawDebug();
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
	self->SetLinearVelocity(pX, pY);
	return 0;	
}

int Character::_setAngularVel(lua_State* L)
{
	MOAI_LUA_SETUP(Character, "U")
	
	float angle = state.GetValue<float>(2, 0.0f);
	self->SetAngularVelocity(angle);

	return 0;
}
	