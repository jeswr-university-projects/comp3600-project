#pragma once
#include <vector>
#include <limits>
using namespace std;

int NegInfinity = numeric_limits<int>::min();

enum colour
{
    Red,
    Black
};

template <typename Value = int>
struct RBNode
{
    RBNode(Value _val){
        val = _val};
    Value val;
    colour colour = Red;
    RBNode<Value> *left, right, parent;
};

template <typename Value = int>
struct RBtree
{

    void insert(Value val);

    void insert(Value val)
    {
        if (root == nullptr)
        {
            root = new RBNode(val);
            root->colour = Black;
        }
        else
        {
            // May be pointer issues here
            RBNode<Value> *node = root;
            RBNode<Value> *newNode = root;

            while (newNode != nullptr)
            {
                node = newNode;
                newNode = node->val < val ? node->right : node->left;
            };

            newNode = new RBNode(val);
            newNode->parent = node;

            if (newNode->val < node->val)
            {
                node->right = newNode;
            }
            else
            {
                node->left = newNode;
            };

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
    };

    void del(Val val);

    void del(Val val){

    };

    bool searh(Val val);

    void bulkInsert(Value val[]);
    void bulkDelete(Value val[]);

    vector<T> flattened()
    {
        // RBNode<T>* n = root;
        vector<T> flattening(RBNode<T> * n)
        {
            // https://stackoverflow.com/questions/3177241/what-is-the-best-way-to-concatenate-two-vectors

            if (n == nullptr)
            {
                vector<T> x;
                return x;
            }
            else
            {
                vector<T> L = flattening(root->left);
                vector<T> R = flattening(root->left);
                L.push_back(n->val);

                vector<T> out;
                out.insert(out.end(), L.begin(), L.end());
                out.insert(out.end(), R.begin(), R.end());

                return out;
            };
        };
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

        return flattened().push_back(val);

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
    void recolour();

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

    void postInsertRecolour(RBNode<Value> *node)
    {
        while (node->parent->colour == Red)
        {
            if (isLeftChild(node->parent))
            {
                if (node->parent->parent->right->colour == Red)
                {
                    node->parent->parent->colour = Red;
                    node->parent->parent->right->colour = Black;
                    node->parent->parent->left->colour = Black;
                    node = node->parent->parent;
                }
                else if (!isLeftChild(node))
                {
                    node = node->parent;
                    RotateLeft(node);
                }
                else
                {
                    node->parent->colour = Black;
                    node->parent->parent->colour = Red;
                };
            }
            else
            {
                if (node->parent->parent->left->colour == Red)
                {
                    node->parent->parent->left->colour = Black;
                    node->parent->parent->right->colour = Black;
                    node->parent->parent->colour = Red;
                    node = node->parent->parent;
                }
                else if (isLeftChild(node))
                {
                    node = node->parent;
                    RotateRight(node);
                    //Check this is in the right spot
                    node->parent = Black;
                    node->parent->parent = Red;
                    RotateLeft(node->parent->parent);
                };
            };
            root->colour = Black;
        };
    };

    RBNode<Value> *root;
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
        RBNode<Value> *prevParent = Parent(node);
        RBNode<Value> *localRoot = Parent(prevParent);

        if (LChild(node) != nullptr)
        {
            prevParent->right = LChild(node);
            LChild(node)->parent = prevParent;
        };

        if (localRoot == nullptr)
        {
            root = node;
            node->parent = nullptr;
        }
        else if (LChild(localRoot) == prevParent)
        {
            localRoot->left = node;
            node->parent = localRoot;
        }
        else
        {
            localRoot->right = node;
            node->parent = localRoot;
        };

        node->left = prevParent;
        prevParent->parent = node;
    };

    // TODO: DOUBLE CHECK
    void RotateRight(RBNode<Value> *node)
    {
        RBNode<Value> *prevParent = Parent(node);
        RBNode<Value> *localRoot = Parent(prevParent);

        if (RChild(node) != nullptr)
        {
            prevParent->left = RChild(node);
            RChild(node)->parent = prevParent;
        };

        if (localRoot == nullptr)
        {
            root = node;
            node->parent = nullptr;
        }
        else if (RChild(localRoot) == prevParent)
        {
            localRoot->right = node;
            node->parent = localRoot;
        }
        else
        {
            localRoot->left = node;
            node->parent = localRoot;
        };

        node->right = prevParent;
        prevParent->parent = node;
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
        colour oldColour = node->colour;

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
