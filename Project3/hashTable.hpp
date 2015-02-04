/* 
 * File:   hashTable.hpp
 * Author: root
 *
 * Created on November 9, 2014, 2:05 AM
 */
#ifdef _MSC_VER // Disables Microsofts Cross-platform restriction warning. 
#define _CRT_SECURE_NO_WARNINGS
#endif

#ifndef HASHTABLE_HPP
#define	HASHTABLE_HPP
#include "stock.hpp"
#include "linkList.hpp"
#include <iostream>
#include <fstream>
#include <sstream> 
#include <stdlib.h> 
#include <string.h>
using namespace std;

class hashTable {
public:
    hashTable();
    hashTable(const hashTable& orig);
    virtual ~hashTable();
    void add(const stock& aStock);
    bool remove(char * tickerSymbol);
    bool modify(char * tickerSymbol, float newNetAssetVal, char * newDate, float newDateReturn);
    bool retrieve(char * tickerSymbol);
    void display();
    void monitor();
    int getCapacity() const;
    
    void SaveToDisk(char * filename);
    void ReadFromDisk(char * filename);

    const hashTable& operator=(const hashTable& obj);
private:
    int CAPACITY = 11;
    int top;
    linkList * stockList;
    int sdbm(const char * tickerSymbol) const;
};

#endif	/* HASHTABLE_HPP */