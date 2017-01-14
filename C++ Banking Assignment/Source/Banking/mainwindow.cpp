/*
 * Written by: Peter Valovcik
 * Date: Oct.22, 2016
 *
 * MainWindow simulating a banking system. NOW WITH 82 goto STATEMENTS, IT'S LIKE I'M REALLY READING ASSEMBLER EDITION!
 * The mainwindow is layed out based on menu's with the menus being named. Options are within the cout's of the menu.
 * Goto was used to traverse menus, though a cleaner alternative should likely be used, ideally one from QT UI.
 * Since the goal of this project was not to spend extensive amount of time on GUI, the goto approach was used
 * since it is much easier for me to implement quickly from my stronger background with C and assemblers.
 *
 */

#include "mainwindow.h"

MainWindow::MainWindow()
{
}

//starts the main window
void MainWindow::startLoop()
{
    //Declare quite a few variables for use during the program that want a large scope (some of these could
    //be moved to a smaller scope but are here due to original implementation and refactoring not being a top priority)

    User* newUser;

    DataManagement * window = new DataManagement();

    Bank* bankTest = window->readBank();

    bool trace = bankTest->getTracer()->getTrace();
    int personTraced = bankTest->getTracer()->getID();

    bool traceLoggedIn;

    User* temp;
    vector<Account*> userActs;
    string privileges;
    int privNum;

    char ch, ch2, ch3, ch4, ch5, ch6, ch7, ch8;
    int id;
    int pin;
    double money;
do
    {
        system("clear");
        /*
         * Here is a large block for the main menu the user sees when starting the program
         */
MainMenu:
        if(bankTest->getTheme() == "Harry Potter"){
            cout << '\t' << "WELCOME TO GRINGOTTS WIZARDING BANK" << '\n';
            cout << "            _            _.,----," << '\n';
            cout << " __  _.-._ / '-.        -  ,._  \)" << '\n';
            cout << "|  `-)_   '-.   \       / < _ )/' }" << '\n';
            cout << "/__    '-.   \   '-, ___(c-(6)=(6)" << '\n';
            cout << " , `'.    `._ '.  _,'   >\    '  )" << '\n';
            cout << " :;;,,'-._   '---' (  ( '/`. -='/" << '\n';
            cout << ";:;;:;;,  '..__    ,`-.`)'- '--'" << '\n';
            cout << ";';:;;;;;'-._ /'._|   Y/   _/' \\" << '\n';
            cout << "      ''''._ F    |  _/ _.'._   `\\" << '\n';
            cout << "             L    \   \/     '._  \\" << '\n';
            cout << "      .-,-,_ |     `.  `'---,  \_ _|" << '\n';
            cout << "      //    'L    /  \,   ('--',=`)7" << '\n';
            cout << "     | `._       : _,  \  /'`-._L,_'-._" << '\n';
            cout << "     '--' '-.\__/ _L   .`'         './/" << '\n';
            cout << "                 [ (  /" << '\n';
            cout << "                  ) `{" << '\n';
            cout << "                  \__)" << '\n';
        }
        if(bankTest->getTheme() == "default"){
            cout << '\t' << "Welcome to Bank Simulator 2016!" << '\n';
        }
        if(bankTest->getTheme() == "Megaman"){
            cout << '\t' << "Welcome to MegaBank!" << '\n';
            cout << "█████████████████████████████████"<< '\n';
            cout << "█░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░█"<< '\n';
            cout << "█░░░░░░░░░░░░░░░███░░░░░░░░░░░░░█"<< '\n';
            cout << "█░░░░░░░░░░░░░███▒▒█░░░░░░░░░░░░█"<< '\n';
            cout << "█░░░░░░░░░░░░█▒▒▒█▒▒█░░░░░░░░░░░█"<< '\n';
            cout << "█░░░░░░░░░░░█▒▒▒▒▒████░░░░░░░░░░█"<< '\n';
            cout << "█░░░░░░░░░░░█▒▒▒▒▒█▒▒▒█░░░░░░░░░█"<< '\n';
            cout << "█░░░░░░░░░░█▒▒▒▒▒▒▒██▒█░░░░░░░░░█"<< '\n';
            cout << "█░░░░░░░░░░█▒▒▒░░░░▒▒░█░░░░░░░░░█"<< '\n';
            cout << "█░░░░░░░░░░█▒▒░░░██░█░█░░░░░░░░░█"<< '\n';
            cout << "█░░░░░░░░░░░█▒░░░██░█░█░░░░░░░░░█"<< '\n';
            cout << "█░░░░░░░░░░██▒░░░░░░░░█░░░░░░░░░█"<< '\n';
            cout << "█░░░░░░░░██▒▒█▒░████░███░░░░░░░░█"<< '\n';
            cout << "█░░░░░░░█▒▒▒▒▒█░░░░░█▒▒▒█░░░░░░░█"<< '\n';
            cout << "█░░░░░░░█▒▒▒▒▒▒█████▒▒▒▒█░░░░░░░█"<< '\n';
            cout << "█░░░░░░█▒▒▒▒█▒▒▒▒▒▒▒█▒▒▒▒█░░░░░░█"<< '\n';
            cout << "█░░░░░░█▒▒███▒▒▒▒▒▒▒███▒▒█░░░░░░█"<< '\n';
            cout << "█░░░░░░█▒▒▒██▒▒▒▒▒▒▒██▒▒▒█░░░░░░█"<< '\n';
            cout << "█░░░░░░█▒▒▒██▒▒▒▒▒▒▒██▒▒▒█░░░░░░█"<< '\n';
            cout << "█░░░░░░░███░█▒▒▒▒▒▒▒█▒███░░░░░░░█"<< '\n';
            cout << "█░░░░░░░░░░█▒▒▒▒▒▒▒▒▒█░░░░░░░░░░█"<< '\n';
            cout << "█░░░░░░░░░█▒▒▒▒▒█▒▒▒▒▒█░░░░░░░░░█"<< '\n';
            cout << "█░░░░░░░░██▒▒▒▒█░█▒▒▒▒██░░░░░░░░█"<< '\n';
            cout << "█░░░░░░██▒▒▒▒▒█░░░█▒▒▒▒▒██░░░░░░█"<< '\n';
            cout << "█░░░░░█▒▒▒▒▒▒▒█░░░█▒▒▒▒▒▒▒█░░░░░█"<< '\n';
            cout << "█░░░░░█████████░░░█████████░░░░░█"<< '\n';
            cout << "█░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░█"<< '\n';
            cout << "█████████████████████████████████"<< '\n';
        }

        //options upon launch
        cout << '\n' << "1. LOG IN" << '\n';
        cout << "X. EXIT" << '\n' << '\n';
        cout << "Select an option (1,x)" << '\n';
        cin>>ch;
        system("clear");
        switch(ch)
        {
        case '1':
            //get credentials
            cout << "Enter your ID:";
            cin >> id;
            system("clear");
            cout << "Enter your PIN:";
            cin >> pin;
            system("clear");
            temp = window->readUser(id);

            goto UserVerify;
        case 'x':
            goto End;
        default :
            goto MainMenu;
        }
        //verify user credentials block
UserVerify:
        //verify login
        if(window->verifyUser(temp, id, pin)){
            privileges = temp->getUserType();

            // Client
            if(privileges == "Client"){
                privNum = 1;

                if(id == personTraced && trace == true){
                    traceLoggedIn = true;
                    window->writeToTrace(personTraced, "Login");
                }

            }

            // Manager
            if(privileges == "Manager"){
                privNum = 2;

                if(id == personTraced && trace == true){
                    traceLoggedIn = true;
                    window->writeToTrace(personTraced, "Login");
                }

            }

            // Maintenance
            if(privileges == "Maintenance"){
                privNum = 3;

                if(id == personTraced && trace == true){
                    traceLoggedIn = true;
                    window->writeToTrace(personTraced, "Login");
                }
            }
        }
        // login fail
        else if(!window->verifyUser(temp, id, pin)) {
            cout << "Sorry, you have entered the wrong ID or PIN, or do not have an account." << '\n' << '\n';
            goto MainMenu;
        }

        switch(privNum){

        case 1:

            //Client main screen
MainClientMenu:
            cout << '\t' << "Welcome " << temp->getFirstName() << " " << temp->getLastName() << "!" << '\n';
            cout << "1. Withdrawal" << '\n';
            cout << "2. Deposit" << '\n';
            cout << "3. Check Balance" << '\n';
            cout << "4. Transfer" << '\n';
            cout << "5. Change PIN" << '\n';
            cout << "Z. Log Out" << '\n';
            cout << "X. Exit" << '\n' << '\n';
            cout << "Select an option (1-5,z,x)" << '\n';
            char cliMenu;
            cin>>cliMenu;
            switch(cliMenu){

            case '1':
                //Withdrawal

                system("clear");
                cout << "Enter amount to withdraw." << '\n';
                cin >> money;
WithdrawMenu:
                cout << "$" << money << " from which account?" << '\n';

                cout << '\n' << "1. Chequing" << '\n';
                cout << "2. Savings" << '\n';
                cout << "B. Back" << '\n' << '\n';
                cout << '\n' << '\n' << "Select an account (1,2,b)" << '\n';
                cin >> ch2;
                switch(ch2){

                case '1':
                    // Chequing Withdrawal
                    userActs = temp->getAccounts();
                    int withdrawalReturn1;
                    //look for account
                    for(int i = 0; i < userActs.size(); i++){
                        if(userActs[i]->getAccountType() == "Chequing"){
                            withdrawalReturn1 = userActs[i]->withdraw(money);
                        }
                    }
                    switch(withdrawalReturn1){
                    case 0:
                        // too poor or no account
                        system("clear");
                        cout << "Insufficient funds or no Chequing account." << '\n' << '\n' << '\n';
                        if(traceLoggedIn){
                            string log = "Attempted withdrawal of $" + to_string(money) + " from Chequing, but insufficient funds or no account.";
                            window->writeToTrace(personTraced, log);
                        }
                        goto MainClientMenu;
                    case 1:
                        // money withdrawn and data updated
                        system("clear");
                        cout << "$" << money << " has been withdrawn." << '\n' << '\n' << '\n';
                        window->writeUser(temp);
                        temp->setAccounts(userActs);
                        bankTest->setBalance(bankTest->getBalance()-money);
                        window->writeBank(bankTest);
                        if(traceLoggedIn){
                            string log = "Withdrawal of $" + to_string(money) + " from Chequing.";
                            window->writeToTrace(personTraced, log);
                        }
                        goto MainClientMenu;
                    case 2:
                        // fee prompt because will go below $1000 in chequing
                        cout << "This transaction will require a processing fee of $2.";
                        cout << '\n' << '\n' <<  "y = accept, anything else = decline" << '\n';
                        char fee;
                        cin >> fee;
                        if(fee == 'y'){
                            system("clear");
                            cout << '\n' << '\n' <<  "$" << money << " has been withdrawn. And a $2 fee paid." << '\n' << '\n' << '\n';
                            temp->setAccounts(userActs);
                            window->writeUser(temp);
                            temp->setAccounts(userActs);
                            bankTest->setBalance(bankTest->getBalance()-money+2);
                            window->writeBank(bankTest);
                            if(traceLoggedIn){
                                string log = "Withdrawal of $" + to_string(money) + " from Chequing and $2 fee incurred.";
                                window->writeToTrace(personTraced, log);
                            }
                        }
                        system("clear");
                        if(fee!='y'){
                            cout << '\n' << '\n' <<  "Transaction cancelled." << '\n' << '\n' << '\n';
                            if(traceLoggedIn){
                                string log = "Withdrawal of $" + to_string(money) + " from Chequing cancelled to avoid $2 fee.";
                                window->writeToTrace(personTraced, log);
                            }
                        }
                        goto MainClientMenu;
                    }
                    system("clear");
                    goto MainClientMenu;

                case '2':
                    // Savings withdrawal
                    userActs = temp->getAccounts();
                    int withdrawalReturn2;
                    // look for account
                    for(int i = 0; i < userActs.size(); i++){
                        if(userActs[i]->getAccountType() == "Savings"){
                            withdrawalReturn2 = userActs[i]->withdraw(money);
                        }
                    }
                    switch(withdrawalReturn2){
                    case 0:
                        // too poor or no account
                        system("clear");
                        cout << "Insufficient funds or no Savings account." << '\n' << '\n' << '\n';
                        if(traceLoggedIn){
                            string log = "Attempted withdrawal of $" + to_string(money) + " from Savings, but insufficient funds or no account.";
                            window->writeToTrace(personTraced, log);
                        }
                        goto MainClientMenu;
                    case 1:
                        // money withdrawn and updated data stored
                        system("clear");
                        cout << "$" << money << " has been withdrawn." << '\n' << '\n' << '\n';
                        temp->setAccounts(userActs);
                        window->writeUser(temp);
                        bankTest->setBalance(bankTest->getBalance()-money);
                        window->writeBank(bankTest);
                        if(traceLoggedIn){
                            string log = "Withdrawal of $" + to_string(money) + " from Savings.";
                            window->writeToTrace(personTraced, log);
                        }
                        goto MainClientMenu;
                    }
                    system("clear");
                    goto MainClientMenu;


                case 'b':
                    //returns
                    system("clear");
                    goto MainClientMenu;

                default:
                    system("clear");
                    goto WithdrawMenu;

                }

                system("clear");
                goto WithdrawMenu;
                /*
                 * END WITHDRAW BLOCK
                 */
            case '2':
                //deposit block
                system("clear");
                cout << "Enter amount to Deposit." << '\n';
                cin >> money;
DepositMenu:
                cout << "$" << money << " into which account?" << '\n';
                cout << '\n' << "1. Chequing" << '\n';
                cout << "2. Savings" << '\n';
                cout << "B. Back" << '\n' << '\n';
                cout << '\n' << '\n' << "Select an account (1,2,b)" << '\n';
                cin >> ch3;
                switch(ch3){

                case '1':
                    userActs = temp->getAccounts();
                    // attempt to find chequing and deposit + write data if exists
                    for(int i = 0; i < userActs.size(); i++){
                        if(userActs[i]->getAccountType() == "Chequing"){
                            system("clear");
                            userActs[i]->deposit(money);
                            cout << "$" << money << " was deposited into Chequing." << '\n' << '\n' << '\n';
                            temp->setAccounts(userActs);
                            window->writeUser(temp);
                            bankTest->setBalance(bankTest->getBalance()+money);
                            window->writeBank(bankTest);
                            if(traceLoggedIn){
                                string log = "Deposit of $" + to_string(money) + " to Chequing." + '\n';
                                window->writeToTrace(personTraced, log);
                            }
                            goto MainClientMenu;
                        }
                    }
                    //if no chequing account
                    system("clear");
                    cout << '\n' << "No Chequing account." << '\n'<< '\n';
                    if(traceLoggedIn){
                        string log = "Deposit of $" + to_string(money) + " attempted to Chequing but no account." + '\n';
                        window->writeToTrace(personTraced, log);
                    }
                    goto MainClientMenu;

                case '2':
                    //attempt to find savings account and deposit if exits
                    userActs = temp->getAccounts();
                    for(int i = 0; i < userActs.size(); i++){
                        if(userActs[i]->getAccountType() == "Savings"){
                            system("clear");
                            userActs[i]->deposit(money);
                            cout << "$" << money << " was deposited into Savings." << '\n' << '\n' << '\n';
                            temp->setAccounts(userActs);
                            window->writeUser(temp);
                            bankTest->setBalance(bankTest->getBalance()+money);
                            window->writeBank(bankTest);
                            if(traceLoggedIn){
                                string log = "Deposit of $" + to_string(money) + " to Savings.";
                                window->writeToTrace(personTraced, log);
                            }
                            goto MainClientMenu;
                        }
                    }
                    //no savings account
                    system("clear");
                    cout << '\n' << "No Savings account." << '\n'<< '\n';
                    if(traceLoggedIn){
                        string log = "Deposit of $" + to_string(money) + " attempted to Savings but no account." + '\n';
                        window->writeToTrace(personTraced, log);
                    }
                    goto MainClientMenu;

                case 'b':
                    system("clear");
                    goto MainClientMenu;

                default:
                    system("clear");
                    goto DepositMenu;

                }
                system("clear");
                goto DepositMenu;

                /*
                 * DEPOSIT END
                 */

            case '3':
                //Balance checking
                system("clear");
BalanceMenu:
                cout << '\n' << "1. Chequing" << '\n';
                cout << "2. Savings" << '\n';
                cout << "B. Back" << '\n' << '\n';
                cout << '\n' << '\n' << "Select an account to see balance for (1,2,b)" << '\n';
                cin >> ch4;
                switch(ch4){

                case '1':
                    //check for chequing existing and give balance
                    userActs = temp->getAccounts();
                    for(int i = 0; i < userActs.size(); i++){
                        if(userActs[i]->getAccountType() == "Chequing"){
                            system("clear");
                            double tempBalance = userActs[i]->getBalance();
                            cout << "$" << tempBalance << " is in your Chequing account." << '\n' << '\n' << '\n';
                            if(traceLoggedIn){
                                string log = "Viewed Chequing balance";
                                window->writeToTrace(personTraced, log);
                            }
                            goto MainClientMenu;
                        }
                    }
                    //no chequing account
                    system("clear");
                    cout << '\n' << "No chequing account." << '\n'<< '\n';
                    if(traceLoggedIn){
                        string log = "Attempted to view balance of chequing but no account." + '\n';
                        window->writeToTrace(personTraced, log);
                    }
                    goto MainClientMenu;

                case '2':
                    //check for savings existing and give balance
                    userActs = temp->getAccounts();
                    for(int i = 0; i < userActs.size(); i++){
                        if(userActs[i]->getAccountType() == "Savings"){
                            system("clear");
                            double tempBalance = userActs[i]->getBalance();
                            cout << "$" << tempBalance << " is in your Savings account." << '\n' << '\n' << '\n';
                            if(traceLoggedIn){
                                string log = "Viewed Savings balance";
                                window->writeToTrace(personTraced, log);
                            }
                            goto MainClientMenu;
                        }
                    }
                    //no savings account
                    system("clear");
                    cout << '\n' << "No Savings account." << '\n'<< '\n';
                    if(traceLoggedIn){
                        string log = "Attempted to view balance of Savings but no account." + '\n';
                        window->writeToTrace(personTraced, log);
                    }
                    goto MainClientMenu;

                case 'b':
                    //back to main menu for client

                    system("clear");
                    goto MainClientMenu;

                default:
                    system("clear");
                    goto BalanceMenu;
                }
                system("clear");
                goto BalanceMenu;
                /*
                 * BALANCE BLOCK END
                 */
            case '4':
                //Transfers
                system("clear");
                userActs = temp->getAccounts();
                // deny transfer attempt if they have 0 or 1 accounts
                if(userActs.size() < 2){
                    system("clear");
                    cout << "You don't have enough accounts for a transfer!" << '\n' <<'\n';
                    if(traceLoggedIn){
                        string log = "Attempted transfer between accounts while having 1 or 0 accounts";
                        window->writeToTrace(personTraced, log);
                    }
                    goto MainClientMenu;
                }
                cout << "Enter amount to Transfer." << '\n';
                cin >> money;
TransferMenu:
                cout << "$" << money << " into which account into which account?" << '\n';
                cout << '\n' << "1.FROM Chequing TO Savings" << '\n';
                cout << "2.FROM Savings TO Chequing" << '\n';
                cout << "B. Back" << '\n' << '\n';
                cout << '\n' << '\n' << "Select which transfer direction you would like(1,2,b)" << '\n';

                cin >> ch5;
                switch(ch5){

                case '1':
                    //find accounts
                    userActs = temp->getAccounts();
                {   Account* cheq;
                    Account* sav;
                    for(int i = 0; i < userActs.size(); i++){
                        if(userActs[i]->getAccountType() == "Chequing"){
                            cheq = userActs[i];
                        }
                        if(userActs[i]->getAccountType() == "Savings"){
                            sav = userActs[i];
                        }
                    }
                    int trans = cheq->transfer(money, sav);
                    // do the transfer and write data
                    if(trans){
                        system("clear");
                        cout << "$" << money << " was transferred from Chequing to Savings." << '\n' << '\n' << '\n';
                        for(int i = 0; i < userActs.size(); i++){
                            if(userActs[i]->getAccountType() == "Chequing"){
                                userActs[i] = cheq;
                            }
                            if(userActs[i]->getAccountType() == "Savings"){
                                userActs[i] = sav;
                            }
                        }
                        temp->setAccounts(userActs);
                        window->writeUser(temp);
                        if(traceLoggedIn){
                            string log = "Transferred $" + to_string(money) + " from Chequing to Savings.";
                            window->writeToTrace(personTraced, log);
                        }
                        goto MainClientMenu;
                    }
                    // not enough money to do the transfer
                    system("clear");
                    cout <<"Insufficient funds in your Chequing account for transfer." << '\n' << '\n' << '\n';
                    if(traceLoggedIn){
                        string log = "Attempted to transfer $" + to_string(money) + " from Chequing to Savings, but insufficient funds.";
                        window->writeToTrace(personTraced, log);
                    }
                    goto MainClientMenu;
                }
                    system("clear");
                    goto MainClientMenu;

                case '2':
                    userActs = temp->getAccounts();
                    //find accounts
                {   Account* cheq;
                    Account* sav;
                    for(int i = 0; i < userActs.size(); i++){
                        if(userActs[i]->getAccountType() == "Chequing"){
                            cheq = userActs[i];
                        }
                        if(userActs[i]->getAccountType() == "Savings"){
                            sav = userActs[i];
                        }
                    }
                    // do the transfer and save data
                    int trans = sav->transfer(money, cheq);
                    if(trans){
                        system("clear");
                        cout << "$" << money << " was transferred from Savings to Chequing." << '\n' << '\n' << '\n';
                        for(int i = 0; i < userActs.size(); i++){
                            if(userActs[i]->getAccountType() == "Chequing"){
                                userActs[i] = cheq;
                            }
                            if(userActs[i]->getAccountType() == "Savings"){
                                userActs[i] = sav;
                            }
                        }
                        temp->setAccounts(userActs);
                        window->writeUser(temp);
                        if(traceLoggedIn){
                            string log = "Transferred $" + to_string(money) + " from Savings to Chequing";
                            window->writeToTrace(personTraced, log);
                        }
                        goto MainClientMenu;
                    }
                    // not enought funds for the transfer
                    system("clear");
                    cout <<"Insufficient funds in your Savings account for transfer." << '\n' << '\n' << '\n';
                    if(traceLoggedIn){
                        string log = "Attempted to transfer $" + to_string(money) + " from Savings to Chequing, but insufficient funds.";
                        window->writeToTrace(personTraced, log);
                    }
                    goto MainClientMenu;
                }
                    system("clear");
                    goto MainClientMenu;

                case 'b':
                    //go back
                    system("clear");
                    goto MainClientMenu;

                default:
                    system("clear");
                    goto TransferMenu;
                }

                system("clear");
                goto TransferMenu;
                /*
                 * END TRANSFER BLOCK
                 */
            case '5':
            {
                //Pin Change
                //get 2 new pin entries
                system("clear");
                cout << "Please enter what you would like as you new PIN" << '\n';
                int pin1, pin2;
                cin >> pin1;
                system("clear");
                cout << "Please enter what you would like as you new PIN one more time" << '\n';
                cin >> pin2;
                system("clear");
                //reject pin change attempt if both do not match
                if(pin1 != pin2){
                    cout << "Sorry, those did not match." << '\n' << '\n';
                    if(traceLoggedIn){
                        string log = "Attempted to change PIN but failed.";
                        window->writeToTrace(personTraced, log);
                    }
                    goto MainClientMenu;
                }
                // save new pin if both match
                temp->setPIN(pin1);
                window->writeUser(temp);
                cout << "PIN changed!" << '\n' << '\n';
                if(traceLoggedIn){
                    string log = "Changed PIN.";
                    window->writeToTrace(personTraced, log);
                }
                goto MainClientMenu;

            }
                system("clear");
                goto MainClientMenu;
                /*
                 * END PIN CHANGE BLOCK
                 */
            case 'z':
                //lougout
                if(traceLoggedIn){
                    string log = "Logged out.";
                    window->writeToTrace(personTraced, log);
                    traceLoggedIn = false;
                }
                system("clear");
                goto MainMenu;

            case 'x':
                if(traceLoggedIn){
                    string log = "Exited Program.";
                    window->writeToTrace(personTraced, log);
                }
                goto End;

            default:
                system("clear");
                goto MainClientMenu;

            }
            system("clear");
            goto MainClientMenu;
            /*
             * END CLIENT BLOCK
             */
        case 2:
MainManagerMenu:
            // Manager menu and options
            cout << '\t' << "Welcome " << temp->getFirstName() << " " << temp->getLastName() << "!" << '\n';

            cout << '\n' << "1. Create New Client" << '\n';
            cout << "2. Create Account" << '\n';
            cout << "3. Close Account" << '\n';
            cout << "4. Get Client Info." << '\n';
            cout << "5. Get All Client info." << '\n';
            cout << "6. Get Total Bank Funds." << '\n';
            cout << "Z. Log Out" << '\n';
            cout << "X. Exit" << '\n' << '\n';
            cout << "Select an option (1-6,z,x)" << '\n';
            char manSwitch;
            cin >> manSwitch;
            switch(manSwitch){

            case '1':
            {
                //Client Creation
                // set up and get all parameters needed to make a base client with no accounts
                string fName, lName;
                vector<Account*> noAct;
                int pin;
                system("clear");
                cout << "Enter client's first name" << '\n';
                cin >> fName;
                cout << "Enter client's last name" << '\n';
                cin >> lName;
                cout << "Enter desired pin" << '\n';
                cin >> pin;
                //Save client
                newUser = new User(fName, lName, "Client", noAct, bankTest->getUser(), pin);
                bankTest->setUser(bankTest->getUser()+1);
                window->writeBank(bankTest);
                window->writeUser(newUser);
                system("clear");
                cout << "New Client created!" << '\n'<< '\n';
                if(traceLoggedIn){
                    string log = "Created new client: " + lName + ", " + fName + " with ID: " + to_string(bankTest->getUser()-1);
                    window->writeToTrace(personTraced, log);
                }
            }
                goto MainManagerMenu;

                /*
                 * END CLIENT CREATION
                 */

            case '2':
            {
                //Acount creation
                char accountType;
                string accountTypeS = "no";

                system("clear");
                cout << "Enter client's ID" << '\n';
                cin >> id;
                //check for user existing
                if(id >= bankTest->getUser() || id <= 0){
                    system("clear");
                    cout << "Sorry, no such user" << '\n'<< '\n';
                    if(traceLoggedIn){
                        string log = "Attempted to create a new account for a non-existent user";
                        window->writeToTrace(personTraced, log);
                    }
                }
                goto MainManagerMenu;


                User* u1 = window->readUser(id);
                //make sure user is a client
                if(u1->getUserType() != "Client"){
                    system("clear");
                    cout << "Sorry, that user is not a client" << '\n'<< '\n';
                    if(traceLoggedIn){
                        string log = "Attempted to create a new account for a non-client User with ID: " + to_string(u1->getID());
                        window->writeToTrace(personTraced, log);
                    }
                    goto MainManagerMenu;
                }
                system("clear");
                cout << "What type of account will you make?" << '\n';
                cout << "c = CHEQUING, s = SAVINGS" << '\n';
                cin >> accountType;
                if(accountType == 'c'){
                    accountTypeS = "Chequing";
                }
                if(accountType == 's'){
                    accountTypeS = "Savings";
                }
                //check for that type of account already existing
                for(int i = 0; i < u1->getAccounts().size(); i++){
                    if(u1->getAccounts()[i]->getAccountType() == accountTypeS){
                        system("clear");
                        cout << "That client already has a " << accountTypeS << " account." << '\n'<< '\n';
                        if(traceLoggedIn){
                            string log = "Attempted to create a new " + accountTypeS + " account for a User with ID: " + to_string(u1->getID()) + " that already has one of that type.";
                            window->writeToTrace(personTraced, log);
                        }
                        goto MainManagerMenu;
                    }

                }
                //create the account and save
                if(accountTypeS != "no"){
                    system("clear");
                    cout << accountTypeS << " account has been created." << '\n'<< '\n';
                    u1->addAccount(Account(accountTypeS, 0));
                    window->writeUser(u1);
                    if(traceLoggedIn){
                        string log = "Created a new " + accountTypeS + " account for User with ID: " + to_string(u1->getID());
                        window->writeToTrace(personTraced, log);
                    }
                }
            }
                goto MainManagerMenu;

                /*
                 * END ACCOUNT CREATION BLOCK
                 */

            case '3':
            {
                // account close
                char accountType;
                string accountTypeS = "no";
                system("clear");
                cout << "Enter client's ID" << '\n';
                cin >> id;
                // MAKE SURE user exists
                if(id >= bankTest->getUser() || id <=0){
                    system("clear");
                    cout << "Sorry, no such user" << '\n'<< '\n';
                    if(traceLoggedIn){
                        string log = "Attempted to close a " + accountTypeS + " account for a non-existent User.";
                        window->writeToTrace(personTraced, log);
                    }
                    goto MainManagerMenu;
                }
                //make sure user is a client
                User* u1 = window->readUser(id);
                if(u1->getUserType() != "Client"){
                    system("clear");
                    cout << "Sorry, that user is not a client" << '\n';
                    if(traceLoggedIn){
                        string log = "Attempted to close a " + accountTypeS + " account for a User with ID: " + to_string(u1->getID()) + " that is not a client.";
                        window->writeToTrace(personTraced, log);
                    }
                    goto MainManagerMenu;
                }

                cout << "What type of account would you like to close" << '\n';
                cout << "c = CHEQUING, s = SAVINGS" << '\n';
                cin >> accountType;
                if(accountType == 'c'){
                    accountTypeS = "Chequing";
                }
                if(accountType == 's'){
                    accountTypeS = "Savings";
                }
                // attempt closing the account type selected if it exists
                int succOrFail = u1->removeAccount(accountTypeS);
                if(succOrFail){
                    system("clear");
                    cout << '\n' << accountTypeS << " account has been closed." << '\n'<< '\n';
                    window->writeUser(u1);
                    if(traceLoggedIn){
                        string log = "Closed a " + accountTypeS + " account for a User with ID: " + to_string(u1->getID()) + ".";
                        window->writeToTrace(personTraced, log);
                    }
                    goto MainManagerMenu;
                }
                system("clear");
                cout << accountTypeS << " account doesn't exist or has a non-zero balance." << '\n'<< '\n';
                if(traceLoggedIn){
                    string log = "Attempted to close a " + accountTypeS + " account for a User with ID: " + to_string(u1->getID()) + " that doesn't have one of that type, or that account is not $0 balanced.";
                    window->writeToTrace(personTraced, log);
                }

            }
                goto MainManagerMenu;

                /*
                 * END ACCOUNT CLOSE BLOCK
                 */
            case '4':
            {
                //View Client Info
                system("clear");
                cout << "Enter client's ID" << '\n';
                cin >> id;
                User* u2 = new User();
                u2 = window->readUser(id);
                //make sure they are a client or they exist in DB
                if(u2->getUserType() != "Client"){
                    system("clear");
                    cout << "Sorry, that user is not a client." << '\n';
                    if(traceLoggedIn){
                        string log = "Attempted to look at account information of a non-existent User.";
                        window->writeToTrace(personTraced, log);
                    }
                    goto MainManagerMenu;
                }
                // display info
                system("clear");
                cout << "Name:" << u2->getLastName() << ", " << u2->getFirstName() << '\n';
                cout << "ID:" << u2->getID() << '\n';
                cout << "PIN:" << u2->getPIN() << '\n';
                cout << "Accounts:" << '\n';
                Account* a1;
                if(u2->getAccounts().size() > 0){
                    for(int i = 0; i < u2->getAccounts().size(); i++){
                        a1 = u2->getAccounts()[i];
                        cout << a1->getAccountType() << ": $" << a1->getBalance() << '\n';
                    }
                } else {
                    cout << "None." << '\n';
                }
                cout << '\n' << "Press b to return." << '\n'<< '\n';
                do{
                    cin >> ch6;
                }while(ch6 != 'b');
                if(traceLoggedIn){
                    string log = "Looked at account information of a User with ID: " + to_string(u2->getID()) + ".";
                    window->writeToTrace(personTraced, log);
                }
            }
                system("clear");
                goto MainManagerMenu;

                /*
                 * END VIEW CLIENT INFO BLOCK
                 */

            case '5':
            {
                // view or save all client info
                char fileOrScreen;
                system("clear");
                //choose to save or view
                cout << "Save to file or display on screen?" << '\n';
                cout << "f for file, any other button for display" << '\n';
                cin >> fileOrScreen;
                system("clear");
                User* u2 = new User();
                //loop through all users and write their info to a file if clients
                if(fileOrScreen == 'f'){
                    string filename = "../data/Users.dat";
                    ofstream outFile;
                    outFile.open(filename, ios::binary | ios::trunc);

                    for(int j = 1; j < bankTest->getUser(); j++){
                        u2 = window->readUser(j);
                        if(u2->getUserType() == "Client"){
                            outFile << "Name:" << u2->getLastName() << ", " << u2->getFirstName() << '\n';
                            outFile << "ID:" << u2->getID() << '\n';
                            outFile << "PIN:" << u2->getPIN() << '\n';
                            outFile << "Accounts:" << '\n';
                            Account* a1;
                            if(u2->getAccounts().size() > 0){
                                for(int i = 0; i < u2->getAccounts().size(); i++){
                                    a1 = u2->getAccounts()[i];
                                    outFile << a1->getAccountType() << ": $" << a1->getBalance() << '\n';
                                }
                            } else {
                                outFile << "None." << '\n';
                            }
                        }
                        outFile << '\n';
                    }
                    if(traceLoggedIn){
                        string log = "Created a file containing account information of all clients.";
                        window->writeToTrace(personTraced, log);
                    }
                }
                // loop through all users and display their info if clients
                else {
                    for(int j = 1; j < bankTest->getUser(); j++){
                        u2 = window->readUser(j);
                        if(u2->getUserType() == "Client"){
                            cout << "Name:" << u2->getLastName() << ", " << u2->getFirstName() << '\n';
                            cout << "ID:" << u2->getID() << '\n';
                            cout << "PIN:" << u2->getPIN() << '\n';
                            cout << "Accounts:" << '\n';
                            Account* a1;
                            if(u2->getAccounts().size() > 0){
                                for(int i = 0; i < u2->getAccounts().size(); i++){
                                    a1 = u2->getAccounts()[i];
                                    cout << a1->getAccountType() << ": $" << a1->getBalance() << '\n';
                                }
                            } else {
                                cout << "None." << '\n';
                            }
                        }
                        cout << '\n';
                    }
                    if(traceLoggedIn){
                        string log = "Looked at account information of all clients.";
                        window->writeToTrace(personTraced, log);
                    }

                    cout << '\n' << "Press b to return." << '\n'<< '\n';
                    do{
                        cin >> ch7;
                    }while(ch7 != 'b');
                }
            }
                system("clear");
                goto MainManagerMenu;

                /*
                 * END VIEW ALL CLIENT INFO BLOCK
                 */

            case '6':
                //show all bank funds
                system("clear");
                cout << "Total bank funds: $" << bankTest->getBalance() << '\n';
                cout << '\n' << "Press b to return." << '\n'<< '\n';
                if(traceLoggedIn){
                    string log = "Looked at bank balance.";
                    window->writeToTrace(personTraced, log);
                }
                do{
                    cin >> ch8;
                }while(ch8 != 'b');
                system("clear");
                goto MainManagerMenu;

                /*
                 * END VIEW BANK FUNDS BLOCK
                 */

            case 'z':
                //logout
                if(traceLoggedIn){
                    string log = "Logged out.";
                    window->writeToTrace(personTraced, log);
                    traceLoggedIn = false;
                }
                system("clear");
                goto MainMenu;

            case 'x':
                if(traceLoggedIn){
                    string log = "Exited Program.";
                    window->writeToTrace(personTraced, log);
                }
                goto End;
            default:
                system("clear");
                goto MainManagerMenu;
            }
            system("clear");
            goto MainManagerMenu;

            /*
             * END MANAGER BLOCK
             */

        case 3:
            system("clear");
MaintenanceMainMenu:
        {
            //Maintenance person

            //Display trace infor upon login
            cout << '\t' << "Welcome " << temp->getFirstName() << " " << temp->getLastName() << "!" << '\n';
            string traceStatus = "OFF";
            User* temp2;
            if(trace){
                traceStatus = "ON";
                temp2 = window->readUser(personTraced);
            }

            cout << '\n' << "Trace is currently: " << traceStatus << '\n';
            if(trace){
                cout << "Person being traced: " << temp2->getLastName() << ", " << temp2->getFirstName() << '\n';
                cout << "ID: " << temp2->getID() << '\n';
            }

            cout << '\n' << "1. Toggle trace" << '\n';
            cout << "2. Change user being traced" << '\n';
            cout << "3. Delete Trace Logs" << '\n';
            cout << "4. Change Theme" << '\n';
            cout << "Z. Log Out" << '\n';
            cout << "X. Exit" << '\n' << '\n';
            cout << "Select an option (1-4,z,x)" << '\n';

            char maintSwitch;
            cin >> maintSwitch;
            switch(maintSwitch){

            case '1':
            {
                //Trace toggle
                system("clear");
                if(trace){
                    trace = false;
                    bankTest->getTracer()->setTrace(false);
                    window->writeBank(bankTest);
                    cout << "Trace has been turned OFF." << '\n' << '\n';
                    if(traceLoggedIn){
                        string log = "Toggled Trace off.";
                        window->writeToTrace(personTraced, log);
                    }
                    traceLoggedIn = false;
                    goto MaintenanceMainMenu;
                }
                trace = true;
                bankTest->getTracer()->setTrace(true);
                window->writeBank(bankTest);
                cout << "Trace has been turned ON." << '\n' << '\n';
                //make sure to account for tracing the person logged in if need be
                if(personTraced == temp->getID()){
                    traceLoggedIn = true;
                }
                if(traceLoggedIn){
                    string log = "Toggled Trace on.";
                    window->writeToTrace(personTraced, log);
                }
                goto MaintenanceMainMenu;
            }
                goto MaintenanceMainMenu;

                /*
                 * END TRACE TOGGLE BLOCK
                 */

            case '2':
            {
                //Trace target
                int tempID;
                system("clear");
                cout << "Enter the ID of the user you would like to trace:" << '\n';
                cin >> tempID;

                if(tempID < bankTest->getUser() && tempID > 0){
                    personTraced = tempID;
                    bankTest->getTracer()->setID(tempID);
                    window->writeBank(bankTest);
                    cout << '\n' << "Successfully changed trace to ID: " << tempID << '\n' << '\n';

                    if(traceLoggedIn){
                        string log = "Changed trace target to User with ID: " + to_string(tempID);
                        window->writeToTrace(personTraced, log);
                    }
                    // account for pointing trace at self if trace was on
                    else if(trace == true && personTraced == tempID && temp->getID() == tempID){
                        traceLoggedIn = true;
                        string log = "Switched Trace to self while Trace on.";
                        window->writeToTrace(personTraced, log);
                    }

                    goto MaintenanceMainMenu;

                }
                // no such user
                cout << '\n' << "Sorry, could not find anyone with that ID." << '\n' << '\n';
                if(traceLoggedIn){
                    string log = "Attempted to change trace target to a non-existent user.";
                    window->writeToTrace(personTraced, log);
                }
                goto MaintenanceMainMenu;
            }


                /*
                 * END TRACE TARGET BLOCK
                 */

            case '3':
            {
DeleteLogsMenu:
                //log deletion of trace
                system("clear");
                cout << '\n' << "Are you sure? This will delete all logs and log you deleting them." << '\n';
                cout << "y - YES, n - NO" << '\n';
                char deleteLogs;
                cin >> deleteLogs;
                switch(deleteLogs){
                case 'y':
                {
                    //rewrite over trace log with just the entry of this person deleting the log
                    window->deleteTrace(temp->getID());
                    goto MaintenanceMainMenu;
                }
                case 'n':
                    if(traceLoggedIn){
                        string log = "Was promted to delete log of trace but chose not to.";
                        window->writeToTrace(personTraced, log);
                    }
                    goto MaintenanceMainMenu;
                default:
                    goto DeleteLogsMenu;
                }

            }
                goto MaintenanceMainMenu;

                /*
                 * END TRACE DELETION BLOCK
                 */

            case '4':
            {
ThemeMenu:
                //Theme selection
                system("clear");
                cout << "1. Default" << '\n';
                cout << "2. Harry Potter" << '\n';
                cout << "3. Megaman" << '\n' << '\n';

                cout << "Make a selection (1-3,b)" << '\n';

                char themeChar;
                cin >> themeChar;
                switch(themeChar){

                case '1':
                    //change theme to default and save
                    system("clear");
                    bankTest->setTheme("default");
                    window->writeBank(bankTest);
                    cout << "Theme changed to default!" << '\n';
                    if(traceLoggedIn){
                        string log = "Changed theme to default.";
                        window->writeToTrace(personTraced, log);
                        traceLoggedIn = false;
                    }
                    goto MaintenanceMainMenu;

                case '2':
                    //change theme to Harry Potter and save
                    system("clear");
                    bankTest->setTheme("Harry Potter");
                    window->writeBank(bankTest);
                    cout << "Theme changed to Harry Potter!" << '\n';
                    if(traceLoggedIn){
                        string log = "Some muggle changed theme to Harry Potter.";
                        window->writeToTrace(personTraced, log);
                        traceLoggedIn = false;
                    }
                    goto MaintenanceMainMenu;

                case '3':
                    //change theme to Megaman and save
                    system("clear");
                    bankTest->setTheme("Megaman");
                    window->writeBank(bankTest);
                    cout << "Theme changed to Megaman!" << '\n';
                    if(traceLoggedIn){
                        string log = "Changed theme to Megaman. Hope you like Rock and Roll!";
                        window->writeToTrace(personTraced, log);
                        traceLoggedIn = false;
                    }
                    goto MaintenanceMainMenu;

                case 'b':
                    //go back
                    system("clear");
                    goto MaintenanceMainMenu;

                default:
                    goto ThemeMenu;
                }

                system("clear");
                goto MaintenanceMainMenu;
            }
                goto MaintenanceMainMenu;

                /*
                 * END THEME SELECTION BLOCK
                 */

            case 'z':
                //logout
                if(traceLoggedIn){
                    string log = "Logged out.";
                    window->writeToTrace(personTraced, log);
                    traceLoggedIn = false;
                }
                system("clear");
                goto MainMenu;

            case 'x':
                if(traceLoggedIn){
                    string log = "Exited Program.";
                    window->writeToTrace(personTraced, log);
                }
                goto End;
            default:
                system("clear");
                goto MaintenanceMainMenu;
            }

        }
        default:
            system("clear");
            goto MaintenanceMainMenu;

            /*
             * END MAINTENANCE BLOCK
             */

        }

    }while(1); //end Menu loop

End:
    //printouts on exit prompt
    system("clear");
    if(bankTest->getTheme() == "Harry Potter"){
        cout<<"Thank you for being a valued customer of Gringotts!" << '\n' << '\n';
    }
    if(bankTest->getTheme() == "default"){
        cout<<"Thank you for being a valued customer of this simulated Bank!" << '\n' << '\n';
    }
    if(bankTest->getTheme() == "Megaman"){
        cout<<"Humans and robots living together in harmony and equality. That was my ultimate wish. (MegaBank thanks you)" << '\n' << '\n';
    }



}
