// I will create a banking system that includes features like:
// account management : new account, delete account,view account and update profile
// banking: deposit, withdraw, transaction history and check balance
// handling: insufficient balance, invalid account, unique account number

#include <bits/stdc++.h>
using namespace std;

class Account
{
public:
    string name;
    string DOB;
    string phoneNumber;
    long long accountNumber;
    double balance;
    bool verified;
};

class Bank
{
private:
    map<long long, Account> accounts;

public:
    // student id exist check method
    bool accountExist(long long accountNumber) const
    {
        return accounts.find(accountNumber) != accounts.end();
    }

    // add account method
    void addAccount(string name, string DOB, string phoneNumber, double balance)
    {
        static long long accNum = 1101010101LL;
        Account newAccount;
        newAccount.accountNumber = accNum;
        newAccount.name = name;
        newAccount.DOB = DOB;
        newAccount.phoneNumber = phoneNumber;
        newAccount.balance = balance;
        newAccount.verified = false;

        accounts[accNum] = newAccount;

        cout << "Account created successfully!\n";
        cout << "Your Account Number is: " << accNum << endl;
        accNum++;
    }

    // delete account method
    void deleteAccount(long long accountNumber)
    {
        auto it = accounts.find(accountNumber);

        if (it == accounts.end())
        {
            cout << "User with " << accountNumber << " does not exist\n";
            return;
        }

        if (it->second.balance > 0)
        {
            cout << "Withdraw balance before deleting account\n";
            return;
        }

        accounts.erase(it);
        cout << "Account with " << accountNumber << " deleted successfully\n";
    }

    Account *getAccount(long long accountNumber)
    {
        auto it = accounts.find(accountNumber);
        if (it == accounts.end())
            return nullptr;
        return &it->second;
    }

    // view account details method
    void viewAccount(long long accountNumber)
    {
        auto it = accounts.find(accountNumber);
        if (it == accounts.end())
        {
            cout << "User with " << accountNumber << " not exist" << endl;
            return;
        }

        const Account &account = it->second;
        cout << string(90, '-') << endl;

        cout << left
             << setw(20) << "Account Number"
             << setw(20) << "Name"
             << setw(20) << "DOB"
             << setw(20) << "Phone Number"
             << setw(20) << "Balance" << endl;

        cout << string(90, '-') << endl;

        cout << left
             << setw(20) << account.accountNumber
             << setw(20) << account.name
             << setw(20) << account.DOB
             << setw(20) << account.phoneNumber
             << setw(20) << account.balance << endl;

        cout << string(90, '-') << endl;
    }

    // update account details
    void updateAccount(long long accountNumber, string name, string dob, string phoneNumber, double balance)
    {
        if (balance < 0)
        {
            cout << "Balance cannot be negative\n";
            return;
        }

        if (accounts.find(accountNumber) != accounts.end())
        {
            Account &account = accounts[accountNumber];
            account.name = name;
            account.DOB = dob;
            account.phoneNumber = phoneNumber;
            account.balance = balance;

            cout << "Account with " << accountNumber << " updated successfully" << endl;
        }
        else
            cout << "User with " << accountNumber << " not found" << endl;
    }
};

class AccountOperations
{
public:
    // KYC verification method
    static void verifiedUser(Account &account)
    {

        if (account.verified)
        {
            cout << "User is already verified\n";
            return;
        }
        account.verified = true;
        cout << "User verified successfully\n";
    }

    // Withdraw method
    static void withdrawAmount(Account &account, double amount)
    {
        if (!account.verified)
        {
            cout << "Account not verified. Complete KYC first.\n";
            return;
        }
        if (amount <= 0)
        {
            cout << "Invalid withdrawal amount\n";
            return;
        }

        if (amount > account.balance)
        {
            cout << "Oops! Insufficient Amount" << endl;
            return;
        }

        account.balance = account.balance - amount;
        cout << "Transaction is completed" << endl;
    }

    // add Amount
    static void depositAmount(Account &account, double amount)
    {
        if (!account.verified)
        {
            cout << "Account not verified. Complete KYC first.\n";
            return;
        }
        if (amount <= 0)
        {
            cout << "Invalid deposit amount\n";
            return;
        }

        account.balance = account.balance + amount;

        cout << "Amount deposited successfully!" << endl;
    }
};
// valid phone number
static bool isValidPhoneNumber(const string &phone)
{
    if (phone[0] == '0') // should not starts with 0
        return false;

    if (phone.length() != 10) // should have length = 10
        return false;

    for (char ch : phone)
    {
        if (!isdigit(ch))
            return false;
    }
    bool allSame = true; // does not contains same digits
    for (int i = 1; i < 10; i++)
        if (phone[i] != phone[0])
            allSame = false;

    if (allSame)
        return false;

    return true;
}
// VALID DOB
bool isValidDOB(const string &dob)
{
    int year, month, day;
    char dash1, dash2;

    stringstream ss(dob);
    ss >> year >> dash1 >> month >> dash2 >> day;

    if (ss.fail() || dash1 != '-' || dash2 != '-')
        return false;

    // Basic date validation
    if (year < 1900 || month < 1 || month > 12 || day < 1 || day > 31)
        return false;

    // Get current date
    time_t t = time(nullptr);
    tm *now = localtime(&t);

    int currentYear = now->tm_year + 1900;
    int currentMonth = now->tm_mon + 1;
    int currentDay = now->tm_mday;

    int age = currentYear - year;

    if (currentMonth < month ||
        (currentMonth == month && currentDay < day))
    {
        age--;
    }

    return age >= 18;
}

int main()
{
    Bank b;

    while (true)
    {
        cout << "<---------------- Bank Operations ------------------>" << endl;
        cout << "1. New Account" << endl;
        cout << "2. Delete Account" << endl;
        cout << "3. view Account" << endl;
        cout << "4. Update Account" << endl;
        cout << "5. KYC Verification" << endl;
        cout << "6. Withdraw" << endl;
        cout << "7. Deposit" << endl;
        cout << "8. Exit" << endl;

        int choice;
        cout << "Enter your choice" << endl;
        cin >> choice;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input.Please enter a valid choice" << endl;
            continue;
        }

        if (choice == 8)
        {
            cout << "Thank you for visiting Us, Have a Good Day Ahead!" << endl;
            break;
        }
        long long accountNumber;
        double amount;
        string name, dob, phoneNumber;

        switch (choice)
        {
        case 1:
            cout << "Enter your name: " << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, name);

            cout << "Enter your phone number: " << endl;
            cin >> phoneNumber;
            if (!isValidPhoneNumber(phoneNumber))
            {
                cout << "Invalid phone number. Must contain exactly 10 digits.\n";
                break;
            }
            cout << "Enter your DOB (YYYY-MM-DD): " << endl;
            cin >> dob;
            if (!isValidDOB(dob))
            {
                cout << "Invalid DOB or age must be 18+ to open an account.\n";
                break;
            }
            cout << "Enter initial amount:" << endl;
            cin >> amount;
            if (amount < 0)
            {
                cout << "Initial balance cannot be negative\n";
                break;
            }

            b.addAccount(name, dob, phoneNumber, amount);
            break;

        case 2:
            cout << "Enter a valid account Number:" << endl;
            cin >> accountNumber;
            b.deleteAccount(accountNumber);
            break;

        case 3:
            cout << "Enter a valid account Number:" << endl;
            cin >> accountNumber;
            b.viewAccount(accountNumber);
            break;

        case 4:
            cout << "Enter account number: ";
            cin >> accountNumber;

            cout << "Enter name: ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, name);

            cout << "Enter dob: ";
            cin >> dob;

            cout << "Enter your Phone Number): ";
            cin >> phoneNumber;

            cout << "Enter Amount: ";
            cin >> amount;
            b.updateAccount(accountNumber, name, dob, phoneNumber, amount);
            break;

        case 5:
        {
            cout << "Enter your Account number:\n";
            cin >> accountNumber;
            if (!b.accountExist(accountNumber))
            {
                cout << "Invalid account number\n";
                break;
            }

            Account *acc = b.getAccount(accountNumber);
            AccountOperations::verifiedUser(*acc);

            break;
        }

        case 6:
        {
            cout << "Enter your Account Number:\n";
            cin >> accountNumber;
            cout << "Enter the Amount:\n";
            cin >> amount;
            if (!b.accountExist(accountNumber))
            {
                cout << "Invalid account number\n";
                break;
            }

            Account *acc = b.getAccount(accountNumber);

            AccountOperations::withdrawAmount(*acc, amount);
            break;
        }

        case 7:
        {
            cout << "Enter your Account Number:\n";
            cin >> accountNumber;
            cout << "Enter the Amount:\n";
            cin >> amount;
            if (!b.accountExist(accountNumber))
            {
                cout << "Invalid account number\n";
                break;
            }

            Account *acc = b.getAccount(accountNumber);

            AccountOperations::depositAmount(*acc, amount);
            break;
        }

        default:
            cout << "Invalid Choice, Bye Bye " << endl;
        }
    }

    return 0;
}