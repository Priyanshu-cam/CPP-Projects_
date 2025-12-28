// Implementing the Redo and Undo logic as a 6th mini project

#include <bits/stdc++.h>
using namespace std;
class Action
{
public:
// virtual function are overridden to enable runtime polymorphism 
    virtual void execute() = 0;
    virtual void undo() = 0;
    virtual ~Action() {}
};

class Account
{
public:
    int balance = 0;
    bool verified = false;
};

class Redo_Undo
{
    stack<unique_ptr<Action>> redoStack; // this will store the redo works 
    stack<unique_ptr<Action>> undoStack; // to store the undo works 


public:
    void performAction(unique_ptr<Action> a) //unique-ptr us used to provide exclusive ownership of dynamically allocated object , provide automatic memory management and memory leak
    {
        a->execute();
        undoStack.push(move(a));

        while (!redoStack.empty())
        {
            redoStack.pop();
        }
    }

    void undo()
    {
        if (!undoStack.empty())
        {
            auto a = move(undoStack.top());
            undoStack.pop();
            a->undo();
            redoStack.push(move(a));
        }
    }

    void redo()
    {
        if (!redoStack.empty())
        {
            auto a = move(redoStack.top());
            redoStack.pop();
            a->execute();
            undoStack.push(move(a));
        }
    }

   ~Redo_Undo() = default;
};

class DepositAction : public Action
{
    Account &account;
    int amount;

public:
    DepositAction(Account &acc, int amt)
        : account(acc), amount(amt) {}

    void execute() override
    {
        if (!account.verified || amount <= 0)
        {
            cout << "Invalid deposit\n";
            return;
        }
        account.balance += amount;
        cout << "Deposited " << amount << endl;
    }

    void undo() override
    {
        account.balance -= amount;
        cout << "Undo deposit " << amount << endl;
    }
};

int main(){
    Redo_Undo manager; 
    Account acc;
    acc.verified = true;

    cout << "Initial balance: " << acc.balance << endl;

    manager.performAction(make_unique<DepositAction>(acc, 500));

    cout << "After deposit: " << acc.balance << endl;

    manager.undo();
    cout << "After undo: " << acc.balance << endl;

    manager.redo();
    cout << "After redo: " << acc.balance << endl;
}
