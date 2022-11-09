//FCAI – Object-Oriented Programming 2 – 2022 - Assignment 2
// Program Name: Bank System
// Last Modification Date: 10/11/2022
// Author1 and ID and Group: Aya Ali Hassan        ID: 20210083
// Author2 and ID and Group: Belal Ahmed Eid       ID: 20210092
// Author3 and ID and Group: Habiba Mohamed Morgan ID: 20210119
//Bank system program that provides withdrawing and depositing money with saving the clients' information.

#include <iostream>
#include <map>
#include <set>

using namespace std;

class BankAccount;

class Client;

class SavingsBankAccount;


class Client {
private:

    string Name;
    string Address;
    string phoneNumber;
    string accountType;
    BankAccount *account;

public:

    Client();

    Client(string name, string address, string phone_number, string type);

    void setClientBankAccount(BankAccount &);

    string getName();

    string getAddress();

    string getPhoneNumber();

    string getAccountType();

    BankAccount *getBalance();
};

Client::Client() {}

Client::Client(string name, string address, string phone_number, string type) {
    Name = name;

    Address = address;

    phoneNumber = phone_number;

    accountType = type;
}

void Client::setClientBankAccount(BankAccount &newAccount) {
    account = &newAccount;
}

string Client::getName() {
    return Name;
}

string Client::getAddress() {
    return Address;
}

string Client::getPhoneNumber() {
    return phoneNumber;
}

string Client::getAccountType() {
    return accountType;
}

BankAccount *Client::getBalance() {
    return account;
}


class BankAccount {
protected:

    Client *client;
    string accountID;
    double Balance;

public:

    BankAccount();

    BankAccount(double h);

    void setAccountID(string AccID) {
        accountID = AccID;
    }

    void setClient(Client &anything);

    void set_Balance(double b) {
        Balance = b;
    }

    string getAccountID() {
        return accountID;
    }

    double get_Balance() {
        return Balance;
    }

    virtual double withdraw(double balance, double amount);

    virtual double deposit(double balance, double amount);

};

BankAccount::BankAccount() {
    Balance = 0;
}

BankAccount::BankAccount(double h) {
    Balance = h;
}

void BankAccount::setClient(Client &cl) {
    client = &cl;
}

double BankAccount::withdraw(double balance, double amount) {
    while (amount > balance) {
        cout << "Your balance is less the amount you want to withdraw: \n";
        cin >> amount;
        cin.clear();
        cin.sync();
    }
    return balance - amount;
}

double BankAccount::deposit(double balance, double amount) {
    return balance + amount;
}


class SavingsBankAccount : public BankAccount {
private:
    double MinimumBalance = 1000;
public:

    SavingsBankAccount(double n);

    SavingsBankAccount() {};

    virtual double withdraw(double amount);

    virtual double deposit(double amount);

    void set_Balance(double b) {
        Balance = b;
    }

    double get_Balance() {
        return Balance;
    }


};

SavingsBankAccount::SavingsBankAccount(double n) : BankAccount(Balance) {
    while (n < MinimumBalance) {
        cout << "The MinimumBalance should be greater than or equal 1000:\n";
        cin >> n;
        cin.clear();
        cin.sync();
    }
    Balance = n;
}

double SavingsBankAccount::withdraw(double amount) {

    while (Balance - amount < MinimumBalance) {
        cout << "The MinimumBalance should be greater than or equal 1000:\n";
        cin >> amount;
        cin.clear();
        cin.sync();
    }
    cout << "Withdrawing is done.\n";
    return Balance - amount;
}

double SavingsBankAccount::deposit(double amount) {

    while (amount < 100) {
        cout << "The amount you want to deposit is less than 100.\n";
        cin >> amount;
        cin.clear();
        cin.sync();
    }
    cout << "Deposition is done.\n";
    return Balance + amount;
}


class banking_application {
private:

    int idCounter = 0;
    double balance{};
    string selectOption;
    map<string, Client> clients;
    map<string, BankAccount> basicAccounts;
    map<string, SavingsBankAccount> savingAccounts;

public:
    banking_application();

    void displayMenu();

    void addClient();

    void listClients();

    string enterAccountID();

    void withdrawBasicAccount(string id);

    void withdrawSavingAccount(string id);

    void depositBasicAccount(string id);

    void depositSavingAccount(string id);
};


banking_application::banking_application() {
    while (true) {
        displayMenu();
        if (selectOption == "1") {
            addClient();
        } else if (selectOption == "2") {
            listClients();
        } else if (selectOption == "3") {
            string accountID = enterAccountID();
            if (clients[accountID].getAccountType() == "Basic")withdrawBasicAccount(accountID);
            else withdrawSavingAccount(accountID);
        } else if (selectOption == "4") {
            string accountID = enterAccountID();
            if (clients[accountID].getAccountType() == "Basic") depositBasicAccount(accountID);
            else depositSavingAccount(accountID);
        } else if (selectOption == "5") {
            exit(1);
        } else {
            cout << "Chose a valid option !" << endl;
        }
    }
}

void banking_application::displayMenu() {
    cout << "\nWelcome to FCAI Banking Application \n"
            "1. Create a New Account\n"
            "2. List Clients and Accounts\n"
            "3. Withdraw Money\n"
            "4. Deposit Money\n"
            "5. Exit\n"
            "Please Enter Choice =========> ";
    cin >> selectOption;
    cin.clear();
    cin.sync();
}

void banking_application::addClient() {

    string clientName;
    string clientAddress;
    string clientPhoneNumber;
    string clientAccountType;

    // Generate IDs
    string ID = "FCAI-";
    if (idCounter < 10) {
        ID.insert(ID.size(), 2, '0');
        ID.insert(ID.size(), 1, idCounter + '0');
    } else if (idCounter < 100) {
        ID.insert(ID.size(), 1, '0');
        ID += to_string(idCounter);
    } else {
        ID += to_string(idCounter);
    }

    cout << "\nPlease Enter Client Name =========> ";
    getline(cin, clientName);
    cin.clear();
    cin.sync();
    cout << "\nPlease Enter Client Address =======> ";
    getline(cin, clientAddress);
    cin.clear();
    cin.sync();
    cout << "\nPlease Enter Client Phone =======> ";
    getline(cin, clientPhoneNumber);
    cin.clear();
    cin.sync();
    cout << "\nWhat Type of Account Do You Like? (1) Basic (2) Saving - Type 1 or 2 =========> ";
    cin >> clientAccountType;
    cin.clear();
    cin.sync();

    if (clientAccountType == "1") {
        Client clientData(clientName, clientAddress, clientPhoneNumber, "Basic");

        cout << "\nPlease Enter the Starting account =========> ";
        cin >> balance;
        cin.clear();
        cin.sync();

        BankAccount openBasicAccount(balance);
        openBasicAccount.setAccountID(ID);

        clients[ID] = clientData;
        basicAccounts[ID] = openBasicAccount;

        basicAccounts[ID].setClient(clients[ID]);
        clients[ID].setClientBankAccount(basicAccounts[ID]);
    } else {
        Client clientData(clientName, clientAddress, clientPhoneNumber, "Saving");

        cout << "\nPlease Enter the Starting account =========> ";
        cin >> balance;
        cin.clear();
        cin.sync();

        SavingsBankAccount openSaving(balance);
        openSaving.setAccountID(ID);

        clients[ID] = clientData;
        savingAccounts[ID] = openSaving;

        savingAccounts[ID].setClient(clients[ID]);
        clients[ID].setClientBankAccount(savingAccounts[ID]);
    }
    cout << "\nYour account is created and your ID is " << ID << "\n";
    idCounter++;
}

void banking_application::listClients() {

    // show all clients and basicAccounts
    if (clients.empty()) {
        cout << "There is no registered clients in the system yet\n";
    } else {
        for (auto &client: clients) {
            cout << "\n------------------- " << client.second.getName() << " -------------------" << "\n";
            cout << "\nAddress    :" << client.second.getAddress();
            cout << "\nPhone      :" << client.second.getPhoneNumber();
            cout << "\nBalance    :" << client.second.getBalance()->get_Balance();
            cout << "\nAccount ID :" << client.first << "\n";
        }
    }
}

string banking_application::enterAccountID() {
    cout << "\nPlease enter Account ID(e.g: FCAI-015): ";
    string accountID;
    cin >> accountID;
    // convert id characters to uppercase
    for (int i = 0; i <= 3; ++i)accountID[i] = toupper(accountID[i]);
    while (clients.find(accountID) == clients.end()) {
        cout << "\nYour ID is Invalid. Try again: ";
        cin >> accountID;
        for (int i = 0; i <= 3; ++i)accountID[i] = toupper(accountID[i]);
        cin.clear();
        cin.sync();
    }
    return accountID;
}

void banking_application::withdrawBasicAccount(string id) {
    string accountID = id;
    cout << "\nAccount ID  : " << accountID;
    cout << "\nAccount Type: " << clients[accountID].getAccountType();
    cout << "\nBalance     : " << basicAccounts[accountID].get_Balance();
    cout << "\nPlease enter the amount you want to withdraw: ";

    double amount;
    cin >> amount;

    double accountBalance = basicAccounts[accountID].get_Balance();
    basicAccounts[accountID].set_Balance(basicAccounts[accountID].withdraw(accountBalance, amount));

    cout << "\nThank You.";
    cout << "\nAccount ID: " << accountID;
    cout << "\nNew Balance: " << basicAccounts[accountID].get_Balance() << "\n";
}

void banking_application::withdrawSavingAccount(string id) {
    string accountID = id;
    cout << "\nAccount ID  : " << accountID;
    cout << "\nAccount Type: " << clients[accountID].getAccountType();
    cout << "\nBalance     : " << savingAccounts[accountID].get_Balance();
    cout << "\nPlease enter the amount you want to withdraw: ";

    double amount;
    cin >> amount;

    double newBalance = savingAccounts[accountID].withdraw(amount);
    savingAccounts[accountID].set_Balance(newBalance);

    cout << "\nThank You.";
    cout << "\nAccount ID: " << accountID;
    cout << "\nNew Balance: " << savingAccounts[accountID].get_Balance() << "\n";
}

void banking_application::depositBasicAccount(string id) {
    string accountID = id;
    cout << "\nAccount ID  : " << accountID;
    cout << "\nAccount Type: " << clients[accountID].getAccountType();
    cout << "\nBalance     : " << basicAccounts[accountID].get_Balance();
    cout << "\nPlease enter the amount you want to deposit: ";

    double amount;
    cin >> amount;

    double accountBalance = basicAccounts[accountID].get_Balance();
    basicAccounts[accountID].set_Balance(basicAccounts[accountID].deposit(accountBalance, amount));

    cout << "\nThank You.";
    cout << "\nAccount ID: " << accountID;
    cout << "\nNew Balance: " << basicAccounts[accountID].get_Balance() << "\n";
}

void banking_application::depositSavingAccount(string id) {
    string accountID = id;
    cout << "\nAccount ID  : " << accountID;
    cout << "\nAccount Type: " << clients[accountID].getAccountType();
    cout << "\nBalance     : " << savingAccounts[accountID].get_Balance();
    cout << "\nPlease enter the amount you want to deposit: ";

    double amount;
    cin >> amount;

    double newBalance = savingAccounts[accountID].deposit(amount);
    savingAccounts[accountID].set_Balance(newBalance);

    cout << "\nThank You.";
    cout << "\nAccount ID: " << accountID;
    cout << "\nNew Balance: " << savingAccounts[accountID].get_Balance() << "\n";
}


int main() {
    banking_application b1;
}
