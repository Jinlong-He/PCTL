//
//  MCState.hpp
//
//  Created by 何锦龙 on 2019/5/1.
//  Copyright © 2019年 何锦龙. All rights reserved.
//

#ifndef MCState_hpp
#define MCState_hpp
#include <unordered_map>
#include <unordered_set>
#include <iostream>
#include <Eigen/Dense>
#include "../Proposition/AP.hpp"
using namespace std;
using namespace Eigen;

namespace pctl {
    class MCState;
    typedef double P;
    typedef size_t ID;
    typedef unordered_map<MCState*, P> TransMap;
    typedef unordered_set<MCState*> MCStates;
    typedef unordered_set<AP*> APs;

    class MCState {
    private:
        TransMap transMap;
        TransMap rTransMap;
        APs aps;

    public:
        static ID counter;
        ID id;
        MCState() : id(counter++) {
        }

        ID getID() {
            return id;
        }

        TransMap& getTransMap() {
            return transMap;
        }

        TransMap& getRTransMap() {
            return rTransMap;
        }

        APs& getAPs() {
            return aps;
        }

        void addTrans(MCState* state, P p);

        void addAP(AP* ap);
    };
}

#endif /* MCState_hpp */
