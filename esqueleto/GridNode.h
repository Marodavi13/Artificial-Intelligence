#pragma once
#include "Node.h"

class CGridNode: public CNode
{
public:
	CGridNode()		{}
	~CGridNode()	{}
	
	virtual USVec2D	        GetNodeLocation()							const;
	virtual const CNode*	GetNextNeighbour(const CNode* previousNeighbour)					const;
	virtual float			GetCostToNeightbour(const CNode* neighbour, USVec2D startLocation = USVec2D(0.f,0.f))	const;
	virtual void			DrawDebug()															const;
private:
    virtual bool			IsLocationInside(const USVec2D& location)							const;
public:
    int8_t mCost = C_NORMAL;
    uint8_t mIndex;     
    vector<CGridNode*> mNeighbours;

private:
    void DrawFill(const USVec2D& nodeCenter) const;
};