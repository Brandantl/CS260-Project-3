/* 
 * File:   main.hpp
 * Author: root
 *
 * Created on November 9, 2014, 2:06 AM
 */
#ifdef _MSC_VER // Disables Microsofts Cross-platform restriction warning. 
#define _CRT_SECURE_NO_WARNINGS
#endif

#ifndef MAIN_HPP
#define	MAIN_HPP
#include "hashTable.hpp"
#include <cstdlib>
using namespace std;
hashTable database;
const int MAX_LEN = 25;

void displayMenu();
char getCommand();
void executeCmd(char command);
float getFloat(char * prompt);
void getString(char * prompt, char * input);


#endif	/* MAIN_HPP */