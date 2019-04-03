#pragma once


#include <moaicore/MOAIEntity2D.h>
#include <params.h>

class CSeekSteering;
class CSteering;
class CPathSteering;


class Character: public MOAIEntity2D
{
public:
    DECL_LUA_FACTORY(Character)
protected:
	virtual void OnStart();
	virtual void OnStop();
	virtual void OnUpdate(float step);
public:
	virtual void DrawDebug();

	Character();
	~Character();
	
	void SetLinearVelocity(const USVec2D& NewVelocity)	{ mLinearVelocity  = NewVelocity; }
	void SetAngularVelocity(const float& angle)			{ mAngularVelocity = angle;}

	USVec2D GetLinearVelocity()		const { return mLinearVelocity;}
	float GetAngularVelocity()		const { return mAngularVelocity;}
	float GetMaxAcceleration()		const { return mParams.max_acceleration; }
	float GetMaxSpeed()				const { return mParams.max_velocity; }
	Params* GetParams()					  { return &mParams; }

	void AddSteeringBehavior(CSteering* steering) { steeringBehaviors.push_back(steering); }

private:
	USVec2D			mLinearVelocity;
	float			mAngularVelocity;
	Params			mParams;
	vector<CSteering*> steeringBehaviors;

	// Lua configuration
public:
	virtual void RegisterLuaFuncs(MOAILuaState& state);
private:
	static int _setLinearVel(lua_State* L);
	static int _setAngularVel(lua_State* L);
};

