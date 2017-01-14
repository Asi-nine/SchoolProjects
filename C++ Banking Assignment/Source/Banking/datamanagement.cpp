/*
 * Written by: Peter Valovcik
 * Date: Oct.22, 2016
 *
 * DataManagement class deals with reading and writing of data to and from flat files. It allows for the
 * storage of individual users, the bank's total data, aggregate user data, and a trace log. Member functions
 * here may not be inherently obvious, and as such have been commented.
 *
 */

#include "datamanagement.h"

DataManagement::DataManagement(){

}

/*
 * This will write a user and their information into a flatfile that is named after their unique ID
 *
 */
void DataManagement::writeUser(User* user){
    string filename = "../data/" + to_string(user->getID()) + ".dat";
    ofstream outFile;
    outFile.open(filename, ios::binary | ios::trunc);
    outFile << user->getID() <<  '\n' << user->getPIN() << '\n' << user->getUserType() << '\n' << user->getFirstName() << '\n' << user->getLastName();
    for(int i = 0; i < user->getAccounts().size(); i++){
        Account* acnt = user->getAccounts()[i];
        outFile << '\n' << acnt->getAccountType() << '\n' << acnt->getBalance();
    }
    outFile.close();
}

/*
 * Returns a User pointer based on reading a flat file with ID input.
 *
 */

User* DataManagement::readUser(int id){
    string filename = "../data/" + to_string(id) + ".dat";
    ifstream inFile;
    inFile.open(filename);
    if(inFile.is_open()){
        string fName, lName, type, uID, uPIN;
        getline(inFile, uID);
        getline(inFile, uPIN);
        getline(inFile, type);
        getline(inFile, fName);
        getline(inFile, lName);
        int userID = stoi(uID);
        int userPIN= stoi(uPIN);

        vector<Account*> userAccounts;
        string actType, balance;
        double balanceD;
        if(type == "Client"){
           // get accounts if any exist
            while(!inFile.eof()){

                getline(inFile, actType);
                getline(inFile, balance);
                balanceD = stod(balance);
                Account* acnt = new Account(actType, balanceD);
                userAccounts.push_back(acnt);

            }
        }
        User* returnUser = new User(fName, lName, type, userAccounts, userID, userPIN);
        return returnUser;
    }
    //return a user pointer to a user with no data upon failure of reading the file
    User* n = new User();
    return n;
}

/*
 * Verify a user's credentials for login. Will compare the entered ID and PIN to that
 * of the user with that ID.
 *
 */

int DataManagement::verifyUser(User* user, int id, int pin){
    if(user->getID() == 0 || user->getPIN() == 0){
        return 0; // an empty user
    }
    if(user->getID() == id && user->getPIN() == pin){
        return 1; // verified
    }
    return 0; // did not match
}

/*
 * Writes the banks data to a flat file.
 *
 */

void DataManagement::writeBank(Bank* bank){
    string filename = "../data/MegaBank.dat";
    ofstream outFile;
    outFile.open(filename, ios::binary | ios::trunc);
    outFile << bank->getBalance() <<  '\n' << bank->getUser() << '\n' << bank->getTheme() << '\n' << bank->getTracer()->getTrace() << '\n' << bank->getTracer()->getID();
}

/*
 * Reads the banks data from a flat file. Returns and empty bank if no file exists.
 *
 */

Bank* DataManagement::readBank(){
    string filename = "../data/MegaBank.dat";
    Bank* bank;
    ifstream inFile;
    inFile.open(filename);
    if(inFile.is_open()){
        string bal, user, newTheme, traS, idS;
        bool tra = false;
        getline(inFile, bal);
        getline(inFile, user);
        getline(inFile, newTheme);
        getline(inFile, traS);
        getline(inFile, idS);
        if(traS == "1"){
            tra = true;
        }
        Tracer* t = new Tracer(tra, stoi(idS));
        bank = new Bank(stod(bal), stoi(user), newTheme, t);
    }
    return bank;
}

//get current date and time (from cplusplus.com)
string DataManagement::getDateTime(){
    time_t rawtime;
    struct tm * timeinfo;
    char buffer [80];

    time (&rawtime);
    timeinfo = localtime (&rawtime);

    strftime (buffer,80,"%c",timeinfo);

    return buffer;
}

/*
 * Writes the date, time, and what a user was doing based on the log input and their id to a flat file.
 * This only is used if tracing is toggled on.
 *
 */

void DataManagement::writeToTrace(int id, string log){
    time_t rawtime;
    struct tm * timeinfo;
    char buffer [80];

    time (&rawtime);
    timeinfo = localtime (&rawtime);

    strftime (buffer,80,"%c",timeinfo);

    string filename = "../data/Trace.dat";
    ofstream outFile;
    outFile.open(filename, ios::binary | ios::app);
    // The if checks are for unique situations in the main, such as a maintenance person toggling trace on while
    // they are the target of the trace.
    if(log == "Login" || log == "Toggled Trace on." || log == "Switched Trace to self while Trace on."){
    outFile << "Trace of user with ID: " << id << '\n';
    }
    outFile << buffer << "  --->  " << log << '\n';
}

/*
 * Deletes logs and logs deletion
 */
void DataManagement::deleteTrace(int id){
    time_t rawtime;
    struct tm * timeinfo;
    char buffer [80];

    time (&rawtime);
    timeinfo = localtime (&rawtime);

    strftime (buffer,80,"%c",timeinfo);

    string filename = "Trace.dat";
    ofstream outFile;
    outFile.open(filename, ios::binary | ios::trunc);

    outFile << "Trace of user with ID: " << id << '\n';
    outFile << buffer << "  --->  " << "Deleted Trace Log." << '\n';
}



