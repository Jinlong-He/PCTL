//
//  MCs.hpp
//
//  Created by 何锦龙 on 2019/5/1.
//  Copyright © 2019年 何锦龙. All rights reserved.
//

#ifndef MCs_hpp
#define MCs_hpp

#include "MCState.hpp"
#include <vector>

namespace pctl {
    typedef vector<MCState*> MCStateVec;

    class MCs {
    private:
        MCStates states;
        MCStates initialStates;
    public:
        ~MCs() {
            for (MCState* state : states) {
                delete state;
            }
        }

        MCStates& getStates() {
            return states;
        }

        MCStates& getInitialStates(){
            return initialStates;
        }

        MCState* mkState();
        MCState* mkInitialState();

        void getNotBStates(MCStates& B, MCStateVec& stateVec);
        void getSqStates(MCStates& C, MCStates& B, MCStateVec& sq, MCStates& s1States, MCStates& s0States);

        void getNotS0States(MCStates& C, MCStates& B, MCStates& res);
        void getNotS1States(MCStates& C, MCStates& B, MCStates& badStates);

        void getMatrix(const MCStateVec& stateVec, MatrixXd& m);
        void getVector(const MCStateVec& stateVec, MCStates& stateSet, VectorXd& v);

        void getNotBMatrixAndVec(MCStates& B, MatrixXd& m, VectorXd& v, MCStateVec& stateVec);
        void getSqMatrixAndVec(MCStates& C, MCStates& B, MatrixXd& m, VectorXd& v, MCStateVec& stateVec, MCStates& S1, MCStates& S0);
    };
}

#endif /* MCs_hpp */
