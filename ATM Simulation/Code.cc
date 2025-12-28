// creating a ATM simulation where insert pin, verify pin, withdraw amount, make a receipt and maintain a transaction history

#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

class ATM
{
private:
    int pin = 666645;
    int amount = 12000;
    int dailyWithdrawCount = 0;

    struct Transaction
    {
        int amount;
        int balanceAfter;
    };
    vector<Transaction> transactionHistory;

public:
    bool verifyPin(int pin)
    {
        if (pin != this->pin)
        {
            cout << "Invalid Pin, Transaction failed!" << endl;
            return false;
        }

        return true;
    }

    void withdraw(int enteredAmount)
    {
        // to check the  daily transaction limit;
        if (dailyWithdrawCount == 3)
        {
            cout << "You have reached your daily withdraw limit" << endl;
            return;
        }

        Transaction t;
        // insufficient amount
        if (this->amount < enteredAmount)
        {
            cout << "Insufficient Amount, Transaction Failed!" << endl;
            return;
        }

        this->amount -= enteredAmount;
        t.amount = enteredAmount;
        t.balanceAfter = this->amount;
        transactionHistory.push_back(t);
        dailyWithdrawCount++;
        cout << "Balance left: " << this->amount << endl;
    }

    void printReceipt()
    {
        if (transactionHistory.empty())
        {
            cout << "No transaction to print receipt for." << endl;
            return;
        }

        Transaction last = transactionHistory.back();

        cout << "Transaction Receipt" << endl;
        cout << string(90, '-') << endl;

        cout << left
             << setw(20) << "Account Number"
             << setw(20) << "Name"
             << setw(20) << "Withdrawn"
             << setw(20) << "Balance" << endl;

        cout << string(90, '-') << endl;

        cout << left
             << setw(20) << "12XXXXXXXX23"
             << setw(20) << "Mahesh Kumar"
             << setw(20) << last.amount
             << setw(20) << last.balanceAfter << endl;

        cout << string(90, '-') << endl;
    }

    void showTransactions()
    {

        int n = transactionHistory.size();

        for (int i = 0; i < n; i++)
        {
            cout << "Withdraw: " << transactionHistory[i].amount << " | " << "Balance: " << transactionHistory[i].balanceAfter << endl;
        }
    }
};

int main()
{
    ATM a;
    int pin, amount;

    while (true)
    {
        cout << "Insert your card" << endl;
        cout << "Enter the required amount:" << endl;
        cin >> amount;
        cout << "Enter your Pin" << endl;
        cin >> pin;
        if (a.verifyPin(pin) == false)
        {
            break;
        }
        a.withdraw(amount);
        cout << "Do you want to print receipt (1 =Yes / 0 = No)" << endl;
        int choice;
        cin >> choice;
        if (choice == 1)
            a.printReceipt();
        cout << "Transaction done successfully! Thank You" << endl;
        int option; 
        cout<<"Do you want to see your transaction history? (1 = yes / 0 = no)"<<endl;
        cin>>option; 
        if(option == 1)a.showTransactions();
        cout << "Take out your card please!" << endl;
    }
    return 0;
}