#include <bits/stdc++.h>
#include <iostream>
#include <map>
#include <iomanip>
#include <string>

using namespace std;

class Doctor
{
public:
    int id;
    string name;
    string specialization;
    string department;

    void display()
    {
        cout << left
             << setw(15) << id
             << setw(25) << name
             << setw(25) << specialization
             << setw(25) << department << endl;
    }
};

class Patient
{
public:
    int id;
    string name;
    int age;
    string disease;
    int assignedDoctorId = -1;

    void display()
    {
        cout << left
             << setw(15) << id
             << setw(25) << name
             << setw(25) << age
             << setw(25) << disease << endl;
    }
};

class HospitalManagement
{
private:
    map<int, Doctor> doctors;
    map<int, Patient> patients;

public:
    string toLower(string s)
    {
        for (char &c : s)
        {
            c = tolower(c);
        }
        return s;
    }

    void addPatient(int id, string name, int age, string disease)
    {
        Patient p;
        p.name = name;
        p.id = id;
        p.age = age;
        p.disease = disease;

        patients[id] = p;

        cout << "Patient added successfully! Patient ID: " << id << endl;
    }
    void searchPatient(int id)
    {
        auto it = patients.find(id);
        if (it == patients.end())
        {
            cout << "Patient not found!" << endl;
            return;
        }

        const Patient &p = it->second;
        cout << string(90, '-') << endl;

        cout << left
             << setw(20) << "Patient Id"
             << setw(20) << "Name"
             << setw(20) << "Age"
             << setw(20) << "Patient Disease" << endl;

        cout << string(90, '-') << endl;

        cout << left
             << setw(20) << p.id
             << setw(20) << p.name
             << setw(20) << p.age
             << setw(20) << p.disease << endl;

        cout << string(90, '-') << endl;
        if (p.assignedDoctorId != -1)
            cout << "Assigned Doctor ID: " << p.assignedDoctorId << endl;
        else
            cout << "No doctor assigned yet" << endl;
    }

    void addDoctor(int id, string name, string specialization, string department)
    {
        Doctor d;
        d.id = id;
        d.name = name;
        d.specialization = toLower(specialization);
        d.department = department;

        doctors[id] = d;

        cout << "Doctor added Successfully!" << endl;
    }

    void viewDoctor(int id)
    {
        if (doctors.find(id) == doctors.end())
        {
            cout << "Doctor not found!" << endl;
            return;
        }
        Doctor &d = doctors[id];
        cout << "\n"
             << string(60, '-') << "\n";
        cout << left
             << setw(10) << "ID"
             << setw(20) << "Name"
             << setw(20) << "Specialization"
             << "Dept" << endl;
        cout << string(60, '-') << "\n";
        cout << left << setw(10) << d.id << setw(20) << d.name << setw(20) << d.specialization << d.department << endl;
    }

    string getSpecializationForDisease(string disease)
    {
        disease = toLower(disease);

        if (disease == "heart")
            return "Cardiologist";
        if (disease == "skin")
            return "Dermatologist";
        if (disease == "eye")
            return "Ophthalmologist";

        return "General Physician";
    }

    void assignDoctor(int patientId)
    {
        auto pit = patients.find(patientId);

        if (pit == patients.end())
        {
            cout << "Patient not found!" << endl;
            return;
        }

        string requiredSpec = toLower(getSpecializationForDisease(pit->second.disease));

        for (const auto &pair : doctors)
        {
            if (pair.second.specialization == requiredSpec)
            {
                pit->second.assignedDoctorId = pair.second.id; // ✅ correct place

                cout << "Doctor Assigned Successfully!" << endl;
                cout << "Patient: " << pit->second.name << endl;
                cout << "Doctor: " << pair.second.name << endl;
                cout << "Specialization: " << requiredSpec << endl;
                return;
            }
        }

        cout << "No doctor available for specialization: "
             << requiredSpec << endl;
    }
};
int main()
{
    HospitalManagement h;
    int choice;
    int nextPatientId = 1;
    int nextDoctorId = 101;

    while (true)
    {
        cout << "\n--- Hospital Management System ---\n";
        cout << "1. Add Patient\n2. Search Patient\n3. Add Doctor\n4. View Doctor\n0. Exit\nChoice: ";
        cin >> choice;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (choice == 0)
        {
            cout << "Thank you for visiting, Bye Bye!" << endl;
            break;
        }
        string name, disease, dName, spec, dept;
        int age, sId, dId;

        switch (choice)
        {
        case 1:
        {
            cout << "Name: ";
            getline(cin, name);
            cout << "Age: ";
            cin >> age;
            cin.ignore();
            cout << "Disease: ";
            getline(cin, disease);
            int currentId = nextPatientId;
            h.addPatient(currentId, name, age, disease);
            h.assignDoctor(currentId);
            nextPatientId++;
            break;
        }

        case 2:
        {
            cout << "Enter Patient ID to search: ";
            cin >> sId;
            h.searchPatient(sId);
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        }
        case 3:
        {

            cout << "Doctor Name: ";
            getline(cin, dName);
            cout << "Specialization: ";
            getline(cin, spec);
            cout << "Department: ";
            getline(cin, dept);
            h.addDoctor(nextDoctorId++, dName, spec, dept);
            break;
        }

        case 4:
        {
            cout << "Enter Doctor ID: ";
            cin >> dId;
            h.viewDoctor(dId);
            break;
        }
        }
    }

    return 0;
}