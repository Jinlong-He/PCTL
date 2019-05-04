//
//  FinallyNode.cpp
//
//  Created by 何锦龙 on 2019/5/1.
//  Copyright © 2019年 何锦龙. All rights reserved.
//

#include "Proposition/PCTLTree.hpp"

namespace pctl {
    void FinallyNode::solve(MCs* mcs) {
        childNode -> solve(mcs);
        MCStates& B = childNode -> getStates();
        MatrixXd m, mid;
        VectorXd v, res;
        MCStateVec stateVec;
        mcs -> getNotBMatrixAndVec(B, m, v, stateVec);
        ID n = stateVec.size();
        mid = MatrixXd::Identity(n, n);
        if (step == 0) {
            res = ((mid - m).inverse()) * v;
        } else {
            res = VectorXd::Zero(n);
            for (ID i = 0; i < step; i++) {
                res = m * res + v;
            }
        }
        for (ID i = 0; i < stateVec.size(); i++) {
            pVec[stateVec[i]] = res(i);
        }
    }
};

