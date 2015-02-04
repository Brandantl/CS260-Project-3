/* 
 * File:   LinkList.cpp
 * Author: root
 * 
 * Created on November 9, 2014, 3:05 AM
 */

#include "linkList.hpp"

linkList::linkList() {
    size = 0;
    headBySymbol = NULL;
}

linkList::linkList(const linkList& obj) {
	headBySymbol = NULL;
    this->size = 0;
    node * curr = headBySymbol;
    while (headBySymbol) {
        curr = headBySymbol->nextBySymbol;
        delete headBySymbol;
        headBySymbol = curr;
    }
    if (!obj.headBySymbol)
        headBySymbol = NULL;
    else {
        headBySymbol = new node;
        assert(headBySymbol != NULL);
        headBySymbol->item = obj.headBySymbol->item;
        node * destNode = headBySymbol;
        node * srcNode = obj.headBySymbol->nextBySymbol;
        while (srcNode) {
            destNode->nextBySymbol = new node;
            assert(destNode->nextBySymbol);
            destNode = destNode->nextBySymbol;
            destNode->item = srcNode->item;
            srcNode = srcNode->nextBySymbol;
            this->size++;
        }
        destNode->nextBySymbol = NULL;
    }
}

linkList::~linkList() {
    if (size != 0) {
        node * curr = headBySymbol;
        while (headBySymbol) {
            curr = headBySymbol->nextBySymbol;
            delete headBySymbol;
            headBySymbol = curr;
            size--;
        }
    }
}

bool linkList::insert(const stock& obj) {
    node * prev = NULL;
    node * curr = headBySymbol;

    while (curr != NULL && curr->item < obj) {
        prev = curr;
        curr = curr->nextBySymbol;
    }

    if (curr && curr->item == obj) {
        return false;
    } else {
        // Create a new node
        node * newNode = new node;
        newNode->item = obj;
        newNode->nextBySymbol = curr;
        if (prev == NULL) {
            headBySymbol = newNode;
        } else {
            prev->nextBySymbol = newNode;
        }
        size++;
        return true;
    }
    return false;
}

bool linkList::remove(char * symbol) {
    if (size > 0) {
        node * prev = NULL;
        node * curr;
        bool found = false;

        if (size == 0) {
            return false;
        } else {
            for (curr = headBySymbol; curr; curr = curr->nextBySymbol) {
                if (strcmp(curr->item.getTickersymbol(), symbol) == 0) {
                    found = true;
                    if (!prev) {
                        headBySymbol = curr->nextBySymbol;
                    } else {
                        prev->nextBySymbol = curr->nextBySymbol;
                    }
                    break;
                }
                prev = curr;
            }

            if (found) {
                delete curr;
                size--;
                return true;
            }
        }
    }
    return false;
}

bool linkList::update(const stock& obj) {
    if (size > 0) {
        node * curr;
        for (curr = headBySymbol; curr; curr = curr->nextBySymbol) {
            if (strcmp(curr->item.getTickersymbol(), obj.getTickersymbol()) == 0) {
                curr->item.setDate(obj.getDate());
                curr->item.setValue(obj.getValue());
                curr->item.setYear(obj.getYear());
                return true;
            }
        }
    }
    return false;
}

bool linkList::exists(char * symbol) {
    if (size > 0) {
        node * curr;
        for (curr = headBySymbol; curr; curr = curr->nextBySymbol) {
            if (strcmp(curr->item.getTickersymbol(), symbol) == 0) {
                return true;
            }
        }
    }
    return false;
}

int linkList::getLength(void) {
    return this->size;
}

stock* linkList::retrieve(char * const symbol) const {
    if (size > 0) {
        node * curr;
        for (curr = headBySymbol; curr; curr = curr->nextBySymbol) {
            if (strcmp(curr->item.getTickersymbol(), symbol) == 0) {
                return &curr->item;
            }
        }
    }
    return NULL;
}

const linkList& linkList::operator=(const linkList& obj) {
    if (this == &obj)
        return *this;
    else {
        this->size = 0;
        node * curr = headBySymbol;
        while (headBySymbol) {
            curr = headBySymbol->nextBySymbol;
            delete headBySymbol;
            headBySymbol = curr;
        }
        if (!obj.headBySymbol)
            headBySymbol = NULL;
        else {
            headBySymbol = new node;
            assert(headBySymbol != NULL);
            headBySymbol->item = obj.headBySymbol->item;
            node * destNode = headBySymbol;
            node * srcNode = obj.headBySymbol->nextBySymbol;
            while (srcNode) {
                destNode->nextBySymbol = new node;
                assert(destNode->nextBySymbol);
                destNode = destNode->nextBySymbol;
                destNode->item = srcNode->item;
                srcNode = srcNode->nextBySymbol;
                this->size++;
            }
            destNode->nextBySymbol = NULL;
        }
        return *this;
    }
}

ostream& operator<<(ostream& out, const linkList& obj) {
    out << left << setw(7) << "Ticker"
            << left << setw(25) << "Fund Name"
            << left << setw(6) << "Value"
            << left << setw(5) << "Year"
            << left << setw(25) << "Date"
            << endl;

    if (obj.size > 0) {
        linkList::node * curr;
        for (curr = obj.headBySymbol; curr; curr = curr->nextBySymbol) {
            out << left << setw(7) << curr->item.getTickersymbol()
                    << left << setw(25) << curr->item.getFundName()
                    << left << setw(6) << curr->item.getValue()
                    << left << setw(5) << curr->item.getYear()
                    << left << setw(25) << curr->item.getDate()
                    << endl;
        }
    }
    return out;
}

stock* linkList::retrievedata() const {
    if (size > 0) {
        stock * tmp = new stock[this->size];
        node * curr;
        int i = 0;
        for (curr = headBySymbol; curr; curr = curr->nextBySymbol) {
            tmp[i] = curr->item;
            i++;
        }
        return tmp;
    }
    return NULL;
}