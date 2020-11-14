// TODO: Put this back in when it is no
// longet the main file
// #pragma once

// #include "RB-tree.h"
#include <cassert>
#include <set>
// // #ifndef __GUARDED_RB_TREE
// // #define __GUARDED_RB_TREE

// // #include <vector>

// // template<typename Value = int>
// // struct Node {
// //     Value val;
// //     int BalanceFactor;
// // };

// // template<typename Value = int>
// // struct RBtree {

// //     void insert(Value val);
// //     void del(Val val);
// //     bool searh(Val val);

// //     void bulkInsert(Value val[]);
// //     void bulkDelete(Value val[]);

// //     private:
// //         void recolour();
// //         vector<Node<Value>> nodes;
// // };

// // #endif

/**
 * The following pseudocode was used for the Left and Right rotation
 * pseudocode - remainder was obtained from the notes
 * https://www.andrew.cmu.edu/user/mm6/95-771/examples/RedBlackTreeProject/dist/javadoc/redblacktreeproject/RedBlackTree.html
 */

#include <vector>
#include <limits>
#include <iostream>
#include <fstream>
using namespace std;

int NegInfinity = numeric_limits<int>::min();

enum colours
{
    Red,
    Black
};

template <typename Value = int>
struct RBNode
{
    RBNode(Value _val)
    {
        val = _val;
    };
    Value val;
    colours colour = Red;
    RBNode<Value> *left = nullptr;
    RBNode<Value> *right = nullptr;
    RBNode<Value> *parent = nullptr;
};

template <typename Value = int>
struct RBtree
{

    
    vector<Value> getHighest(int i)
    {
        return _getHighest(i, this->root);
    };
    
    void insert(Value val)
    {
        RBNode<Value> *z = new RBNode<Value>(val);
        RBNode<Value> *y = nullptr;
        RBNode<Value> *x = root;

        while (x != nullptr)
        {
            y = x;
            x = (val < (x->val)) ? (x->left) : (x->right);
        };
        z->parent = y;

        if (y == nullptr)
        {
            root = z;
        }
        else if (val < (y->val))
        {
            y->left = z;
        }
        else
        {
            y->right = z;
        };

        // if (root == nullptr)
        // {
        //     root = new RBNode<Value>(val);
        //     root->colour = Black;
        //     cout << "adding root element" << endl;
        // }
        // else
        // {
        //     // May be pointer issues here
        //     RBNode<Value> *node = root;
        //     RBNode<Value> *newNode = root;

        //     while (newNode != nullptr)
        //     {
        //         node = newNode;
        //         newNode = node->val < val ? node->right : node->left;
        //     };

        //     newNode = new RBNode<Value>(val);
        //     newNode->parent = node;

        //     if (newNode->val < node->val)
        //     {
        //         node->right = newNode;
        //     }
        //     else
        //     {
        //         node->left = newNode;
        //     };
        // return;
        this->postInsertRecolour(z);

        // if (node->val < val)
        // {
        //     node->right = new RBNode(val);
        //     newNode = node->right;
        // }
        // else
        // {
        //     node->left = new RBNode(val);
        //     newNode = node->left;
        // }
        // newNode->parent = node;
    };

    // NEED TO SOMEHOW INIIT ROOT

    vector<Value> flat()
    {
        return flatten(root);
    };

    void print()
    {
        int depth = 0;
        vector<RBNode<Value> *> layer;
        if (root != NULL)
        {
            layer.push_back(root);
        };
        // RBNode<Value> *n = root;
        while (layer.size() > 0 && depth < 4)
        {
            depth++;
            vector<RBNode<Value> *> layerTemp;
            for (RBNode<Value> *v : layer)
            {
                cout << v->val << (v->colour == Red ? "-R" : "-B") << " ";
                if (v->left != NULL)
                {
                    layerTemp.push_back(v->left);
                };
                if (v->right != NULL)
                {
                    layerTemp.push_back(v->right);
                };
            };
            layer = layerTemp;
            cout << endl;
        };
    };

    vector<Value> flatten(RBNode<Value> *n)
    {
        // RBNode<T>* n = root;
        // vector<Value> flattening(RBNode<Value> * n)
        // {
        // https://stackoverflow.com/questions/3177241/what-is-the-best-way-to-concatenate-two-vectors
        cout << "flattening" << endl;
        if (n == nullptr)
        {
            vector<Value> x;
            x.clear();
            return x;
        }
        else
        {
            cout << " - " << n->val << " - " << endl;
            vector<Value> L = flatten(n->left);
            vector<Value> R = flatten(n->right);
            L.push_back(n->val);

            vector<Value> out;
            out.insert(out.end(), L.begin(), L.end());
            out.insert(out.end(), R.begin(), R.end());

            return out;
        };
        // };
        // return flattening(root);

        // T val;
        // // vector<T> out;
        // // T last = NegInfinity;

        // while (n->right != nullptr)
        // {
        //     n = n->right;
        // };

        // val = n->val;

        // Delete(n);

        // return flattened().push_back(val);

        // while (n != nullptr)
        // {
        //     if (n->right == nullptr || n->right->val > last)
        //     {
        //         last = n->right->val;
        //         out.push_back(last);
        //     };
        // };

        // // I guess we should find a better way of handling this?
        // T last = NegInfinity;
        // // for (int i = 0; i < )
    };

private:
    // void recolour();
    vector<Value> _getHighest(int i, RBNode<Value> *node)
    {
        vector<Value> out;
        if (node->right != nullptr)
        {
            out = _getHighest(i, node->right);
        };
        
        if (out.size() < i)
        {
            out.push_back(node->val);
        };

        if (out.size() < i && node->left != nullptr)
        {
            vector<Value> rest = _getHighest(i - out.size(), node->left);
            out.insert(out.end(), rest.begin(), rest.end());
        };
        return out;
    };

    // USING NODES
    void postDeleteRecolour(RBNode<Value> *node)
    {
        while (node != root && node->colour == Black)
        {
            if (isLeftChild(node))
            {
                RBNode<Value> *w = node->parent->right;
                if (w->colour == Red)
                {
                    w->colour = Black;
                    w->parent->colour = Red;
                    RotateLeft(node);
                    w = node->parent->right;
                };

                if (w->left->colour == Black && w->right->colour == Black)
                {
                    w->colour = Red;
                    node = node->parent;
                }
                else if (w->right->colour == Black)
                {
                    w->left->colour = Black;
                    w->colour = Red;
                    RotateRight(w);
                    w = node->parent->right;
                }
                else // Double check whether this section should be else or stand alone
                {
                    w->colour = node->parent->colour;
                    node->parent->colour = Black;
                    w->right->colour = Black;
                    RotateLeft(node);
                    node = root;
                };
            }
            else
            {
                RBNode<Value> *w = node->parent->left;
                if (w->colour == Red)
                {
                    w->colour = Black;
                    w->parent->colour = Red;
                    RotateLeft(node);
                    w = node->parent->left;
                };

                if (w->right->colour == Black && w->left->colour == Black)
                {
                    w->colour = Red;
                    node = node->parent;
                }
                else if (w->left->colour == Black)
                {
                    w->right->colour = Black;
                    w->colour = Red;
                    RotateRight(w);
                    w = node->parent->left;
                }
                else // Double check whether this section should be else or stand alone
                {
                    w->colour = node->parent->colour;
                    node->parent->colour = Black;
                    w->left->colour = Black;
                    RotateLeft(node);
                    node = root;
                };
            };
        }
        node->colour = Black;
    };
    
    // COLOUR OF NULL NODE IS ALWAYS BLAKC
    void postInsertRecolour(RBNode<Value> *node)
    {
        while ((node->parent) && (node->parent->colour == Red))
        {
            if (node->parent == node->parent->parent->left)
            {
                RBNode<Value> *y = node->parent->parent->right;
                if (y->colour = Red)
                {
                    node->parent->colour = Black;
                    y->colour = Black;
                    node->parent->parent->colour = Red;
                    node = node->parent->parent;
                }
                else
                {
                    if (node == node->parent->right)
                    {
                        node = node->parent;
                        RotateLeft(node);
                    }
                    node->parent->colour = Black;
                    node->parent->parent->colour = Red;
                    RotateRight(node->parent->parent);
                };
            }
            else
            {
                RBNode<Value> *y = node->parent->parent->left;
                if ((y != nullptr) && (y->colour = Red))
                {
                    node->parent->colour = Black;
                    y->colour = Black;
                    node->parent->parent->colour = Red;
                    node = node->parent->parent;
                }
                else
                {
                    if (node == node->parent->left)
                    {
                        node = node->parent;
                        RotateRight(node);
                    }

                    node->parent->colour = Black;
                    node->parent->parent->colour = Red;
                    RotateLeft(node->parent->parent);
                };
            };
        };
        this->root->colour = Black;
        //     if (!isLeftChild())

        //         if (isLeftChild(node->parent))
        //         {
        //             if (node->parent->parent->right->colour == Red)
        //             {
        //                 node->parent->parent->colour = Red;
        //                 node->parent->parent->right->colour = Black;
        //                 node->parent->parent->left->colour = Black;
        //                 node = node->parent->parent;
        //             }
        //             else if (!isLeftChild(node))
        //             {
        //                 node = node->parent;
        //                 RotateLeft(node);
        //             }
        //             else
        //             {
        //                 node->parent->colour = Black;
        //                 node->parent->parent->colour = Red;
        //             };
        //         }
        //         else
        //         {
        //             if (node->parent->parent->left->colour == Red)
        //             {
        //                 RBNode<Value> *granparent = Parent(Parent(node));
        //                 if (granparent != nullptr)
        //                 {
        //                 };

        //                 if (LChild(granparent) != nullptr)
        //                 {
        //                 };

        //                 if (granparent != nullptr)
        //                 {
        //                     granparent->left && granparent->colour
        //                 }

        //                 node->parent->parent->left->colour = Black;
        //                 node->parent->parent->right->colour = Black;
        //                 node->parent->parent->colour = Red;
        //                 node = node->parent->parent;
        //             }
        //             else if (isLeftChild(node))
        //             {
        //                 node = node->parent;
        //                 RotateRight(node);
        //                 //Check this is in the right spot
        //                 node->parent->colour = Black;
        //                 node->parent->parent->colour = Red;
        //                 RotateLeft(node->parent->parent);
        //             };
        //         };
        //     root->colour = Black;
        // };
    };

    RBNode<Value> *root = nullptr;
    // vector<RBNode<Value>> nodes;

    RBNode<Value> *Parent(RBNode<Value> *node)
    {
        return node == nullptr ? nullptr : node->parent;
    };

    RBNode<Value> *LChild(RBNode<Value> *node)
    {
        return node == nullptr ? nullptr : node->left;
    };

    RBNode<Value> *RChild(RBNode<Value> *node)
    {
        return node == nullptr ? nullptr : node->right;
    };

    bool isLeftChild(RBNode<Value> *node)
    {
        return Parent(node) != nullptr && (Parent(node)->left == node);
    };

    RBNode<Value> *Sibling(RBNode<Value> *node)
    {
        RBNode<Value> *parent = Parent(node);
        return (LChild(parent) == node ? RChild : LChild)(parent);
    };

    void RotateLeft(RBNode<Value> *node)
    {

        assert (node->right != nullptr);
        assert (root->parent == nullptr);
        
        // RBNode<Value> *p = Parent(node);
        RBNode<Value> *y = node->right;

        node->right = y->left;
        if (y->left != nullptr)
        {
            y->left->parent = node;
        };
        y->parent = node->parent;

        if (node->parent == nullptr)
        {
            this->root = y;
        }
        else
        {
            if (node == node->parent->left)
            {
                node->parent->left = y;
            }
            else
            {
                node->parent->right = y;
            };
        };
        y->left = node;
        node->parent = y;

        // p->

        // node->right = newRight->left;
        // newRight->left = node;
        // node->parent = newRight;

        // if (node->right != nullptr)
        // {
        //     node->right->parent = node;
        // };

        // if (LChild(newLeft) == node)
        // {
        //     newLeft->left = newRight;
        // };

        // if (newLeft != nullptr)
        // {
        //     if (node == newLeft-<)
        // };

        // if (LChild(node) != nullptr)
        // {
        //     prevParent->right = LChild(node);
        //     LChild(node)->parent = prevParent;
        // };

        // if (localRoot == nullptr)
        // {
        //     root = node;
        //     node->parent = nullptr;
        // }
        // else if (LChild(localRoot) == prevParent)
        // {
        //     localRoot->left = node;
        //     node->parent = localRoot;
        // }
        // else
        // {
        //     localRoot->right = node;
        //     node->parent = localRoot;
        // };

        // node->left = prevParent;
        // prevParent->parent = node;
    };

    // TODO: DOUBLE CHECK
    void RotateRight(RBNode<Value> *node)
    {
        assert (node->left != nullptr);
        assert (root->parent == nullptr);
        
        RBNode<Value> *y = node->left;

        node->left = y->right;
        if (y->right != nullptr)
        {
            y->right->parent = node;
        };
        y->parent = node->parent;

        if (node->parent == nullptr)
        {
            root = y;
        }
        else
        {
            if (node == node->parent->left)
            {
                node->parent->left = y;
            }
            else
            {
                node->parent->right = y;
            };
        };
        y->right = node;
        node->parent = y;

        // RBNode<Value> *prevParent = Parent(node);
        // RBNode<Value> *localRoot = Parent(prevParent);

        // if (RChild(node) != nullptr)
        // {
        //     prevParent->left = RChild(node);
        //     RChild(node)->parent = prevParent;
        // };

        // if (localRoot == nullptr)
        // {
        //     root = node;
        //     node->parent = nullptr;
        // }
        // else if (RChild(localRoot) == prevParent)
        // {
        //     localRoot->right = node;
        //     node->parent = localRoot;
        // }
        // else
        // {
        //     localRoot->left = node;
        //     node->parent = localRoot;
        // };

        // node->right = prevParent;
        // prevParent->parent = node;
    };

    void LRRotate(RBNode<Value> *node)
    {
        RotateLeft(node);
        RotateRight(node);
    };

    void RLRotate(RBNode<Value> *node)
    {
        RotateRight(node);
        RotateLeft(node);
    };

    void Delete(RBNode<Value> *node)
    {
        colours oldColour = node->colour;

        if (node->left == nullptr)
        {
            if (node->right == nullptr)
            {
                // Probably wont work
                *node = nullptr;
                // maybe this will
                delete node;
            }
            else
            {
                if (isLeftChild(node))
                {
                    // Don't think this works in the case of the root
                    node->parent->left = node->right;
                }
                else
                {
                    node->parent->right = node->right;
                };
                node->right->parent = node->parent;
            };
        }
        else if (node->right == nullptr)
        {
            if (isLeftChild(node))
            {
                // Don't think this works in the case of the root
                node->parent->left = node->left;
            }
            else
            {
                node->parent->right = node->left;
            };
            node->left->parent = node->parent;
        }
        else
        {
            /* code */
        };
    };
};

int main()
{
    RBtree<int> t;
    t.insert(5);
    t.insert(1);
    t.insert(7);
    t.insert(3);
    t.insert(10);
    t.print();
    for (int i : t.flat())
    {
        cout << i << " ";
    };
    cout << endl;
    for (int i : t.getHighest(3))
    {
        cout << i << " ";
    };
    // cout << "after second insert" << endl;
    // t.insert(4);
    // vector<int> g = t.flat();
    // // int s = g[0];
    // // cout << s << endl;
    // cout << g.size() << endl;
    // for (int e : g)
    // {
    //     cout << e << " ";
    // };
    // cout << endl;
};
