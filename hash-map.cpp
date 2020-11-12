#include <iostream>
#include <array>
#include <vector>
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
    struct Node<T, K> *next = NULL;
};

template <typename T, typename K>
struct Map
{

    // O(len + 1)
    Map(int len = 1)
    {
        this->len = len; // O(1)
        this->val.reserve(len); // O(len)
    };

    void add(T key, K val)
    {
        // Node<T, K> *ptr = this->start(key);
        // while (ptr != NULL)
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

        if (this->start(key) == NULL)
        {
            this->val[slot(key)] = new Node<T, K>(key, val);
            _size++;
        }
        else
        {
            Node<T, K> *ptr = this->start(key);
            while (ptr->next != NULL && ptr->key != key)
            {
                ptr = ptr->next;
            };
            if (ptr->key == key)
            {
                ptr->value = val;
            }
            else
            {
                ptr->next = new Node<T, K>(key, val);
                _size++;
            };
        };
    };

    void remove(T key)
    {
        Node<T, K> *ptr = this->start(key);
        if (ptr->key == key)
        {
            // O(len(key)) if key is a string, else O(1).
            this->val[slot(key)] = (ptr->next != NULL) ? this->val[slot(key)]->next : NULL;
        }
        else
        {
            while (ptr->next != NULL && ptr->next->key != key)
            {
                ptr = ptr->next;
            };
            if (ptr->next != NULL)
            {
                if (ptr->next->next != NULL)
                {
                    ptr->next = ptr->next->next;
                }
                else
                {
                    ptr->next = NULL;
                };
            }
        };
    };

    // ~O(1)
    K get(T key)
    {
        Node<T, K> *ptr = this->start(key);
        while (ptr != NULL)
        {
            if (ptr->key == key)
            {
                return ptr->value;
            };
            ptr = ptr->next;
            // cout << "inside while" << endl;
        };
        throw "Error: Key not found";
    };

    // ~O(1)
    bool hasKey(T key)
    {
        Node<T, K> *ptr = this->start(key);
        while (ptr != NULL)
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
            while (ptr != NULL)
            {
                if (ptr->value == value)
                {
                    return true;
                };
            };
        };
        return false;
    };

    // Finds the *first* key with
    // value that satisfies test function
    // Best O(1), avg O(edges), worst O(edges)
    K reverseLookup(T val)
    {
        for (int i = 0; i < len; i++)
        {
            Node<T, K> *ptr = val[i];
            while (ptr != NULL)
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

private:
    int len = 1;
    int _size = 0;
    // Node<T, K>* node;
    vector<Node<T, K> *> val = NULL;

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
        return hash(key) % len;
    };

    // O(len(key)) [string] | O(1) [int]
    Node<T, K> *start(T key)
    {
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
