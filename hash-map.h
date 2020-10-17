#include <iostream>
using namespace std;
/**
 * Hash map used throughout this
 * software
 */
template<typename T, typename K>
class HashMap {

    int hash(string key);
    int hash(int key);

    void add(T key, K value);
    void remove(T key);
    void clear();
    
    K get(T key);

    private:
        int len;
        array<int, len> val;
};