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
    void                    SetNeighbours(const vector<CNode*>& map, const uint16_t& mapSize);
    void                    SetIndex(const uint16_t& index);
private:
    virtual bool			IsLocationInside(const USVec2D& location)							const;
    void                    DrawFill(const USVec2D& nodeCenter) const;
    bool                    AddNeighbour(const vector<CNode*>& map, const uint16_t & mapSize, const uint16_t& neighbourIndex, const uint8_t& neighbourPosition);

public:
    float mCost = C_NORMAL;
    uint16_t mIndex;     
    vector<CGridNode*> mNeighbours;
    uint8_t mRow = 0;
    uint8_t mColumn = 0;
private:
   

};