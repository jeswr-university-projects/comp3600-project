#ifndef __GUARDED_RB_TREE
#define __GUARDED_RB_TREE

#include <vector>

template<typename Value = int>
struct Node {
    Value val;
    int BalanceFactor;
};


template<typename Value = int>
struct RBtree {

    void insert(Value val);
    void del(Val val);
    bool searh(Val val);

    void bulkInsert(Value val[]);
    void bulkDelete(Value val[]);

    private:
        void recolour();
        vector<Node<Value>> nodes;      
};

#endif