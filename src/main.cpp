#include "MCs/MCs.hpp"
#include "Proposition/PCTLTree.hpp"
using namespace pctl;

ID MCState::counter = 1;
ID Node::counter = 1;
int main() {
    MCs msc;
    MCState* start = msc.mkState();
    MCState* try_ = msc.mkState();
    MCState* delivered = msc.mkState();
    MCState* lost = msc.mkState();

    start -> addTrans(try_, 1);
    try_ -> addTrans(delivered, 0.9);
    delivered -> addTrans(start, 1);
    try_ -> addTrans(lost, 0.1);
    lost -> addTrans(try_, 1);

    AP* ap = new AP();
    delivered -> addAP(ap);

    PCTLTree tree;
    PNode* pnode = new PNode(1,1,1,1);
    FinallyNode* fnode = new FinallyNode();
    pnode -> setChildNode(fnode);
    APNode* apnode = new APNode(ap);
    fnode -> setChildNode(apnode);
    tree.setRoot(pnode);
    tree.solve(&msc);

    delete ap;

    return 0;
}
