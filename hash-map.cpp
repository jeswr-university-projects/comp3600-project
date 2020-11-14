#pragma once

#include <iostream>
#include <array>
#include <vector>
#include <set>
using namespace std;
/**
 * Hash map used throughout this
 * software
 * 
 * With regards to the time complexities
 * in this file - we note that some of the 
 * operations on the vector package may be
 * amatorized. In this case we deoote the
 * amatorized complexity (which is essentially
 * average case as ~O(1)).
 */

template <typename T, typename K>
struct Pair
{
    T key;
    K value;
};

// TODO: UPDATE THE TIME COMPLEITIES TO REFLECT
// THE ACTUAL WORST CASE TIME COMPLEXITY
template <typename T, typename K>
struct Node
{
    // O(1)
    Node(T key, K value)
    {
        this->key = key;
        this->value = value;
    };

    T key;
    K value;
    Node<T, K> *next = nullptr;
};

template <typename T, typename K>
struct Map
{

    // O(len + 1)
    Map(int len = 1)
    {
        this->len = len; // O(1)
        // this->val..
        this->val.reserve(len); // O(len)
        for (int i = 0; i < len; i++)
        {
            this->val[i] = nullptr;
        };
    };

    void add(T key, K val)
    {
        // Node<T, K> *ptr = this->start(key);
        // while (ptr != nullptr)
        // {
        //     if (ptr->key == key) {};
        //     {
        //         ptr->value = val;
        //         return;
        //     };
        //     ptr = ptr->next;
        // };
        // // Node<T, K> *tmp = new Node<T, K>(key, val);
        // // node = new Node<T, K>(key, val);
        // ptr = new Node<T, K>(key, val);
        // // *ptr = &(new Node<T, K>(key, val));

        if (this->start(key) == nullptr)
        {
            // delete this->val[slot(key)];
            this->val[slot(key)] = new Node<T, K>(key, val);
            _size++;
        }
        else
        {
            Node<T, K> *ptr = this->start(key);
            while (ptr->next != nullptr && ptr->key != key)
            {
                ptr = ptr->next;
            };
            if (ptr->key == key)
            {
                ptr->value = val;
            }
            else
            {
                // delete ptr->next;
                ptr->next = new Node<T, K>(key, val);
                _size++;
            };
        };
    };

    void remove(T key)
    {
        Node<T, K> *ptr = this->start(key);
        _size--;
        if (ptr->key == key)
        {
            // O(len(key)) if key is a string, else O(1).
            this->val[slot(key)] = (ptr->next != nullptr) ? this->val[slot(key)]->next : nullptr;
        }
        else
        {
            while (ptr->next != nullptr && ptr->next->key != key)
            {
                ptr = ptr->next;
            };
            if (ptr->next != nullptr)
            {
                if (ptr->next->next != nullptr)
                {
                    Node<T, K> *x = ptr->next;
                    ptr->next = ptr->next->next;
                    // delete x;
                }
                else
                {
                    // delete ptr->next;
                    ptr->next = nullptr;
                };
            }
        };
    };

    // ~O(1)
    K get(T key)
    {
        // cout << "inside get for key " << key << endl;
        Node<T, K> *ptr = this->start(key);
        // cout << "starting pointer is" << ptr << endl;
        while (ptr != nullptr)
        {
            // cout << ptr->key << endl;
            if (ptr->key == key)
            {
                // cout << "found" << endl;
                return ptr->value;
            };
            ptr = ptr->next;
            // cout << "inside while" << endl;
        };
        // cout <<
        cout << "erroneous key " << key << endl;
        throw "Error: Key not found - ";
    };

    // ~O(1)
    bool hasKey(T key)
    {
        // cout << "has key called" << endl;
        Node<T, K> *ptr = this->start(key);
        while (ptr != nullptr)
        {
            if (ptr->key == key)
            {
                return true;
            };
            ptr = ptr->next;
        };
        return false;
    };

    // O(edges)
    bool hasValue(K value)
    {
        for (int i = 0; i < len; i++)
        {
            Node<T, K> *ptr = val[i];
            while (ptr != nullptr)
            {
                if (ptr->value == value)
                {
                    return true;
                };
            };
        };
        return false;
    };

    // Gets all values in the hash map
    vector<K> values()
    {
        vector<K> result;
        result.reserve(_size);

        for (Node<T, K> *ptr : val)
        {
            while (ptr != nullptr)
            {
                result.push_back(ptr->value);
                ptr = ptr->next;
            };
        };

        return result;
    };

    vector<Pair> getPairs()
    {
        vector<Pair> prs;
        prs.reserve(_size);

        for (Node<T, K> *ptr : val)
        {
            while (ptr != nullptr)
            {
                result.push_back({
                    key : ptr->key,
                    value : ptr->value
                });
                ptr = ptr->next;
            };
        };

        return prs;
    };

    // Finds the *first* key with
    // value that satisfies test function
    // Best O(1), avg O(edges), worst O(edges)
    K reverseLookup(T val)
    {
        for (int i = 0; i < len; i++)
        {
            Node<T, K> *ptr = val[i];
            while (ptr != nullptr)
            {
                if (ptr->value == val)
                {
                    return ptr->key;
                };
            };
        };
    };

    // O(1)
    int size()
    {
        return _size;
    };

    void print()
    {
        for (int i = 0; i < len; i++)
        {
            Node<T, K> *ptr = this->val[i];
            while (ptr != nullptr)
            {
                cout << ptr->key << " -> " << ptr->value << endl;
                ptr = ptr->next;
            };
        };
    };

private:
    int len = 1;
    int _size = 0;
    // Node<T, K>* node;
    vector<Node<T, K> *> val = vector<Node<T, K> *>(len, nullptr);

    // Generic string hash, but noting that
    // credit (https://computinglife.wordpress.com/2008/11/20/why-do-hash-functions-use-prime-numbers/)
    // the http:// is going to be universal over
    // most/all urls we choose to skip it

    // O(len(key))
    int hash(string key)
    {
        int h = 1;
        for (int i = 0; i < key.length(); i++)
        {
            h = h * 31 + key[i];
        };
        // cout << "hash is" << h << endl;
        return h;
    };

    // O(1)
    int hash(int key)
    {
        return key;
    };

    // O(len(key)) [string] | O(1) [int]
    int slot(T key)
    {
        int s = hash(key) % len;
        if (s < 0)
        {
            s += len;
        };
        return s;
    };

    // O(len(key)) [string] | O(1) [int]
    Node<T, K> *start(T key)
    {
        // cout << "the key is " << key << endl;
        // cout << "the slot is " << slot(key) << endl;
        return this->val[slot(key)];
    };
};

template <typename T, typename K>
struct ReverseLookupMap
{
    // ReverseLookupMap<T, K>()
    // {

    // };

    void add(T key, K val)
    {
        cout << "adding edge" << endl;
        cout << key << endl;
        forward.add(key, val);
        backward.add(val, key);
    };

    K get(T key)
    {
        return forward.get(key);
    };

    // ~O(1)
    T getKey(K val)
    {
        return backward.get(val);
    };

    // ~O(1)
    bool hasKey(T key)
    {
        cout << "checking if key " << key << " exists" << endl;
        return forward.hasKey(key);
    };

    // ~O(1)
    bool hasVal(K val)
    {
        return backward.hasKey(val);
    };

    // O(1)
    int size()
    {
        return backward.size();
    };

    void print()
    {
        cout << "Forward mappings:" << endl;
        forward.print();
        cout << "Backward mappings" << endl;
        backward.print();
    };

private:
    Map<T, K> forward = Map<T, K>();
    Map<K, T> backward = Map<K, T>();
};

// int main()
// {
//     ReverseLookupMap<string, string> x;
//     x.add("x", "y");
//     cout << x.getKey("y") << endl;
//     return 0;
// };
