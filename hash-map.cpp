#include <iostream>
using namespace std;
/**
 * Hash map used throughout this
 * software
 */
// template<typename T, typename K>
class HashMap {

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

    //
    K get(T key) {

    };

    void add(T key, K value) {

    };

    remove() {

    };

    clear() {

    };

    private:
        int len;
        array<int, len> val;
};