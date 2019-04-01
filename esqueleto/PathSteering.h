#pragma once
#include "Steering.h"

class Character;
class CSeekSteering;

using namespace std;

class CPathSteering : public CSteering
{
public:
	CPathSteering();
	CPathSteering(Character* character, const float& weight = 1.f);
	~CPathSteering();

	void GetSteering(Params* params, USVec2D & outLinearAcceleration, float & outAngularAcceleration);
	void DrawDebug();

	bool SetPath(const string& filename);
	void SetTargetLocation(Params* params);
	USVec2D GetClosestPointInSegment(const USVec2D& start, const USVec2D& end);
	void SetClosestPointInPath();
private:

	CSeekSteering*	mSeek;
	vector<USVec2D>	mPath;
	size_t			mNumberOfPathPoints;
	USVec2D			mClosestPoint;
	uint8_t			mClosestSegment;
};

