//
//  PNode.cpp
//
//  Created by 何锦龙 on 2019/5/1.
//  Copyright © 2019年 何锦龙. All rights reserved.
//

#include "Proposition/PCTLTree.hpp"

namespace pctl {
    void PNode::solve(MCs* mcs) {
        childNode -> solve(mcs);
        for (auto& mapPair : childNode -> getPVec()) {
            if (J.contains(mapPair.second)) {
                states.insert(mapPair.first);
            }
        }
    }
};

