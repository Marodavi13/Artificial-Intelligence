#include "PathSteering.h"
#include "SeekSteering.h"
#include "character.h"
#include <tinyxml.h>
using namespace std;
CPathSteering::CPathSteering()
{
	mSeek = new CSeekSteering();
	
}

CPathSteering::CPathSteering(Character * character, const float& weight): CSteering(character, weight)
{
	
	mSeek = new CSeekSteering(character,weight);
}

CPathSteering::~CPathSteering()
{
	delete mSeek;
}

void CPathSteering::GetSteering(Params * params, USVec2D & outLinearAcceleration, float & outAngularAcceleration)
{
    if (mCharacter->mNumberOfPathPoints > 0) 
    {
        mCharacterLocation = mCharacter->GetLoc();

        SetClosestPointInPath();
        SetTargetLocation(params);

        mSeek->GetSteering(params, outLinearAcceleration, outAngularAcceleration);
    }
}

void CPathSteering::DrawDebug() const
{
    if (mCharacter->mNumberOfPathPoints > 0)
    {
        MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get();
        gfxDevice.SetPenColor(1.0f, 1.0f, 1.0f, 1.f);
        for (uint8_t i = 0; i < mCharacter->mNumberOfPathPoints - 1; ++i)
        {
            MOAIDraw::DrawLine(mCharacter->mPath[i], mCharacter->mPath[i + 1]);
        }
        mSeek->DrawDebug();
    }
}

void CPathSteering::SetTargetLocation(Params* params) const
{
	USVec2D lastPoint = mCharacter->mPath.back();
	float totalAhead = 0.f;
	size_t indexSegment = mClosestSegment;
	USVec2D startSegment = mClosestPoint;
	USVec2D endSegment = mCharacter->mPath[indexSegment + 1];
	float	segmentLength = (endSegment - startSegment).LengthSquared();

	while(totalAhead + segmentLength < pow(params->look_ahead,2.f))
	{
		++indexSegment;
		if(indexSegment+1 < mCharacter->mNumberOfPathPoints)
		{
			totalAhead += segmentLength;
			startSegment = mCharacter->mPath[indexSegment];
			endSegment = mCharacter->mPath[indexSegment + 1];
			segmentLength = (endSegment - startSegment).LengthSquared();
		}
		else
		{
			break;
		}
	}

	if (totalAhead + segmentLength >= pow(params->look_ahead, 2.f)) {
		USVec2D segmentDir = endSegment - startSegment;
		segmentDir.NormSafe();
		params->target_position = startSegment + segmentDir * (params->look_ahead - Sqrt(totalAhead));
	}
}

USVec2D CPathSteering::GetClosestPointInSegment(const USVec2D & start, const USVec2D & end)
{
	//Vector that indicates the direction of the segment
	USVec2D segmentVector = end - start;
	segmentVector.NormSafe();

	//Vector that indicates the player position from the start of the segment
	USVec2D vector = mCharacterLocation - start;
	float projection = vector.Dot(segmentVector);

	//if the projection is bigger than the segment i have passed it
	//As vector isn't used anymore, i use it for the closest point
	if(!IsVectorBiggerThan(end-start,projection))
	{
		vector = end;
	}
	//if is negative i am behind the start
	else if(projection < 0)
	{
		vector = start;
	}
	else
	{
		vector = start + segmentVector * projection;
	}

	return vector;

}

void CPathSteering::SetClosestPointInPath()
{
	float minDistance = 999999999999999.f;
	uint8_t CurrentIndex = 0;
    for (uint8_t i = 0; i < mCharacter->mNumberOfPathPoints - 1; ++i)
    {
            USVec2D closestPoint = GetClosestPointInSegment(mCharacter->mPath[i], mCharacter->mPath[i + 1]);
            float currentDistance = (closestPoint - mCharacterLocation).Length();
            if (currentDistance < minDistance)
            {
                minDistance = currentDistance;
                mClosestSegment = i;
                mClosestPoint = closestPoint;
            }
    }
}
