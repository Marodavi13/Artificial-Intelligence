#pragma once
#include <moaicore/MOAIEntity2D.h>
#include "Node.h"
class Character;

struct CPathNode
{
    CPathNode(): CPathNode(nullptr) {}
    CPathNode(const CNode* node, const CNode* parent = nullptr, float currentscore = 0.f, float totalscore = 0.f) :mNode(node), mParent(parent), mCurrentScore(currentscore), mTotalScore(totalscore) {};
    ~CPathNode() {}

    const CNode* mNode;
    const CNode* mParent;
    float mCurrentScore;
    float mTotalScore;
};

class Pathfinder : public virtual MOAIEntity2D
{
public:
    DECL_LUA_FACTORY(Pathfinder)
public:


    Pathfinder();
    ~Pathfinder();

    void SetStartPosition(float x, float y) { 
        mStartPosition = USVec2D(x, y);/* UpdatePath(); */}
    void SetEndPosition(float x, float y) { mEndPosition = USVec2D(x, y); if (mEndNode) mEndNode->bIsEndNode = false; mEndNode = CNode::GetNodeFromLocation(mEndPosition, mMap); mEndNode->bIsEndNode = true; UpdatePath(); }
    const USVec2D& GetStartPosition() const { return mStartPosition; }
    const USVec2D& GetEndPosition() const { return mEndPosition; }


    virtual void DrawDebug();
private:
    bool ReadGrid(const string* filename);
    void UpdatePath();
    CPathNode* GetNodeWithMinCost();
private:
    USVec2D mStartPosition;
    USVec2D mEndPosition;
    CNode*  mEndNode;
    //All nodes
    vector<CNode*> mMap;
    //Nodes to travel from
    map<const CNode*, CPathNode*> mOpenMap;
    //Nodes visited with neighbours visited
    map<const CNode*, CPathNode*> mClosedMap;
    Character*                    mCharacter;

    // Lua configuration

public:
    virtual void RegisterLuaFuncs(MOAILuaState& state);
private:
    static int _setCharacter(lua_State* L);
    static int _setStartPosition(lua_State* L);
    static int _setEndPosition(lua_State* L);
};


