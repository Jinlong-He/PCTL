//
//  MCs.cpp
//
//  Created by 何锦龙 on 2019/5/1.
//  Copyright © 2019年 何锦龙. All rights reserved.
//

#include "MCs/MCs.hpp"

namespace pctl {
    MCState* MCs::mkState() {
        MCState* state = new MCState();
        states.insert(state);
        return state;
    }

    MCState* MCs::mkInitialState() {
        MCState* state = new MCState();
        initialStates.insert(state);
        return state;
    }

    void MCs::getNotBStates(MCStates& B, MCStateVec& stateVec) {
        MCStates works, newWorks, visited;
        works.insert(B.begin(), B.end());
        visited.insert(B.begin(), B.end());
        while (works.size() > 0) {
            newWorks.clear();
            for (MCState* state : works) {
                for (auto& mapPair : state -> getRTransMap()) {
                    if (mapPair.second == 0) continue;
                    MCState* newState = mapPair.first;
                    if (visited.insert(newState).second) {
                        newWorks.insert(newState);
                        if (B.count(newState) == 0) {
                            stateVec.push_back(newState);
                        }
                    }
                }
            }
            works.clear();
            if (newWorks.size() > 0) {
                works.insert(newWorks.begin(), newWorks.end());
            }
        }
    }

    void MCs::getNotS0States(MCStates& C, MCStates& B, MCStates& res) {
        MCStates works, newWorks, visited;
        works.insert(B.begin(), B.end());
        visited.insert(B.begin(), B.end());
        while(works.size() > 0) {
            newWorks.clear();
            for (MCState* state : works) {
                for (auto& mapPair : state -> getRTransMap()) {
                    if (mapPair.second == 0) continue;
                    MCState* newState = mapPair.first;
                    if (visited.insert(newState).second) {
                        if (C.count(newState) == 1) {
                            newWorks.insert(newState);
                            res.insert(newState);
                        }
                    }
                }
            }
            works.clear();
            if (newWorks.size() > 0) {
                works.insert(newWorks.begin(), newWorks.end());
            }
        }
    }

    void MCs::getNotS1States(MCStates& C, MCStates& B, MCStates& badStates) {
        MCStates goodStates, works, newWorks, visited;
        goodStates.insert(C.begin(), C.end());
        goodStates.insert(B.begin(), B.end());
        for (MCState* state : C) {
            for (auto& mapPair : state -> getTransMap()) {
                MCState* newState = mapPair.first;
                P p = mapPair.second;
                if (goodStates.count(newState) == 0 && p > 0) {
                    badStates.insert(state);
                }
            }
        }
        works.insert(badStates.begin(), badStates.end());
        visited.insert(badStates.begin(), badStates.end());
        while (works.size() > 0) {
            newWorks.clear();
            for (MCState* state : works) {
                for (auto& mapPair : state -> getRTransMap()) {
                    if (mapPair.second == 0) continue;
                    MCState* newState = mapPair.first;
                    if (visited.insert(newState).second) {
                        newWorks.insert(newState);
                        if (C.count(newState) == 1) {
                            badStates.insert(newState);
                        }
                    }
                }
            }
            works.clear();
            if (newWorks.size() > 0) {
                works.insert(newWorks.begin(), newWorks.end());
            }
        }
    }

    void MCs::getSqStates(MCStates& C, MCStates& B, MCStateVec& sq, MCStates& s1States, MCStates& s0States) {
        MCStates notS0States, sqStates;
        getNotS0States(C, B, notS0States);
        getNotS1States(notS0States, B, sqStates);
        for (MCState* state : states) {
            if (notS0States.count(state) == 0 && B.count(state) == 0) {
                s0States.insert(state);
            }
        }
        for (MCState* state : notS0States) {
            if (sqStates.count(state) == 0) {
                s1States.insert(state);
            }
        }
        s1States.insert(B.begin(), B.end());
        for (MCState* state : sqStates) {
            sq.push_back(state);
        }
    }

    void MCs::getMatrix(const MCStateVec& stateVec, MatrixXd& m) {
        ID n = stateVec.size();
        for (ID i = 0; i < n; i++) {
            for (ID j = 0; j < n; j++) {
                TransMap& transMap = stateVec[i] -> getTransMap();
                if (transMap.count(stateVec[j]) == 0) {
                    m(i, j) = 0;
                } else {
                    m(i, j) = transMap[stateVec[j]];
                }
            }
        }
    }

    void MCs::getVector(const MCStateVec& stateVec, MCStates& stateSet, VectorXd& v) {
        ID n = stateVec.size();
        for (ID i = 0; i < n; i ++) {
            TransMap& transMap = stateVec[i] -> getTransMap();
            P p = 0;
            for (MCState* state : stateSet) {
                if (transMap.count(state) > 0)
                    p += transMap[state];
            }
            v[i] = p;
        }
    }

    void MCs::getNotBMatrixAndVec(MCStates& B, MatrixXd& m, VectorXd& v, MCStateVec& stateVec) {
        getNotBStates(B, stateVec);
        ID n = stateVec.size();
        m.resize(n,n);
        v.resize(n);
        getMatrix(stateVec, m);
        getVector(stateVec, B, v);
    }

    void MCs::getSqMatrixAndVec(MCStates& C, MCStates& B, MatrixXd& m, VectorXd& v, MCStateVec& stateVec, MCStates& S1, MCStates& S0) {
        getSqStates(C, B, stateVec, S1, S0);
        ID n = stateVec.size();
        m.resize(n,n);
        v.resize(n);
        getMatrix(stateVec, m);
        getVector(stateVec, S1, v);
    }

};

