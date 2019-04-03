#include "GridNode.h"

USVec2D CGridNode::GetNodeLocation() const
{
    //Get the corner of the screen
    USVec2D topLeftEdge(-(MAP_COLUMNS / 2)* GRID_SIZE, -(MAP_ROWS / 2)* GRID_SIZE);
    
    return USVec2D(topLeftEdge.mX + GRID_SIZE * mColumn + GRID_SIZE * 0.5,
                   topLeftEdge.mY + GRID_SIZE * mRow    + GRID_SIZE * 0.5);
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
   const CGridNode* gridNeighbour = static_cast<const CGridNode*>(neighbour);
   //To make the movement more realistic, we make diagonals with more cost (sqrt(2)) than straights (1)
   return gridNeighbour->mCost * GetNodeLocation().Dist(gridNeighbour->GetNodeLocation()/GRID_SIZE);
}

void CGridNode::DrawDebug() const
{
    MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get();
    
    gfxDevice.SetPointSize(1.0f);
    USVec2D nodeCenter = GetNodeLocation();
    gfxDevice.SetPenColor(WHITE);
    gfxDevice.SetPenWidth(1.0f);
    //MOAIDraw::DrawRectOutline(GRID_RECT(nodeCenter));
    DrawFill(nodeCenter);
}

void CGridNode::SetNeighbours(const vector<CNode*>& map, const uint16_t & mapSize)
{
    if (mCost != C_OBSTACLE) {
        //left neighbour
        uint16_t neighbourIndex = mIndex - 1;
        AddNeighbour(map, mapSize, neighbourIndex, SAME_ROW);

        //right neighbour
        neighbourIndex = mIndex + 1;
        AddNeighbour(map, mapSize, neighbourIndex, SAME_ROW);

        //left down neighbour
        neighbourIndex = mIndex - 1 + MAP_COLUMNS;
        AddNeighbour(map, mapSize, neighbourIndex, DOWN_ROW);
        //down neighbour
        ++neighbourIndex;
        AddNeighbour(map, mapSize, neighbourIndex, DOWN_ROW);
        //right down neighbour
        ++neighbourIndex;
        AddNeighbour(map, mapSize, neighbourIndex, DOWN_ROW);

        //right up neighbour
        neighbourIndex = mIndex + 1 - MAP_COLUMNS;
        AddNeighbour(map, mapSize, neighbourIndex, UP_ROW);
        //up neighbour
        --neighbourIndex;
        AddNeighbour(map, mapSize, neighbourIndex, UP_ROW);
        //left up neighbour
        --neighbourIndex;
        AddNeighbour(map, mapSize, neighbourIndex, UP_ROW);
    }
}

void CGridNode::SetIndex(const uint16_t & index)
{
    mIndex = index;
    //int / int gives you truncated int
    mRow = mIndex / MAP_COLUMNS;
    // And the remainder gives us the column
    mColumn = mIndex % MAP_COLUMNS;
}

bool CGridNode::IsLocationInside(const USVec2D & location) const
{
    USVec2D nodeCenter = GetNodeLocation();
    bool ret =  signbit(abs(location.mX - nodeCenter.mX) - abs(GRID_SIZE * 0.5)) && signbit(abs(location.mY - nodeCenter.mY) - abs(GRID_SIZE * 0.5));
   
    return ret;
}

void CGridNode::DrawFill(const  USVec2D& nodeCenter) const
{
    MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get();
    if(bIsEndNode)
    {
        gfxDevice.SetPenColor(YELLOW);
    }
    else
    {
        if (mCost == C_NORMAL)
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
        else if (mCost == C_OBSTACLE)
        {
            gfxDevice.SetPenColor(RED);
        }
        else
        {
            gfxDevice.SetPenColor(GREEN);
        }
    }
    //MOAIDraw::DrawRectFill(GRID_RECT(nodeCenter));
    MOAIDraw::DrawRectOutline(GRID_RECT(nodeCenter));

}

bool CGridNode::AddNeighbour(const vector<CNode*>& map, const uint16_t & mapSize, const uint16_t& neighbourIndex, const uint8_t& neighbourPosition)
{
    if (!IsValidIndex(neighbourIndex, mapSize))
    {
        return false;
    }
    CGridNode* neighbour = static_cast<CGridNode*>(map.at(neighbourIndex));
    switch (neighbourPosition)
    {
    case SAME_ROW:
        if (neighbour->mRow != mRow)
        {
            return false;
        }
        break;
    case UP_ROW:
        if (neighbour->mRow >= mRow)
        {
            return false;
        }
        break;
    case DOWN_ROW:
        if (neighbour->mRow <= mRow)
        {
            return false;
        }
        break;
    default:
        break;
    }
    if(neighbour->mCost != C_OBSTACLE)
    {
        mNeighbours.push_back(neighbour);
        return true;
    }
    return false;
}
