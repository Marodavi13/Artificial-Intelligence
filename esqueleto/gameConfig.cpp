#include <stdafx.h>
#include "gameConfig.h"

#include "character.h"
#include "pathfinder.h"
void Configure(MOAIGlobals* globals)
{
	REGISTER_LUA_CLASS(Character)
	REGISTER_LUA_CLASS(Pathfinder)

}