// Login and Registration System project

#include <iostream>
#include <string>
#include <fstream>
#include <limits>

using namespace std;

class Authentication
{
private:
    string userName;
    string password;
    string fullName;
    string emailId;

public:
    void login()
    {
        string uName;
        string pass;
        cout << "------------------------------" << endl;
        cout << "Enter userName" << endl;
        getline(cin, uName);

        cout << "Enter password" << endl;
        getline(cin, pass);

        cout << "------------------------------" << endl;
        ifstream fin(uName + ".txt");

        if (fin.is_open())
        {
            if (
                getline(fin, fullName) &&
                getline(fin, emailId) &&
                getline(fin, userName) &&
                getline(fin, password))
            {
                if (userName == uName && password == pass)
                {
                    cout << "Login Successful\n";
                }
                else
                {
                    cout << "Invalid Username or Password\n";
                }
            }
        }
        else
        {
            cout << "This is not an authorise person!" << endl;
        }
    }

    void registration()
    {
        // getting user inputs
        cout << "--------------------------------" << endl;
        cout << "Enter fullName" << endl;
        getline(cin, fullName);

        cout << "Enter email" << endl;
        getline(cin, emailId);

        cout << "Enter username" << endl;
        getline(cin, userName);

        cout << "Enter password " << endl;
        getline(cin, password);
        cout << "--------------------------------" << endl;

        // Storing user inputs
        ofstream fout(userName + ".txt");
        if (fout.is_open())
        {
            fout << fullName << "\n";
            fout << emailId << "\n";
            fout << userName << "\n";
            fout << password << "\n";

            fout.close();
        }
        else
        {
            cout << "Error" << endl;
        }
    }
};

int main()
{
    Authentication a1;
    while (true)
    {
        int x;
        cout << "Enter 1 for login: " << endl;
        cout << "Enter 2 for registration: " << endl;
        cin >> x;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // or the safer version below

        if (x == 1)
            a1.login();
        else if (x == 2)
            a1.registration();
    }
}
