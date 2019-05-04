//
//  AndNode.cpp
//
//  Created by 何锦龙 on 2019/5/1.
//  Copyright © 2019年 何锦龙. All rights reserved.
//

#include "Proposition/PCTLTree.hpp"

namespace pctl {
    void AndNode::solve(MCs* mcs) {
        leftNode -> solve(mcs);
        rightNode -> solve(mcs);
        for (MCState* state : leftNode -> getStates()) {
            if (rightNode -> getStates().count(state) == 1) {
                states.insert(state);
            }
        }
    }
};

