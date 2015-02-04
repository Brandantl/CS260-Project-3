/* 
 * File:   stock.hpp
 * Author: root
 *
 * Created on November 9, 2014, 2:05 AM
 */
#ifdef _MSC_VER // Disables Microsofts Cross-platform restriction warning. 
#define _CRT_SECURE_NO_WARNINGS
#endif

#ifndef STOCK_HPP
#define	STOCK_HPP
#include <string.h>

class stock {
public:
    stock();
    stock(const stock& obj);
    virtual ~stock();

    void setTickersymbol(const char * _tickerSymbol);
    void setFundName(const char * _fundName);
    void setValue(const float _value);
    void setDate(const char * _date);
    void setYear(const float _year);


    char * getTickersymbol() const;
    char * getFundName() const;
    float getValue() const;
    char * getDate() const;
    float getYear() const;

    bool operator==(const stock& obj) const;
    const stock& operator=(const stock& obj);
     bool operator<(const stock& obj) const;
private:
    char * tickerSymbol;
    char * fundName;
    float value;
    char * date;
    float year;
};

#endif	/* STOCK_HPP */