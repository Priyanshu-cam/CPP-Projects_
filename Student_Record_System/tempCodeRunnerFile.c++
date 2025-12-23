// Creating a student record system where we can add, delete, update and view the students records and verify them

#include <bits/stdc++.h>
using namespace std;

class StudentRecords
{
private:
    struct Student
    {
        int id;
        string name;
        int age;
        double gpa;
        string department;
        int year;
        bool verified;
    };
    unordered_map<int, Student> records;

public:
    // student id exist check method
    bool studentExists(int id) const
    {
        return records.find(id) != records.end();
    }
    // add student method
    void addStudent(int id, string name, int age, double gpa, string department, int year)
    {
        Student newStudent = {id, name, age, gpa, department, year, false};
        if (records.find(id) != records.end())
        {
            cout << "Student with ID " << id << " already exists." << endl;
            return;
        }
        records[id] = newStudent;
        cout << "Student with ID " << id << " added successfully." << endl;
    }
    // delete student method
    void deleteStudent(int id)
    {
        if (records.find(id) != records.end())
        {
            records.erase(id);
            cout << "Student with ID " << id << " deleted successfully." << endl;
        }
        else
        {
            cout << "Student with ID " << id << " not found." << endl;
        }
    }
    // update student method
    void updateStudent(int id, string name, int age, double gpa, string department, int year)
    {
        if (records.find(id) != records.end())
        {
            Student &student = records[id];
            student.name = name;
            student.age = age;
            student.gpa = gpa;
            student.department = department;
            student.year = year;
            cout << "Student with ID " << id << " updated successfully." << endl;
        }
        else
        {
            cout << "Student with ID " << id << " not found." << endl;
        }
    }

    // view student method
    void viewStudent(int id) const
    {
        auto it = records.find(id);
        if (it == records.end())
        {
            cout << "Student with ID " << id << " not found." << endl;
            return;
        }

        const Student &student = it->second;

        cout << string(90, '-') << endl;

        cout << left
             << setw(10) << "ID"
             << setw(20) << "Name"
             << setw(10) << "Age"
             << setw(10) << "GPA"
             << setw(20) << "Department"
             << setw(10) << "Year"
             << setw(10) << "Verified" << endl;

        cout << string(90, '-') << endl;

        cout << left
             << setw(10) << student.id
             << setw(20) << student.name
             << setw(10) << student.age
             << setw(10) << student.gpa
             << setw(20) << student.department
             << setw(10) << student.year
             << setw(10) << (student.verified ? "Yes" : "No") << endl;

        cout << string(90, '-') << endl;
    }
    // view all student method
    void viewAllStudents() const
    {
        if (records.empty())
        {
            cout << "No student records available." << endl;
            return;
        }

        cout << string(90, '-') << endl;

        cout << left
             << setw(10) << "ID"
             << setw(20) << "Name"
             << setw(10) << "Age"
             << setw(10) << "GPA"
             << setw(20) << "Department"
             << setw(10) << "Year"
             << setw(10) << "Verified" << endl;

        cout << string(90, '-') << endl;

        for (const auto &pair : records)
        {
            const Student &student = pair.second;
            cout << left
                 << setw(10) << student.id
                 << setw(20) << student.name
                 << setw(10) << student.age
                 << setw(10) << student.gpa
                 << setw(20) << student.department
                 << setw(10) << student.year
                 << setw(10) << (student.verified ? "Yes" : "No") << endl;
        }

        cout << string(90, '-') << endl;
    }

    // verify student method
    void verifyStudent(int id)
    {

        if (records.find(id) != records.end())
        {
            Student &student = records[id];
            if (student.verified)
            {
                cout << "Student already verified." << endl;
                return;
            }

            student.verified = true;
            cout << "Student with ID " << id << " verified successfully." << endl;
        }
        else
        {
            cout << "Student with ID " << id << " not found." << endl;
        }
    }
};

int main()
{
    StudentRecords sr;

    while (true)
    {
        cout << "Student Record System Menu:\n";
        cout << "1. Add Student\n";
        cout << "2. Delete Student\n";
        cout << "3. Update Student\n";
        cout << "4. View Student\n";
        cout << "5. Verify Student\n";
        cout << "6. View All Students\n";
        cout << "7. Exit\n";
        int choice;
        cout << "Enter your choice of operation: ";
        cin >> choice;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input.Please enter a valid choice" << endl;
            continue;
        }

        if (choice == 7)
        {
            cout << "Exiting the Student Record System. GoodBye!" << endl;
            break;
        }

        int id, age, year;
        string name, department;
        double gpa;
        switch (choice)
        {
        case 1:
            cout << "Enter Student ID: ";
            cin >> id;
            if (sr.studentExists(id))
            {
                cout << "Student with ID " << id << " already exists." << endl;
                break;
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear newline character from input buffer
            cout << "Enter name: ";
            getline(cin, name);

            cout << "Enter age: ";
            cin >> age;
            if (age < 0 || age > 100)
            {
                cout << "Invalid age. Please enter a valid age." << endl;
                break;
            }
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Enter GPA (only ranges from 0.0 to 10.0): ";
            cin >> gpa;
            if (gpa < 0.0 || gpa > 10.0)
            {
                cout << "Invalid GPA. Please enter a GPA between 0.0 and 10.0." << endl;
                break;
            }

            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Enter department: ";
            getline(cin, department);

            cout << "Enter current year: ";
            cin >> year;
            if (year < 1 || year > 5)
            {
                cout << "Invalid academic year." << endl;
                break;
            }

            sr.addStudent(id, name, age, gpa, department, year);
            break;

        case 2:
            cout << "Enter Student ID to delete: ";
            cin >> id;
            sr.deleteStudent(id);
            break;

        case 3:
            cout << "Enter Student ID to update: ";
            cin >> id;
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear newline character from input buffer

            cout << "Enter name: ";
            getline(cin, name);

            cout << "Enter age: ";
            cin >> age;
            if (age < 0 || age > 100)
            {
                cout << "Invalid age. Please enter a valid age." << endl;
                break;
            }
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Enter GPA (only ranges from 0.0 to 10.0): ";
            cin >> gpa;
            if (gpa < 0.0 || gpa > 10.0)
            {
                cout << "Invalid GPA. Please enter a GPA between 0.0 and 10.0." << endl;
                break;
            }

            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Enter department: ";
            getline(cin, department);

            cout << "Enter course year: ";
            cin >> year;
            if (year < 1 || year > 5)
            {
                cout << "Invalid academic year." << endl;
                break;
            }
            sr.updateStudent(id, name, age, gpa, department, year);
            break;

        case 4:
            cout << "Enter Student ID to view: ";
            cin >> id;
            sr.viewStudent(id);
            break;

        case 5:
            cout << "Enter Student ID to verify: ";
            cin >> id;
            sr.verifyStudent(id);
            break;

        case 6:
            sr.viewAllStudents();
            break;
        default:
            cout << "Invalid choice. Please enter a valid choice." << endl;
        }
    }
}