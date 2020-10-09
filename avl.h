#include <vector>

template<typename Value = int>
struct Node {
    Value val;
    int BalanceFactor;
};


template<typename Value = int>
struct AVL {

    void insert(Value val);
    void del(Val val);
    bool searh(Val val);

    void bulkInsert(Value val[]);
    void bulkDelete(Value val[]);

    private:
        vector<Node<Value>> nodes;      
};