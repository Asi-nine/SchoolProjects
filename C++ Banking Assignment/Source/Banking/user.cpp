/*
 * Written by: Peter Valovcik
 * Date: Oct.22, 2016
 *
 * User Class represents a user of the banking software. The user will have their name, their role (which
 * determines their permissions), a unique identifier + pin to login, and their bank accounts if they
 * are a user that would have those. Member functions are generic accessors and mutators mostly.
 *
 */

#include "user.h"
#include "account.h"

User::User()
{

}

User::User(string role){
    userType = role;
}

User::User(string role, vector<Account *> acnts){
    userType = role;
    accounts = acnts;
}

User::User(string fName, string lName, string role, vector<Account*> acnts, int id, int pin){
    firstName = fName;
    lastName = lName;
    userType = role;
    ID = id;
    PIN = pin;
    accounts = acnts;
}

string User::getFirstName(){
    return firstName;
}

void User::setFirstName(string name){
    firstName = name;
}

string User::getLastName(){
    return lastName;
}

void User::setLastName(string name){
    lastName = name;
}

string User::getUserType(){
    return userType;
}

void User::setUserType(string type){
    userType = type;
}

void User::setID(int id){
    ID = id;
}

int User::getID(){
    return ID;
}

void User::setPIN(int pin){
    PIN = pin;
}

int User::getPIN(){
    return PIN;
}


vector<Account*> User::getAccounts(){
    return accounts;
}

void User::setAccounts(vector<Account*> act){
    accounts = act;
}

void User::addAccount(Account acnt){
    accounts.push_back(&acnt);
}

int User::removeAccount(string type){
    for(int i = 0; i < accounts.size(); i++){
        string comparisonType = accounts[i]->getAccountType();
        if (comparisonType == type && accounts[i]->getBalance() == 0){
            accounts.erase(accounts.begin() + i);
            return 1; //success
        }
    }
    return 0; //failure
}

