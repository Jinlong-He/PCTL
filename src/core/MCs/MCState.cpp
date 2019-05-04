//
//  MCState.cpp
//
//  Created by 何锦龙 on 2019/5/1.
//  Copyright © 2019年 何锦龙. All rights reserved.
//

#include "MCs/MCState.hpp"

namespace pctl {
    void MCState::addTrans(MCState* state, P p) {
        transMap[state] = p;
        state -> getRTransMap()[this] = p;
    }

    void MCState::addAP(AP* ap) {
        aps.insert(ap);
    }
    
};

