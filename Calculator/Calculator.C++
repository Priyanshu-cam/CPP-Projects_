// Build a Calculator class that can perform basic arithmetic operations
// such as addition, subtraction, multiplication, and division.
#include <bits/stdc++.h>
using namespace std;

class Calculator
{
private:
    // storing history of calculations
    struct History
    {
        int id;
        string operation;
        string expression;
        double result;
    };
    vector<History> history;

public:
    // Add method
    double add(double a, double b)
    {
        history.push_back({(int)history.size() + 1, "addition", to_string(a) + " + " + to_string(b), (double)(a + b)});
        return a + b;
    }
    // subtract method
    double subtract(double a, double b)
    {
        history.push_back({(int)history.size() + 1, "subtraction", to_string(a) + " - " + to_string(b), (double)(a - b)});
        return a - b;
    }
    // multiply method
    double multiply(double a, double b)
    {
        history.push_back({(int)history.size() + 1, "multiply", to_string(a) + " * " + to_string(b), (double)(a * b)});
        return a * b;
    }
    // divide method
    double divide(double a, double b)
    {
        if (b == 0)
        {
            throw invalid_argument("Division by zero is not allowed");
        }
        history.push_back({(int)history.size() + 1, "division", to_string(a) + " / " + to_string(b), (double)(a / b)});
        return a / b;
    }
    // modulo method
    double modulo(double a, double b)
    {
        if (b == 0)
        {
            throw invalid_argument("Modulo by 0 is not allowed");
        }

        double result = fmod(a, b);

        history.push_back({(int)history.size() + 1,
                           "fmod",
                           "fmod(" + to_string(a) + ", " + to_string(b) + ")",
                           result});

        return result;
    }
    // power method
    double power(double a, double b)
    {
        history.push_back({(int)history.size() + 1, "power", to_string(a) + " ^ " + to_string(b), (double)(pow(a, b))});
        return pow(a, b);
    }
    // square root method
    double squareRoot(double a)
    {
        if (a < 0)
        {
            throw invalid_argument("Square root of negative number is not allowed");
        }
        history.push_back({(int)history.size() + 1, "sqrt", to_string(a), (double)(sqrt(a))});
        return sqrt(a);
    }
    // view history method
    void viewHistory()
    {
        if (history.empty())
        {
            cout << "No history available, no operations performed yet." << endl;
            return;
        }
        cout << " <-------- Calculation History --------> " << endl;
        cout << left
             << setw(5) << "Id"
             << setw(15) << "Operation"
             << setw(25) << "Expression"
             << setw(10) << "Result" << endl;
        cout << string(55, '-') << endl;
        for (const auto &record : history)
        {
            cout << left
                 << setw(5) << record.id
                 << setw(15) << record.operation
                 << setw(25) << record.expression
                 << setw(10) << record.result << endl;
        }
        cout << " <------------------------------------> " << endl;
    }
};

int main()
{
    Calculator calc;

    while (true)
    {
        cout << "Choose the required operations:\n";
        cout << "0. Exit\n";
        cout << "1. Addition\n";
        cout << "2. Subtraction\n";
        cout << "3. Multiplication\n";
        cout << "4. Division\n";
        cout << "5. Modulo\n";
        cout << "6. Power\n";
        cout << "7. Square Root\n";
        cout << "8. View History\n";

        int choice;
        cin >> choice;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a valid choice" << endl;
            continue;
        }

        if (choice == 0)
        {
            cout << "Exiting the calculator. Goodbye!" << endl;
            break;
        }
        if (choice == 8)
        {
            calc.viewHistory();
            continue;
        }

        try
        {
            double num1, num2;
            if (choice == 7)
            {
                cout << "Enter number: ";
                cin >> num1;
                if (cin.fail())
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid input. Please enter a valid choice" << endl;
                    continue;
                }
                cout << "Result: " << calc.squareRoot(num1) << endl;
                continue;
            }
            cout << "Enter two numbers: ";
            cin >> num1 >> num2;
            if (cin.fail())
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a valid choice" << endl;
                continue;
            }
            switch (choice)
            {
            case 1:
                cout << "Result: " << calc.add(num1, num2) << endl;
                break;
            case 2:
                cout << "Result: " << calc.subtract(num1, num2) << endl;
                break;
            case 3:
                cout << "Result: " << calc.multiply(num1, num2) << endl;
                break;
            case 4:
                cout << "Result: " << calc.divide(num1, num2) << endl;
                break;
            case 5:
                cout << "Result: " << calc.modulo(num1, num2) << endl;
                break;
            case 6:
                cout << "Result: " << calc.power(num1, num2) << endl;
                break;
            default:
                cout << "Invalid Choice" << endl;
            }
        }
        catch (const invalid_argument &e)
        {
            cout << e.what() << endl;
        }
    }
    return 0;
}