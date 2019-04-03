#include "GridNode.h"

USVec2D CGridNode::GetNodeLocation() const
{
    //int / int gives you truncated int
    int8_t row = mIndex / MAP_COLUMNS;
    // And the remainder gives us the column
    int8_t column = mIndex % MAP_COLUMNS;
    //Get te corner of the screen
    USVec2D topLeftEdge(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
    
    return USVec2D(topLeftEdge.mX + GRID_SIZE * column + GRID_SIZE / 0.5,
                   topLeftEdge.mY + GRID_SIZE * row    + GRID_SIZE / 0.5);
}

const CNode * CGridNode::GetNextNeighbour(const CNode * previousNeighbour) const
{
   const CNode * nextNeighbour = nullptr;
   if (!mNeighbours.empty())
   {
       //if is the first neighbour
       if (previousNeighbour == nullptr)
       {
           nextNeighbour = mNeighbours.front();
       }
       else
       {
            for(auto it = mNeighbours.begin(); (it+1)!=mNeighbours.end(); ++it)
            {
                //if *it is the previous neighbour *it+1 will be the next one
                if(*it == previousNeighbour)
                {
                    nextNeighbour = *(it + 1);
                    break;
                }
            }
       }
   }
   return nextNeighbour;
}

float CGridNode::GetCostToNeightbour(const CNode * neighbour, USVec2D startLocation) const
{
   const CGridNode* gridNeighbour = reinterpret_cast<const CGridNode*>(neighbour);
   return static_cast<float>(gridNeighbour->mCost) * GetNodeLocation().Dist(gridNeighbour->GetNodeLocation());
}

void CGridNode::DrawDebug() const
{
    MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get();
    gfxDevice.SetPointSize(1.0f);
    USVec2D nodeCenter = GetNodeLocation();
    gfxDevice.SetPenColor(WHITE);
    gfxDevice.SetPenWidth(1.0f);
    MOAIDraw::DrawRectOutline(GRID_RECT(nodeCenter));
    DrawFill(nodeCenter);
}

bool CGridNode::IsLocationInside(const USVec2D & location) const
{
    USVec2D nodeCenter = GetNodeLocation();
    return signbit(abs(location.mX - nodeCenter.mX) - abs(GRID_SIZE * 0.5)) && signbit(abs(location.mY - nodeCenter.mY) - abs(GRID_SIZE * 0.5));
}

void CGridNode::DrawFill(const  USVec2D& nodeCenter) const
{
    MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get();
    if(mCost == C_NORMAL)
    {
        gfxDevice.SetPenColor(WHITE);
    }
    else if (mCost == C_WATER)
    {
        gfxDevice.SetPenColor(BLUE);
    }
    else if (mCost == C_MUD)
    {
        gfxDevice.SetPenColor(BROWN);
    }
    else if(mCost == C_OBSTACLE)
    {
        gfxDevice.SetPenColor(RED);
    }
    else
    {
        gfxDevice.SetPenColor(GREEN);
    }
    MOAIDraw::DrawRectFill(GRID_RECT(nodeCenter));
}
