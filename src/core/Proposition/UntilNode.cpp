//
//  UntilNode.cpp
//
//  Created by 何锦龙 on 2019/5/1.
//  Copyright © 2019年 何锦龙. All rights reserved.
//

#include "Proposition/PCTLTree.hpp"

namespace pctl {
    void UntilNode::solve(MCs* mcs) {
        leftNode -> solve(mcs);
        rightNode -> solve(mcs);
        MCStates& C = leftNode -> getStates();
        MCStates& B = rightNode -> getStates();
        MatrixXd m, mid;
        VectorXd v, res;
        MCStateVec stateVec;
        MCStates S0, S1;
        mcs -> getSqMatrixAndVec(C, B, m, v, stateVec, S0, S1);
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

