#include <iostream>
#include <array>
using namespace std;
/**
 * Hash map used throughout this
 * software
 */
// template<typename T, typename K>

// template<typename K, typename V>
// struct Pair {
//     K key;
//     V value;
// };

template <typename T, typename K>
struct Node
{
    Node(T key, K value){
        this->key = key;
        this->value = value;
    };
    K key;
    T value;
    Node<T, K> *next;
};

// typedef struct Node Node;

// class KeyValLinkedList {

// };

// template <typename T, typename K>
// class HashMap
// {
// public:
// HashMap(int _len)
// {
//     len = _len;
//     Node<T, K> val[_len];
// };

//     // Generic string hash, but noting that
//     // credit (https://computinglife.wordpress.com/2008/11/20/why-do-hash-functions-use-prime-numbers/)
//     // the http:// is going to be universal over
//     // most/all urls we choose to skip it
// int hash(string key)
// {
//     int h = 1;
//     for (int i = 6; i < key.length(); i++)
//     {
//         h = h * 31 + key[i];
//     };
//     return h;
// };

//     // If the hash is an int we just use that
// int hash(int key)
// {
//     return key;
// };

//     // Returns the pointer to that starting node
//     // in the linked list corresponding to the given
//     // key
// Node<T, K> &start(T key)
// {
//     return val[hash(key) % len];
// };

// void add(T key, K value)
// {
//     Node<T, K> ptr = start(key);
//     // Checking the pointer is non null
//     while (ptr != NULL)
//     {
//         // Key already exists in the linked list
//         if (ptr.key == key)
//         {
//             ptr.value = value;
//             return;
//         };
//         ptr = ptr.next;
//     };
//     Node<T, K> x = {
//         key : key,
//         value : value
//     };
//     ptr = &x;
// };
//     // Delete the thing at the pointer value?
//     void remove(T key)
//     {
//         Node<T, K> ptr = start(key);
//         while (ptr != NULL)
//         {
//             if (ptr.key == key)
//             {
//                 ptr = ptr.next;
//             };
//         };
//     };
//     // Delete the thing at the pointer value rather
//     // than just setting null?
//     void clear()
//     {
//         for (Node<T, K> ptr : val)
//         {
//             ptr = nullptr;
//         };
//     };

// K get(T key)
// {
//     Node<T, K> ptr = start(key);
//     while (ptr != NULL)
//     {
//         if (ptr.key == key)
//         {
//             return ptr.value;
//         };
//         ptr = ptr.next;
//     };
// };

// private:
//     int len;
//     Node<T, K> val[0];
// };

// template<typename T>
// struct Test
// {
//     T s;
// };

template <typename T, typename K>
struct Map
{

    Map(int len)
    {
        this->len = len;
        cout << len << endl;
        this->val = (Node<T, K> **) calloc(len, sizeof(int));
    };

    K get(T key)
    {
        Node<T, K> *ptr = this->start(key);

        // cout << ptr->next << endl;
        while (ptr != NULL)
        {
            if (ptr->key == key)
            {
                return ptr->value;
            };
            ptr = ptr->next;
        };
        cout << "Invalid key used in hash" << endl;
        throw 20;
    };

    void add(T key, K value)
    {
        Node<T, K> *ptr = this->start(key);
        
        
        // Node<T, K> *ptr = (this->start)(key);
        // cout << ptr << endl;
        // cout << (ptr == NULL) << endl;
        // cout << (ptr == NULL) << endl;
        // cout << (ptr == NULL) << endl;
        // cout << ((this->val)[0] == NULL) << endl;
        // // cout << (ptr == (*void)) << endl;
        // while (ptr == NULL) {
        //     // If key already exists we just override it
        //     // if (ptr->key == key) {
        //     //     ptr->value = value;
        //     // };
        //     // ptr = ptr->next;

        // Node<T, K> x = new Node<T, K>(key, value);
        // Checking the pointer is non null
        while (ptr != NULL)
        {
            // Key already exists in the linked list
            cout << "IN LOOP" << endl;
            if (ptr->key == key)
            {
                ptr->value = value;
                return;
            };
            ptr = ptr->next;
        };
        cout << "about to add pointer" << endl;
        *ptr = *new Node<T, K>(key, value);
        cout << "after adding pointer" << endl;
        // &ptr = x;
    };

private:
    int hash(string key)
    {
        int h = 1;
        for (int i = 6; i < key.length(); i++)
        {
            h = h * 31 + key[i];
        };
        return h;
    };

    int hash(int key)
    {
        return key;
    };

    Node<T, K> *start(T key)
    {
        cout << "hash" << hash(key) % (this->len) << " "; 
        return this->val[hash(key) % (this->len)];
    };

    int len;
    Node<T, K> **val;
};

int main()
{
    Map<string, string> map(10);
    // map.get("http://example.org/person5");
    map.add("http://example.org/person1", "p1");
    cout << 11 << endl;
    map.get("http://example.org/person1");
    cout << 111 << endl;
    map.get("http://example.org/person5");
    

    // Node<string, string> x;
    // Node<string, string> y;
    // x.key = "K1";
    // x.value = "V1";
    // x.next = &y;
    // y.key = "K2";
    // y.value = "V2";

    // cout << x.key << endl;
    // cout << x.value << endl;
    // cout << x.next->key << endl;
    // cout << x.next->value << endl;

    // Test<bool> x;
    // x.s = false;
    // return 0;

    // HashMap<string, string> map(10);
    // map.add("Hello", "booo");
    // cout << map.get("Hello") << endl;
    return 0;
};

// class HashMap {

// // Generic string hash, but noting that
// // credit (https://computinglife.wordpress.com/2008/11/20/why-do-hash-functions-use-prime-numbers/)
// // the http:// is going to be universal over
// // most/all urls we choose to skip it
// int hash(string key) {
//     int h = 1;
//     for (int i = 6; i < key.length(); i++) {
//         h = h*31 + key[i];
//     };
//     return h;
// };

// // If the hash is an int we just use that
// int hash(int key) {
//     return key;
// };

//     //
//     K get(T key) {

//     };

//     void add(T key, K value) {

//     };

//     remove() {

//     };

//     clear() {

//     };

//     private:
//         int len;
//         array<int, len> val;
// };