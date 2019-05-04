//
//  APNode.cpp
//
//  Created by 何锦龙 on 2019/5/1.
//  Copyright © 2019年 何锦龙. All rights reserved.
//

#include "Proposition/PCTLTree.hpp"

namespace pctl {
    void APNode::solve(MCs* mcs) {
        for (MCState* state : mcs -> getStates()) {
            if (state -> getAPs().count(ap) == 1) {
                states.insert(state);
            }
        }
    }
};

