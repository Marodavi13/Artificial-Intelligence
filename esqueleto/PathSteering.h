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

	void GetSteering(Params* params, USVec2D & outLinearAcceleration, float & outAngularAcceleration) override;
	void DrawDebug() const override;

	void SetTargetLocation(Params* params) const;
	USVec2D GetClosestPointInSegment(const USVec2D& start, const USVec2D& end);
	void SetClosestPointInPath();
private:

	CSeekSteering*	mSeek;
	USVec2D			mClosestPoint;
	uint8_t			mClosestSegment;
};

