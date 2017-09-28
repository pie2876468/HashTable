//
//  main.cpp
//  HashTable
//
//  Created by Jen-Feng Chang on 9/16/17.
//  Copyright © 2017 JFC. All rights reserved.
//

#include <iostream>

class HashTable {
    class HashItem {//used for storing key and value
        int key, value;
    public:
        HashItem(int k =0, int v =0) : key(k), value(v) {}
        const int& getkey() {// get key
            return key;
        }
        const int& getvalue() {//get value
            return value;
        }
    };
    int Size =0;// the size of the HashTable
    int usedSize =0;//the number of used HashItem
    HashItem **table;//the storing array
public:
    HashTable(int size) {//prelocate space
        Size = size;//set the size
        table = new HashItem *[Size]();// pre-allocated space for the given number of objects.
    }
    bool set(int key, int value) {
        int idx = key%Size;//calculate hash number
        if(table[idx]) {//if the key is used, set it null.
            table[idx]=NULL;
            usedSize--;//update the usedSize
        }
        table[idx] = new HashItem(key, value);
        usedSize++;//update the usedSize
        return true;
    }
    const int get(int key){
        int idx = key%Size;//calculate hash number
        return table[idx] ? table[idx]->getvalue() : NULL;
    }
    int Delete(int key) {
        int idx = key%Size;
        if(table[idx]) {//if the key is used, set it null.
            int res = table[idx]->getvalue();
            table[idx]=NULL;
            usedSize--;//update the usedSize
            return res;
        }
        else {//if it is not used, return NULL
            return NULL;
        }
    }
    float load() {//return the load factor (`(items in hash map)/(size of hash map)`) of the data structure
        return ((float) usedSize/(float) Size);
    }
    ~HashTable(){//destructor
        for(int i=0; i<Size; i++)
            if(table[i]) delete [] table[i];
        delete[] table;
    }
};
int main(int argc, const char * argv[]) {
    //test code
    HashTable* map = new HashTable(100);
    //size =100;
    for(int i=0; i<99; i++) map->set(i,i*10);//set 99 items
    std::cout << map->get(13) << std::endl;
    std::cout << map->get(99) << std::endl;//this idx is null, so it return null(0)
    std::cout << map->Delete(98) << std::endl;//test Delete
    std::cout << map->Delete(98) << std::endl;//this idx is null, so it return null(0)
    std::cout << map->load() << std::endl;//showthe load factor
    for(int i=0; i<98; i++) map->Delete(i);//delete all the HashItem
    std::cout << map->load() << std::endl;//it should be zero
    return 0;
}
