#include "AvoidanceSteering.h"
#include "character.h"
#include <tinyxml.h>
CAvoidanceSteering::CAvoidanceSteering()
{
}

CAvoidanceSteering::CAvoidanceSteering(Character * character, const float& weight): CSteering(character,weight)
{
	SetObstacles("obstacles.xml");
}

CAvoidanceSteering::~CAvoidanceSteering()
{
}

void CAvoidanceSteering::GetSteering(Params * params, USVec2D & outLinearAcceleration, float & outAngularAcceleration)
{
	mCharacterLocation = mCharacter->GetLoc();
	mLinearAcceleration = USVec2D(0.f, 0.f);
	//calculate desired velocity to avoid each obstacle
	for(USVec3D obstacle: mObstacles)
	{
		CalculateAvoidance(obstacle, params);
	}
	outLinearAcceleration += mLinearAcceleration;
}

void CAvoidanceSteering::DrawDebug()
{
	MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get();
	gfxDevice.SetPenColor(WHITE);
	for(USVec3D obstacle: mObstacles)
	{
		MOAIDraw::DrawEllipseFill(obstacle.mX, obstacle.mY, obstacle.mZ, obstacle.mZ, 32);
	}
	gfxDevice.SetPenColor(RED);
	MOAIDraw::DrawLine(mCharacterLocation, mCharacterLocation + mLinearAcceleration);
	gfxDevice.SetPenColor(GREEN);
	gfxDevice.SetPenColor(BLUE);
	gfxDevice.SetPointSize(10.f);
	MOAIDraw::DrawPoint(mClosestPointToObstacle);
	//MOAIDraw::DrawEllipseFill(mCharacterLocation.mX, mCharacterLocation.mY,mCharacter->GetParams()->char_radius, mCharacter->GetParams()->char_radius,32);

}

bool CAvoidanceSteering::SetObstacles(string filename)
{
	TiXmlDocument doc(filename);
	if (!doc.LoadFile())
	{
		cout << "Couldn't read params from " << filename << endl;
		return false;
	}

	TiXmlHandle hDoc(&doc);

	TiXmlElement* pElem;
	pElem = hDoc.FirstChildElement().Element();
	if (!pElem)
	{
		cout << "Invalid format for " << filename << endl;
		return false;
	}

	TiXmlHandle hRoot(pElem);
	TiXmlHandle hObstacles= hRoot.FirstChildElement("obstacles");

	TiXmlElement* obstacleElem = hObstacles.FirstChild().Element();
	for (obstacleElem; obstacleElem; obstacleElem = obstacleElem->NextSiblingElement())
	{
		string obstacleName = obstacleElem->Value();
		if (!strcmp(obstacleName.c_str(), "obstacle"))
		{
			USVec3D obstacle;
			obstacleElem->Attribute("x", &obstacle.mX);
			obstacleElem->Attribute("y", &obstacle.mY);
			obstacleElem->Attribute("r", &obstacle.mZ);

			mObstacles.push_back(obstacle);
		}
	}
	mNumberOfObstacles = mObstacles.size();
	return true;

}

void CAvoidanceSteering::CalculateAvoidance(const USVec3D& obstacle, const Params* params)
{
	MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get();
	gfxDevice.SetPenWidth(50.f);
	//My avoidance acceleration
	USVec2D linearAcceleration(0.0f, 0.0f);
	//The obstacle
	USVec2D obstacleLoc(obstacle.mX, obstacle.mY);
	float obstacleRadius = obstacle.mZ;
	//Get my velocity ad lookAhead velocity
	USVec2D velocity = mCharacter->GetLinearVelocity();
	velocity.NormSafe();
	USVec2D lookAhead = velocity * params->look_ahead_avoid;
	//get the closest point to the obstacle
	USVec2D obstacleDirection = obstacleLoc - mCharacter->GetLoc();
	float projection = obstacleDirection.Dot(velocity);
	USVec2D closestPointToObstacle = mCharacterLocation + velocity * projection;
	//if the closest point is farther than the look ahead, get the look ahead
	if (pow(projection,2.f) > lookAhead.LengthSquared()) 
	{
		closestPointToObstacle = mCharacterLocation + lookAhead;
	}
	mClosestPointToObstacle = closestPointToObstacle;

	//Distance obstacle-closest point
	float distSquared = (closestPointToObstacle - obstacleLoc).LengthSquared();
	//if the obstacle is in my way and I am going to crash
 	if (projection > 0.0f && distSquared < pow(obstacleRadius+ params->char_radius,2.f))
	{
		//Calculate peneration factor
		float penetrationFactor = 1 - (Sqrt(distSquared) / (obstacleRadius + params->char_radius));
		//get the direction to avoid
		float avoidanceDirection = obstacleDirection.Cross(lookAhead);
		linearAcceleration = obstacleDirection;
		linearAcceleration.NormSafe();
		linearAcceleration = linearAcceleration * (params->max_acceleration  * penetrationFactor);
		if (signbit(avoidanceDirection)) 
		{
			linearAcceleration.Rotate90Anticlockwise();
		}
		else 
		{
			linearAcceleration.Rotate90Clockwise();
		}

	}
	mLinearAcceleration += linearAcceleration;
	
}
