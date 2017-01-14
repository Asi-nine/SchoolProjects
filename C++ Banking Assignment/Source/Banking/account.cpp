/*
 * Written by: Peter Valovcik
 * Date: Oct.22, 2016
 *
 * Account class that represents a generic bank account. It contains the balance as a double
 * and the type of account it is as a string. The member functions should be self explanatory
 * based on their names. They are mostly generic accessors and mutators.
 *
 */

#include "account.h"

Account::Account(){

}

Account::Account(string type, double bal){
    accountType = type;
    accountBalance = bal;
}

void Account::CloseAccount(){
    accountType = "";
    accountBalance = 0;
}

void Account::setAccountType(string type){
    accountType = type;
}

string Account::getAccountType(){
    return accountType;
}

void Account::deposit(double money){
    accountBalance += money;
}

int Account::withdraw(double money){
    if(accountType == "Chequing"){     //chequing account block
        if(accountBalance < 1000 && accountBalance < money){
            return 0; // return 0 for failure due to insufficient funds
        }
        if(accountBalance >= 1000){
            if(accountBalance - money >= 1000){
                accountBalance -= money;
                return 1;// return 1 for a regular withdrawal success
            }else
            if(accountBalance < (money+2)){
                return 0;   // return 0 for failure due to insufficient funds
            }else //account is going to go under 1000 with a withdrawal
            {
                accountBalance -= (money+2);
                return 2; // return 2 when fee occurs with a withdrawal success
            }

        }
        accountBalance -= money;
        return 1; // return 1 for a regular withdrawal success

    }//end cheqing account block
     // non-cheqing block

    if(accountBalance >= money){
        accountBalance -= money;
        return 1; // return 1 for a regular withdrawal success
    }
    return 0;   // return 0 for failure due to insufficient funds

}

double Account::getBalance(){
    return accountBalance;
}

int Account::transfer(double money, Account* destination){
    if(accountBalance >= money){
        destination->accountBalance += money;
        accountBalance -= money;
        return 1; // 1 is a success
    }
    return 0; // 0 is a failure
}
