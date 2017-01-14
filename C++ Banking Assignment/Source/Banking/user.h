/*
 * Written by: Peter Valovcik
 * Date: Oct.22, 2016
 *
 * See the cpp file for more information.
 *
 */

#ifndef USER_H
#define USER_H
#include <iostream>
#include <fstream>
#include <vector>
#include "account.h"
using namespace std;

class User
{
private:
    string firstName;
    string lastName;
    string userType;
    int ID;
    int PIN;
    int numAccounts;
    vector<Account*> accounts;
public:
    User();

    User(string role);

    User(string role, vector<Account*> acnts);

    User(string fName, string lName, string role, vector<Account*> acnts, int id, int pin);

    string getFirstName();

    void setFirstName(string name);

    string getLastName();

    void setLastName(string name);

    string getUserType();

    void setUserType(string type);

    void setID(int id);

    int getID();

    void setPIN(int pin);

    int getPIN();

    vector<Account *> getAccounts();

    void setAccounts(vector<Account*> act);

    void addAccount(Account acnt);

    int removeAccount(string type);

    void writeUser();

    int verifyUser(int id, int pin);

    User* readUser(int id);

};

#endif // USER_H
