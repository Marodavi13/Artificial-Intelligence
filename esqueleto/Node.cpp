#include "Node.h"

const CNode * CNode::GetNodeFromLocation(const USVec2D & location, const vector<CNode*>& nodes)
{
    for(const CNode* node : nodes)
    {
        if(node->GetNodeLocation().Equals(location))
        {
            return node;
        }
    }
    return nullptr;
}
