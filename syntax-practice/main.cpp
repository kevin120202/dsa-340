#include <iostream>
#include <vector>
#include <string>
using namespace std;

class BankAccount {
private:
    string accountHolder;
    double balance;

public:
    // Constructor
    BankAccount(const string& name, double initialBalance)
        : accountHolder(name), balance(initialBalance) {}

    // Deposit
    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << "Deposited $" << amount << ". New balance: $" << balance << endl;
        }
        else {
            cout << "Deposit amount must be positive." << endl;
        }
    }

    // Withdraw
    void withdraw(double amount) {
        if (amount > 0) {
            balance -= amount;
            cout << "Withdrew $" << amount << ". New balance: $" << balance << endl;
        }
        else {
            cout << "Withdrawal amount must be positive." << endl;
        }
    }

    // Display
    void display() const {
        cout << "Account holder: " << accountHolder << endl;
        cout << "Balance: $" << balance << endl;
    }
};

class Bank {
private:
    vector<BankAccount*> accounts;

public:
    // Destructor to free dynamically allocated memory
    ~Bank() {
        for (BankAccount* account : accounts) {
            delete account;
        }
    }

    // Create new account
    void createAccount(const string& name, double initialBalance) {
        BankAccount* newAccount = new BankAccount(name, initialBalance);
        accounts.push_back(newAccount);
        cout << "Account created for " << name << endl;
    }

    // Display all accounts
    void displayAccounts() const {
        for (const BankAccount* account : accounts) {
            account->display();
            cout << "--------------" << endl;
        }
    }

    void depositToAccount(int index, double amount) {
        if (index >= 0 && index < accounts.size()) {
            accounts[index]->deposit(amount);
        }
        else {
            cout << "Invalid account index." << endl;
        }
    }

    void withdrawFromAccount(int index, double amount) {
        if (index >= 0 && index < accounts.size()) {
            accounts[index]->withdraw(amount);
        }
        else {
            cout << "Invalid account index." << endl;
        }
    }
};

int main() {
    Bank bank;

    bank.createAccount("Kevin", 20000);
    bank.createAccount("Micaiah", 50000);

    bank.displayAccounts();

    bank.depositToAccount(0, 500);
    bank.depositToAccount(1, 9000);

    bank.displayAccounts();

    return 0;
}