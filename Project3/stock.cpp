/* 
 * File:   stock.cpp
 * Author: root
 * 
 * Created on November 9, 2014, 2:06 AM
 */

#include "stock.hpp"

stock::stock() {
    this->year = 0;
    this->value = 0;
    this->fundName = NULL;
    this->tickerSymbol = NULL;
    this->date = NULL;
}

stock::stock(const stock& obj) {
	this->year = 0;
	this->value = 0;
	this->fundName = NULL;
	this->tickerSymbol = NULL;
	this->date = NULL;
    this->setYear(obj.getYear());
    this->setValue(obj.getValue());
    this->setTickersymbol(obj.getTickersymbol());
    this->setFundName(obj.getFundName());
    this->setDate(obj.getDate());
}

stock::~stock() {
    if (this->tickerSymbol) {
        delete [] this->tickerSymbol;
    }
    if (this->fundName) {
        delete [] this->fundName;
    }
    if (this->date) {
        delete [] this->date;
    }
}

void stock::setTickersymbol(const char * _tickerSymbol) {
    if (this->tickerSymbol != NULL) {
        delete [] this->tickerSymbol;
    }
    this->tickerSymbol = new char[strlen(_tickerSymbol) + 1];
    strcpy(this->tickerSymbol, _tickerSymbol);
}

void stock::setFundName(const char * _fundName) {
    if (this->fundName != NULL) {
        delete [] this->fundName;
    }
    this->fundName = new char[strlen(_fundName) + 1];
    strcpy(this->fundName, _fundName);
}

void stock::setValue(const float _value) {
    this->value = _value;
}

void stock::setDate(const char * _date) {
    if (this->date != NULL) {
        delete [] this->date;
    }
    this->date = new char[strlen(_date) + 1];
    strcpy(this->date, _date);
}

void stock::setYear(float _year) {
    this->year = _year;
}

char * stock::getTickersymbol() const {
    return this->tickerSymbol;
}

char * stock::getFundName() const {
    return this->fundName;
}

float stock::getValue() const {
    return this->value;
}

char * stock::getDate() const {
    return this->date;
}

float stock::getYear() const {
    return this->year;
}

bool stock::operator==(const stock& obj) const {
    if (strcmp(obj.getTickersymbol(), this->tickerSymbol) == 0) {
        return true;
    }
    return false;
}

const stock& stock::operator=(const stock& obj) {
    if (this == &obj) {
        return *this;
    } else {
        // Clean up 
        if (this->tickerSymbol) {
            delete [] this->tickerSymbol;
        }
        if (this->fundName) {
            delete [] this->fundName;
        }
        if (this->date) {
            delete [] this->date;
        }
        this->year = 0;
        this->value = 0;
        //===============================
        this->setYear(obj.getYear());
        this->setValue(obj.getValue());
        this->setTickersymbol(obj.getTickersymbol());
        this->setFundName(obj.getFundName());
        this->setDate(obj.getDate());
        return *this;
    }
}

bool stock::operator<(const stock& obj) const {
	if (strcmp(obj.getTickersymbol(), this->tickerSymbol) < 0) {
		return true;
	}
	return false;
}