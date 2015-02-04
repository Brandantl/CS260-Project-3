/* 
 * File:   main.cpp
 * Author: root
 *
 * Created on November 9, 2014, 2:02 AM
 */
#include "main.hpp"

int main(int argc, char** argv) {
    database.ReadFromDisk("launchcodes");

    char command = 'a';
    displayMenu();
    command = getCommand();
    while (command != 'q') {
        executeCmd(command);
        displayMenu();
        command = getCommand();
    }

    database.SaveToDisk("launchcodes");
    return 0;
}

void displayMenu() {
    cout << "\nImplemented by: Brandan Lasley" << endl;
    cout << "\nWelcome to CS Stock Management System! " << endl;
    cout << "\ta> add a stock" << endl
            << "\tr> remove a stock" << endl
            << "\td> Debug Block Count" << endl
            << "\tl> Debug Block printout" << endl
            << "\tq> quit the application" << endl << endl;
}

char getCommand() {
    char cmd;
    cout << "Please enter your choice (a, r, m, d, l or q):";
    cin >> cmd;
    cin.ignore(100, '\n');
    return tolower(cmd);
}

void executeCmd(char command) {
    char date[MAX_LEN];
    char FundName[MAX_LEN];
    char Ticker[MAX_LEN];
    float value;
    float year;
    stock obj;
    
    switch (command) {
        case 'a':
            getString("Date: ", date);
            getString("Fund Name: ", FundName);
            getString("Ticker: ", Ticker);
            value = getFloat("Value: ");
            year = getFloat("Year: ");
            obj.setDate(date);
            obj.setFundName(FundName);
            obj.setTickersymbol(Ticker);
            obj.setValue(value);
            obj.setYear(year);
            database.add(obj);
            break;
        case 'm':
            getString("Ticker: ", Ticker);
            getString("Date: ", date);
            value = getFloat("Value: ");
            year = getFloat("Year: ");
            database.modify(Ticker,value,date,year);
            break;
        case 'r':
            getString("Ticker: ", Ticker);
            database.remove(Ticker);
            break;
        case 'd':
            database.monitor();
            break;
        case 'l':
            database.display(); // DEBUG BLOCK
            break;
        default: cout << "illegal command!" << endl;
            break;
    }
}

void getString(char * prompt, char * input) {
    cout << prompt;
    cin.get(input, MAX_LEN, '\n');
    cin.ignore(100, '\n');
}

float getFloat(char * prompt) {
    float temp;
    cout << prompt;
    cin >> temp;
    while (!cin) {
        cin.clear();
        cin.ignore(100, '\n');
        cout << "Illegal input -- try again: ";
        cin >> temp;
    }
    cin.ignore(100, '\n');
    return temp;
}