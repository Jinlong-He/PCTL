//
//  PCTLTree.hpp
//
//  Created by 何锦龙 on 2019/5/1.
//  Copyright © 2019年 何锦龙. All rights reserved.
//

#ifndef PCTLTree_hpp
#define PCTLTree_hpp

#include "AP.hpp"
#include "../MCs/MCs.hpp"

namespace pctl {
    class StateNode;
    typedef unordered_map<MCState*, P> PVec;

    class Internal {
    private:
        P left;
        P right;
        bool le;
        bool re;
    public:
        Internal() {}
        Internal(P lp, bool l, P rp, bool r) : left(lp), right(rp), le(l), re(r) {}
        bool contains(P p) {
            if (p == left && le) return true;
            if (p == right && re) return true;
            if (left < p & p < right) return true;
            return false;
        }
    };


    class Node {
    protected:
        static ID counter;
        ID id;
        Node() : id(counter++) {
        }
    public:
        ID getID() {
            return id;
        }
    };

    class StateNode : public Node {
    protected:
        MCStates states;
    public:
        StateNode() : Node() {
        }

        virtual ~StateNode() {}

        virtual void solve(MCs* mcs) = 0;

        MCStates& getStates() {
            return states;
        }
    };

    class PathNode : public Node {
    protected:
        PVec pVec;
    public:
        PathNode() : Node() {
        }

        virtual ~PathNode() {}

        virtual void solve(MCs* msc) = 0;

        PVec& getPVec() {
            return pVec;
        }

    };

    class APNode : public StateNode {
    private:
        AP* ap;
    public:
        APNode() : StateNode(), ap(nullptr) {
        }

        APNode(AP* a) : StateNode(), ap(a) {
        }

        void solve(MCs* mcs);
    };

    class NegNode : public StateNode {
    private:
        StateNode* childNode;
    public:
        NegNode() : StateNode(), childNode(nullptr) {
        }

        ~NegNode() {
            delete childNode;
        }

        void solve(MCs* mcs);

        void setChildNode(StateNode* stateNode) {
            childNode = stateNode;
        }
    };

    class AndNode : public StateNode {
    private:
        StateNode* leftNode;
        StateNode* rightNode;
    public:
        AndNode() : StateNode(), leftNode(nullptr), rightNode(nullptr) {
        }

        ~AndNode() {
            delete leftNode;
            delete rightNode;
        }

        void solve(MCs* mcs);

        void setLeftNode(StateNode* stateNode) {
            leftNode = stateNode;
        }

        void setRightNode(StateNode* stateNode) {
            rightNode = stateNode;
        }
    };

    class OrNode : public StateNode {
    private:
        StateNode* leftNode;
        StateNode* rightNode;
    public:
        OrNode() : StateNode(), leftNode(nullptr), rightNode(nullptr) {
        }

        ~OrNode() {
            delete leftNode;
            delete rightNode;
        }

        void solve(MCs* mcs);

        void setLeftNode(StateNode* stateNode) {
            leftNode = stateNode;
        }

        void setRightNode(StateNode* stateNode) {
            rightNode = stateNode;
        }
    };

    class PNode : public StateNode {
    private:
        PathNode* childNode;
        Internal J;
    public:
        PNode() : StateNode(), childNode(nullptr) {
        }

        ~PNode() {
            delete childNode;
        }

        PNode(P left, bool le, P right, bool re) : StateNode(), childNode(nullptr), J(left, le, right, re) {}

        void solve(MCs* mcs);

        void setChildNode(PathNode* stateNode) {
            childNode = stateNode;
        }
    };

    class UntilNode : public PathNode {
    private:
        StateNode* leftNode;
        StateNode* rightNode;
        ID step;
    public:
        UntilNode() : PathNode(), leftNode(nullptr), rightNode(nullptr), step(0) {
        }

        UntilNode(ID k) : PathNode(), leftNode(nullptr), rightNode(nullptr), step(k) {
        }

        ~UntilNode() {
            delete leftNode;
            delete rightNode;
        }

        void setLeftNode(StateNode* stateNode) {
            leftNode = stateNode;
        }

        void setRightNode(StateNode* stateNode) {
            rightNode = stateNode;
        }

        void solve(MCs* mcs);
    };

    class FinallyNode : public PathNode {
    private:
        StateNode* childNode;
        ID step;
    public:
        FinallyNode() : PathNode(), childNode(nullptr), step(0){
        }

        FinallyNode(ID k) : PathNode(), childNode(nullptr), step(k){
        }

        ~FinallyNode() {
            delete childNode;
        }

        void setChildNode(StateNode* stateNode) {
            childNode = stateNode;
        }

        void solve(MCs* mcs);
    };

    class NextNode : public PathNode {
    private:
        StateNode* childNode;
    public:
        NextNode() : PathNode(), childNode(nullptr) {
        }

        ~NextNode() {
            delete childNode;
        }

        void setChildNode(StateNode* stateNode) {
            childNode = stateNode;
        }

        void solve(MCs* mcs);
    };

    class PCTLTree {
    private:
        StateNode* root;
    public:
        PCTLTree() : root(nullptr) {}

        ~PCTLTree() {
            delete root;
        }

        void setRoot(StateNode* r) {
            root = r;
        }

        void solve(MCs* mcs) {
            root -> solve(mcs);
            for (MCState* state : root -> getStates()) {
                cout << state -> getID() << endl;
            }
        }

    };
};


#endif /* PCTLTree_hpp */
