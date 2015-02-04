/* 
 * File:   LinkList.hpp
 * Author: root
 *
 * Created on November 9, 2014, 3:05 AM
 */

#ifndef LINKLIST_HPP
#define	LINKLIST_HPP
#include "stock.hpp"
#include <assert.h>
#include <iostream>
#include <iomanip>
using namespace std;

class linkList {
public:
    linkList(void);
    linkList(const linkList &obj);
    ~linkList();

    bool insert(const stock& obj);
    bool update(const stock& obj);
    bool remove(char * symbol);
    bool exists(char * tickerSymbol);
    int getLength(void);
    stock* retrieve(char * const symbol) const;
    stock* retrievedata() const;

    const linkList& operator=(const linkList& obj);
    friend ostream& operator<<(ostream&, const linkList&);
private:

    struct node {
        stock item;
        node * nextBySymbol;
    };

    node * headBySymbol;
    int size;
};
#endif	/* LINKLIST_HPP */