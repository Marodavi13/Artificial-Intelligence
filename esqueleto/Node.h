#pragma once
#include <stdafx.h>


class CNode
{
public:
	CNode() {}
	~CNode() {}

    static const CNode* GetNodeFromLocation(const USVec2D& location, const std::vector<CNode*>& nodes);


	virtual USVec2D			GetNodeLocation		()						const = 0;
	virtual const CNode*	GetNextNeighbour	(const CNode* previousNeighbour)				const = 0;
	virtual float			GetCostToNeightbour	(const CNode* neighbour, USVec2D startLocation = USVec2D(0.f,0.f))	const = 0;
	virtual void			DrawDebug			()												const = 0;
private:
    virtual bool			IsLocationInside	(const USVec2D& location)						const = 0;

};