#include "Node.h"

CNode * CNode::GetNodeFromLocation(const USVec2D & location, const vector<CNode*>& nodes)
{
    for(CNode* node : nodes)
    {
        if(node->IsLocationInside(location))
        {
            return node;
        }
    }
    return nullptr;
}
