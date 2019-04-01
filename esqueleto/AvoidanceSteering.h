#pragma once
#include "Steering.h"
class Character;
using namespace std;
class CAvoidanceSteering : public CSteering
{
public:
	CAvoidanceSteering();
	CAvoidanceSteering(Character* character, const float& weight = 1.f);

	~CAvoidanceSteering();

	virtual void GetSteering(Params* params, USVec2D &outLinearAcceleration, float &outAngularAcceleration);
	virtual void DrawDebug();
	bool SetObstacles(string filename);
private:

	USVec2D mLinearAcceleration;
	USVec2D mClosestPointToObstacle;

	vector<USVec3D> mObstacles;
	vector<int> mCollisionObstacles;
	size_t mNumberOfObstacles;
	void CalculateAvoidance(const USVec3D& obstacle, const Params* params);
};

