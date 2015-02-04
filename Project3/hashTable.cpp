/* 
 * File:   hashTable.cpp
 * Author: root
 * 
 * Created on November 9, 2014, 2:06 AM
 */
#include "hashTable.hpp"

hashTable::hashTable() {
    stockList = new linkList[CAPACITY];
}

hashTable::hashTable(const hashTable& orig) {
    CAPACITY = orig.getCapacity();
    stockList = new linkList[CAPACITY];
    for (int i = 0; i < CAPACITY; i++) {
        stockList[i] = orig.stockList[i];
    }
}

hashTable::~hashTable() {
    // DELETE ALL DATA IN THE ARRAY
    if (CAPACITY > 0) {
        for (int i = 0; i < CAPACITY; i++) {
            if (stockList[i].getLength() > 0) {
                stockList[i].~linkList();
            }
        }
        // DELETE THE ARRAY!
        if (stockList) {
            delete [] stockList;
        }
    }
}

void hashTable::add(const stock& aStock) {
    int index = this->sdbm(aStock.getTickersymbol());
    stockList[index].insert(aStock);
}

bool hashTable::remove(char * tickerSymbol) {
    int index = this->sdbm(tickerSymbol);
    stockList[index].remove(tickerSymbol);
	return true;
}

bool hashTable::modify(char * tickerSymbol, float newNetAssetVal, char * newDate, float newDateReturn) {
    int index = this->sdbm(tickerSymbol);
    stock tmp;
    tmp.setTickersymbol(tickerSymbol);
    tmp.setDate(newDate);
    tmp.setValue(newNetAssetVal);
    tmp.setYear(newDateReturn);
    stockList[index].update(tmp);
	return true;
}

bool hashTable::retrieve(char * tickerSymbol) {
    int index = this->sdbm(tickerSymbol);
    for (int i = 0; i < CAPACITY; i++) {
        stockList[i].retrieve(tickerSymbol);
    }
	return true;
}

void hashTable::display() {
    for (int i = 0; i < CAPACITY; i++) {
        cout << "BLOCK " << i << ": " << endl << stockList[i] << endl; 
    }
}

void hashTable::monitor() {
    cout << "Starting Block Dump:" << endl;
    for (int i = 0; i < CAPACITY; i++) {
        cout << "BLOCK " << i << ": " << stockList[i].getLength() << endl;
    }
}

int hashTable::getCapacity() const {
    return this->CAPACITY;
}

int hashTable::sdbm(const char * tickerSymbol) const {
    unsigned long hash = 0;
    int c;

    while (c = *tickerSymbol++) {
        hash = c + (hash << 6) + (hash << 16) - hash;
    }
    hash = hash % CAPACITY;
    return hash;
}

const hashTable& hashTable::operator=(const hashTable& obj) {
    this->~hashTable();
    CAPACITY = obj.getCapacity();
    stockList = new linkList[CAPACITY];
    for (int i = 0; i < CAPACITY; i++) {
       stock * tmp = obj.stockList[i].retrievedata();
       for (int idx = 0; idx < obj.getCapacity(); idx++) {
           this->add(tmp[idx]);
       }
       delete [] tmp;
    }
	return *this;
}

void hashTable::SaveToDisk(char * filename) {
    ofstream launchCodesFile;
    launchCodesFile.open(filename, ios::trunc); // Truncate those codes, do not want spies stealing them.   
    for (int i = 0; i < CAPACITY; i++) {
        if (stockList[i].getLength() > 0) {
            stock * data = stockList[i].retrievedata();

            for (int idx = 0; idx < stockList[i].getLength(); idx++) {
                launchCodesFile << data[idx].getDate();
                launchCodesFile << ",";
                launchCodesFile << data[idx].getFundName();
                launchCodesFile << ",";
                launchCodesFile << data[idx].getTickersymbol();
                launchCodesFile << ",";
                launchCodesFile << data[idx].getValue();
                launchCodesFile << ",";
                launchCodesFile << data[idx].getYear() << endl;
            }
            delete [] data;
        }
    }
    launchCodesFile.close();
}

void hashTable::ReadFromDisk(char * filename) {
    ifstream codes(filename);
    while (codes) {
        string s;
        if (!getline(codes, s)) break;
        istringstream ss(s);
        while (ss) {
            stock obj;
            string s;
            if (!getline(ss, s, ',')) break;
            obj.setDate(s.c_str());
            if (!getline(ss, s, ',')) break;
            obj.setFundName(s.c_str());
            if (!getline(ss, s, ',')) break;
            obj.setTickersymbol((s.c_str()));
            if (!getline(ss, s, ',')) break;
            obj.setValue((float) atof(s.c_str()));
            if (!getline(ss, s, ',')) break;
            obj.setYear((float) atof(s.c_str()));
            this->add(obj);
        }
    }
}