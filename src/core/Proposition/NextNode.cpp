//
//  NextNode.cpp
//
//  Created by 何锦龙 on 2019/5/1.
//  Copyright © 2019年 何锦龙. All rights reserved.
//

#include "Proposition/PCTLTree.hpp"

namespace pctl {
    void NextNode::solve(MCs* mcs) {
        childNode -> solve(mcs);
        for (MCState* state : mcs -> getStates()) {
            P p = 0;
            for (auto& mapPair : state -> getTransMap()) {
                if (childNode -> getStates().count(mapPair.first) == 1) {
                    p += mapPair.second;
                }
            }
            pVec[state] = p;
        }
    }
};

