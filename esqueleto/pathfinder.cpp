#include <stdafx.h>
#include "pathfinder.h"
#include "GridNode.h"
#include "character.h"

Pathfinder::Pathfinder() : MOAIEntity2D()
{
	RTTI_BEGIN
		RTTI_EXTEND(MOAIEntity2D)
	RTTI_END
    ReadGrid(&string("grid.txt"));
    mCharacter = nullptr;
    mEndNode = nullptr;
}

Pathfinder::~Pathfinder()
{
   
}


bool Pathfinder::ReadGrid(const string * filename)
{
    ifstream file(filename->c_str(), ios::binary);
    if(!file)
    {
        return false;
    }
    string fileRow;
    uint16_t size = 0;
    for(uint8_t row = 0; row < MAP_ROWS; ++row )
    {
        getline(file, fileRow);
        for(uint8_t column = 0; column < MAP_COLUMNS; ++column)
        {
            CGridNode* node = new CGridNode();
            node->SetIndex(row * MAP_COLUMNS + column);
            switch(fileRow[column])
            {
            case NORMAL:
                node->mCost = C_NORMAL;
                break;
            case WATER:
                node->mCost = C_WATER;
                break;
            case MUD:
                node->mCost = C_MUD;
                break;
            case OBSTACLE:
                node->mCost = C_OBSTACLE;
                break;
            default:
                node->mCost = C_NORMAL;
            }
            mMap.push_back(node);
            ++size;
        }
    }
    file.close();

    for (CNode* node: mMap)
    {
        static_cast<CGridNode*>(node)->SetNeighbours(mMap,size);
    }
    return true;
}

void Pathfinder::UpdatePath()
{
   
    mOpenMap.clear();
    mClosedMap.clear();

    //get starting node
    const CNode* node = CNode::GetNodeFromLocation(mStartPosition, mMap);
    if (node && mEndNode && mCharacter != nullptr)
    {
        mCharacter->mPath.clear();
        mCharacter->mNumberOfPathPoints = 0;
        //Create the first pathnode
        mOpenMap[node] = new CPathNode(node);
        while (!mOpenMap.empty())
        {
            //Get the next node to travel from with min cost
            CPathNode* currentPathNode = GetNodeWithMinCost();
            //As we are visiting all his neighbours we erase it from openlist, and introduce it into the closed list 
            mOpenMap.erase(currentPathNode->mNode);
            mClosedMap[currentPathNode->mNode] = currentPathNode;
            if (currentPathNode->mNode == mEndNode)
            {
                break;
            }
            for (CGridNode* neighbour : static_cast<const CGridNode*>(currentPathNode->mNode)->mNeighbours)
            {
                if (mClosedMap.count(neighbour))
                {
                }
                else
                {
                    //Calculate the current cost of the path
                    float currentScore = currentPathNode->mCurrentScore + currentPathNode->mNode->GetCostToNeightbour(neighbour);
                    //add an stimation based on distance with cost 1
                    float totalScore = currentScore + neighbour->GetNodeLocation().Dist(mEndNode->GetNodeLocation());
                    CPathNode* nextPathNode = new CPathNode(neighbour, currentPathNode->mNode, currentScore, totalScore);

                    //Add it to the open map
                    if (mOpenMap.count(neighbour))
                    {
                        if (currentScore < mOpenMap.find(neighbour)->second->mCurrentScore)
                        {
                            mOpenMap[neighbour] = nextPathNode;
                        }
                    }
                    else
                    {
                        mOpenMap[neighbour] = nextPathNode;

                    }
                }
            }
        }

        //if I have reached the end
        if (mClosedMap.count(mEndNode))
        {
            const CNode* parent = mClosedMap.find(mEndNode)->second->mNode;
            while (parent)
            {
                mCharacter->mPath.insert(mCharacter->mPath.begin(), parent->GetNodeLocation());
                ++mCharacter->mNumberOfPathPoints;
                parent = mClosedMap.find(parent)->second->mParent;
            }
        }
    }
}

CPathNode * Pathfinder::GetNodeWithMinCost()
{
    const CNode* node = nullptr;
    float minCost = 99999999999999999.f;
    for(const auto& pair: mOpenMap)
    {
        if (pair.second->mTotalScore < minCost) 
        {
            minCost = pair.second->mTotalScore;
            node = pair.second->mNode;
        }
    }
    return mOpenMap[node];
}




void Pathfinder::DrawDebug()
{
    for(const CNode* node: mMap)
    {
        node->DrawDebug();
    }
}

//lua configuration ----------------------------------------------------------------//
void Pathfinder::RegisterLuaFuncs(MOAILuaState& state)
{
	MOAIEntity::RegisterLuaFuncs(state);

	luaL_Reg regTable [] = {
		{ "setStartPosition",		_setStartPosition},
		{ "setEndPosition",			_setEndPosition},
        { "setCharacter",           _setCharacter},
		{ NULL, NULL }
	};

	luaL_register(state, 0, regTable);
}

int Pathfinder::_setCharacter(lua_State * L)
{
    MOAI_LUA_SETUP(Pathfinder, "U")
    self->mCharacter = state.GetLuaObject<Character>(2, 0.f);
    return 0;
}

int Pathfinder::_setStartPosition(lua_State* L)
{
	MOAI_LUA_SETUP(Pathfinder, "U")

	float pX = state.GetValue<float>(2, 0.0f);
	float pY = state.GetValue<float>(3, 0.0f);
	self->SetStartPosition(pX, pY);
	return 0;
}

int Pathfinder::_setEndPosition(lua_State* L)
{
	MOAI_LUA_SETUP(Pathfinder, "U")

	float pX = state.GetValue<float>(2, 0.0f);
	float pY = state.GetValue<float>(3, 0.0f);
	self->SetEndPosition(pX, pY);
	return 0;
}

