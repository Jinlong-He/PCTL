//
//  NegNode.cpp
//
//  Created by 何锦龙 on 2019/5/1.
//  Copyright © 2019年 何锦龙. All rights reserved.
//

#include "Proposition/PCTLTree.hpp"

namespace pctl {
    void NegNode::solve(MCs* mcs) {
        childNode -> solve(mcs);
        for (MCState* state : mcs -> getStates()) {
            if (childNode-> getStates().count(state) == 0) {
                states.insert(state);
            }
        }
    }
};

