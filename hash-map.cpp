#include <iostream>
using namespace std;
/**
 * Hash map used throughout this
 * software
 */
// template<typename T, typename K>

// template<typename K, typename V>
// struct Pair {
//     key: K;
//     value: V;
// };

template<typename K, typename T>
struct Node {
    key: K;
    value: T;
    next: &Node;
};

// class KeyValLinkedList {

// };


template<typename T, typename K>
class HashMap {

    HashMap(int _len) {
        len = _len;

    };

    // Generic string hash, but noting that
    // credit (https://computinglife.wordpress.com/2008/11/20/why-do-hash-functions-use-prime-numbers/)
    // the http:// is going to be universal over
    // most/all urls we choose to skip it
    int hash(string key) {
        int h = 1;
        for (int i = 6; i < key.length(); i++) {
            h = h*31 + key[i];
        };
        return h;
    };

    // If the hash is an int we just use that
    int hash(int key) {
        return key;
    };
    
    // Returns the pointer to that starting node
    // in the linked list corresponding to the given
    // key
    Node &start(T key) {
        return val[hash(key) % len];
    };

    void add(T key, K value) {
        Node ptr = start(key);
        // Checking the pointer is non null
        while (ptr) {
            // Key already exists in the linked list
            if (ptr.key == key) {
                ptr.value = value;
                return;
            };
            ptr = ptr.next;
        };
        ptr = {
            key : key,
            value : value
        };
    };

    void remove(T key) {
        Node ptr = start(key);
        while (ptr) {
            if (ptr.key == key) {
                
            };
        };
    };

    void clear();
    
    K get(T key) {
        Node ptr = start(key);
        while (ptr) {
            if (ptr.key == key) {
                return ptr.value;
            };
            ptr = ptr.next;
        };
    };

    private:
        int len;
        array<int, len> val;
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