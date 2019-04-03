#pragma once
#include <moaicore/MOAIEntity2D.h>
class CNode;

struct CPathNode
{
    CPathNode(): CPathNode(nullptr) {}
    CPathNode(const CNode* node) :mNode(node), mParent(nullptr), mCurrentScore(0), mTotalScore(0) {};

    const CNode* mNode;
    const CNode* mParent;
    float mCurrentScore;
    float mTotalScore;
};

class Pathfinder: public virtual MOAIEntity2D
{
public:
	DECL_LUA_FACTORY(Pathfinder)
protected:
	virtual void OnStart();
	virtual void OnStop();
	virtual void OnUpdate(float step);

	void SetGrid(string filename);
public:


	Pathfinder();
	~Pathfinder();

	void SetStartPosition(float x, float y) { m_StartPosition = USVec2D(x, y); UpdatePath();}
	void SetEndPosition(float x, float y) { m_EndPosition = USVec2D(x, y); UpdatePath();}
	const USVec2D& GetStartPosition() const { return m_StartPosition;}
	const USVec2D& GetEndPosition() const { return m_EndPosition;}

    bool PathfindStep();
    virtual void DrawDebug();
private:
	void UpdatePath();
    CPathNode* GetNodeWithMinCost();
private:
	USVec2D m_StartPosition;
	USVec2D m_EndPosition;
    vector<CNode*> mMap;
    vector<const CNode*> mPath;
    map<const CNode*, CPathNode*> mOpenMap;
    map<const CNode*, CPathNode*> mClosedMap;
    Character*                    mCharacter;

	// Lua configuration

public:
	virtual void RegisterLuaFuncs(MOAILuaState& state);
private:
	static int _setStartPosition(lua_State* L);
	static int _setEndPosition(lua_State* L);
    static int _pathfindStep(lua_State* L);
};


