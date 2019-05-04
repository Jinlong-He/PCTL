//
//  OrNode.cpp
//
//  Created by 何锦龙 on 2019/5/1.
//  Copyright © 2019年 何锦龙. All rights reserved.
//

#include "Proposition/PCTLTree.hpp"

namespace pctl {
    void OrNode::solve(MCs* mcs) {
        leftNode -> solve(mcs);
        rightNode -> solve(mcs);
        states.insert(leftNode -> getStates().begin(), leftNode -> getStates().end());
        states.insert(rightNode-> getStates().begin(), rightNode -> getStates().end());
    }
};

