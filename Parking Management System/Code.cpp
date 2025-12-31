// creating a parking management system which includes admin and user role
// admin role includes: slot registration, vacant space count and store details of every vehicles
// user role include: can check the vacant slot, can find out his vehicle slot, can pay parking charges
#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <ctime>
#include <limits>
#include <bits/stdc++.h>
using namespace std;

class Vehicle
{
public:
    string vehicleNumber;
    string ownerName;
    int slotId = -1;
};

class Slot
{
public:
    int slotId;
    bool isOccupied;
    string vehicleNumber;
    time_t parkedAt;

    Slot() {}

    Slot(int id)
    {
        slotId = id;
        isOccupied = false;
        parkedAt = 0;
    }
};
class ParkingManagement
{
private:
    vector<Slot> slots;
    unordered_map<string, Vehicle> parkedVehicles;
    int totalSlots;
    int occupiedSlot = 0;

public:
    void addSlot()
    {
        slots.push_back(Slot(slots.size() + 1));
        totalSlots++;
    }
    int getVehicleSlot(string vehicleNumber)
    {
        auto it = parkedVehicles.find(vehicleNumber);
        if (it == parkedVehicles.end())
            return -1;
        return it->second.slotId;
    }

    ParkingManagement(int totalSlots)
    {
        this->totalSlots = totalSlots;
        for (int i = 0; i < totalSlots; i++)
        {
            slots.push_back((Slot(i + 1)));
        }
    }

    int getVacantSlotCount()
    {
        return slots.size() - occupiedSlot;
    }
    bool parkVehicle(Vehicle &v)
    {
        // 1. Check if vehicle already parked
        if (parkedVehicles.find(v.vehicleNumber) != parkedVehicles.end())
        {
            cout << "Vehicle already parked!\n";
            return false;
        }

        // 2. Find vacant slot
        for (auto &slot : slots)
        {
            if (!slot.isOccupied)
            {
                slot.isOccupied = true;
                slot.vehicleNumber = v.vehicleNumber;
                slot.parkedAt = time(nullptr);

                v.slotId = slot.slotId;
                parkedVehicles[v.vehicleNumber] = v;

                occupiedSlot++;
                cout << "Vehicle parked at slot " << slot.slotId << endl;
                return true;
            }
        }

        cout << "No vacant slots available!\n";
        return false;
    }

    bool removeVehicle(string vehicleNumber)
    {
        auto it = parkedVehicles.find(vehicleNumber);
        if (it == parkedVehicles.end())
        {
            cout << "Vehicle not found!\n";
            return false;
        }

        int slotId = it->second.slotId;

        for (auto &slot : slots)
        {
            if (slot.slotId == slotId)
            {
                slot.isOccupied = false;
                slot.vehicleNumber = "";
                slot.parkedAt = 0;
                break;
            }
        }

        parkedVehicles.erase(it);
        if (occupiedSlot > 0)
            occupiedSlot--;

        return true;
    }

    int calculateCharges(string vehicleNumber)
    {
        const int RATE_PER_HOUR = 10;

        auto it = parkedVehicles.find(vehicleNumber);
        if (it == parkedVehicles.end())
        {
            cout << "Vehicle not found!\n";
            return 0;
        }

        int slotId = it->second.slotId;
        time_t parkedAt = 0;

        for (auto &slot : slots)
        {
            if (slot.slotId == slotId)
            {
                parkedAt = slot.parkedAt;
                break;
            }
        }
        if (parkedAt == 0)
            return 0;

        time_t currentTime = time(nullptr);
        int hours = max(1, int((currentTime - parkedAt) / 3600));
        return hours * RATE_PER_HOUR;
    }

    void displayStatus()
    {
        cout << "Vehicle\tSlot\n";
        for (auto &p : parkedVehicles)
        {
            cout << p.second.vehicleNumber << "\t" << p.second.slotId << endl;
        }
    }
};

class User
{
public:
    void requestParking(ParkingManagement &pm, Vehicle &v)
    {
        pm.parkVehicle(v);
    }
    void findMySlot(ParkingManagement &pm, string vehicleNumber)
    {
        int slot = pm.getVehicleSlot(vehicleNumber);
        if (slot == -1)
            cout << "Vehicle not found\n";
        else
            cout << "Your slot is: " << slot << endl;
    }
    void payCharges(ParkingManagement &pm, string vehicleNumber)
    {
        int charge = pm.calculateCharges(vehicleNumber);
        cout << "Parking charge: ₹" << charge << endl;
    }
};

class Admin
{
public:
    void addSlot(ParkingManagement &pm)
    {
        pm.addSlot();
    }
    void viewStatus(ParkingManagement &pm)
    {
        pm.displayStatus();
    }
};

int main()
{
    ParkingManagement pm(5); // initial slots

    while (true)
    {
        cout << "\n<------------ Parking Menu ------------>\n";
        cout << "1. Add Slot\n";
        cout << "2. Park Vehicle\n";
        cout << "3. Remove Vehicle\n";
        cout << "4. Find Vehicle Slot\n";
        cout << "5. Get Vacant Slot Count\n";
        cout << "6. Calculate Charges\n";
        cout << "7. Display Status\n";
        cout << "0. Exit\n";

        int choice;
        cin >> choice;

        if (choice == 0)
            break;

        if (choice == 1)
        {
            pm.addSlot();
            cout << "Slot added successfully\n";
        }
        else if (choice == 2)
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            Vehicle v;
            cout << "Enter vehicle number: ";
            getline(cin, v.vehicleNumber);
            cout << "Enter owner name: ";
            getline(cin, v.ownerName);

            pm.parkVehicle(v);
        }
        else if (choice == 3)
        {
            string vehicleNumber;
            cout << "Enter vehicle number: ";
            getline(cin, vehicleNumber);

            pm.removeVehicle(vehicleNumber);
        }
        else if (choice == 4)
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            string vehicleNumber;
            cout << "Enter vehicle number: ";
            getline(cin, vehicleNumber);

            int slot = pm.getVehicleSlot(vehicleNumber);
            if (slot == -1)
                cout << "Vehicle not found\n";
            else
                cout << "Vehicle parked at slot " << slot << endl;
        }
        else if (choice == 5)
        {
            cout << "Vacant slots: " << pm.getVacantSlotCount() << endl;
        }
        else if (choice == 6)
        {
            string vehicleNumber;
            cout << "Enter vehicle number: ";
            getline(cin, vehicleNumber);

            cout << "Charge: ₹" << pm.calculateCharges(vehicleNumber) << endl;
        }
        else if (choice == 7)
        {
            pm.displayStatus();
        }
        else
        {
            cout << "Invalid choice!\n";
        }
    }

    return 0;
}
