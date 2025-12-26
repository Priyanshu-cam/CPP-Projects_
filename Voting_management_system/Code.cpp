// creating a voting management system where i will use classes as Voter, Party and votingSystem;

#include <bits/stdc++.h>
using namespace std;

class Voter
{
public:
    int voterId;
    string name;
    int age;
    bool hasVoted;
    string phoneNumber;
    bool verified;

    Voter(int id, string name, int age, string number)
    {
        this->voterId = id;
        this->name = name;
        this->age = age;
        this->hasVoted = false;
        this->phoneNumber = number;
        this->verified = false;
    }
    Voter() {};


};

class Party
{
public:
    string partyName;
    string partyId;
    int voteCount;

    Party(string id, string name)
    {
        partyId = id;
        partyName = name;
        voteCount = 0;
    }
    Party() {};

};

class VotingSystem
{
private:
    map<int, Voter> voters;
    map<string, Party> parties;
    set<string> registeredPhones;

public:
    // Add Voter method (admin only)
    void addVoter(const string &name, int age, string phoneNumber)
    {
        static long int id = 11012201;

        if (age < 18)
        {
            cout << "Voter must be at least 18 years old." << endl;
            return;
        }
        if (phoneNumber.length() != 10)
        { // should have length = 10
            cout << "Phone number must be exactly 10 digits.\n";
            return;
        }

        for (char ch : phoneNumber)
        {
            if (!isdigit(ch))
            {
                cout << "Phone Number must contain digits only" << endl;
                return;
            }
        }
        bool allSame = true; // does not contains same digits
        for (int i = 1; i < 10; i++)
        {
            if (phoneNumber[i] != phoneNumber[0])
            {
                allSame = false;
                break;
            }
        }

        if (allSame)
        {
            cout << "Invalid Phone Number!" << endl;
            return;
        }
        if (registeredPhones.count(phoneNumber))
        {
            cout << "Phone number already registered.\n";
            return;
        }
        registeredPhones.insert(phoneNumber);

        Voter newVoter(id, name, age, phoneNumber);
       voters.emplace(id, Voter(id, name, age, phoneNumber));


        cout << "Voter registered successfully!" << endl;
        cout << "Voter Id: " << id << endl;
        id++;
    }
    void deleteVoter(long int voterId)
    {
        auto it = voters.find(voterId);
        if (it == voters.end())
        {
            cout << "User does not exist\n";
            return;
        }
        if (it->second.hasVoted)
        {
            cout << "Cannot delete voter after voting.\n";
            return;
        }

        voters.erase(it);
        cout << "Account with " << voterId << " deleted successfully\n";
    }

    void addParty(const string &name)
    {
        static int id = 100;
        string partyId;
        do
        {
            partyId = to_string(id) + "BS" + to_string(id + 23) + "EA";
            id++;
        } while (parties.find(partyId) != parties.end());

        Party newParty(partyId, name);
        parties.emplace(partyId, Party(partyId, name));
        cout << "Party registered successfully!\n";
    }
    // KYC verification method
    void KYCVerification(long int voterId)
    {
        if (voters.find(voterId) == voters.end())
        {
            cout << "Voter not found" << endl;
            return;
        }

        Voter &voter = voters[voterId];
        if (voter.verified)
        {
            cout << "User is already verified\n";
            return;
        }
        voter.verified = true;
        cout << "Voter verified successfully\n";
    }

    void castVote(long int voterId, const string &partId)
    {
        if (voters.find(voterId) == voters.end())
        {
            cout << "Invalid voter ID." << endl;
            return;
        }

        if (parties.find(partId) == parties.end())
        {
            cout << "Invalid party" << endl;
            return;
        }

        Voter &voter = voters[voterId];

        if (!voter.verified)
        {
            cout << "Voter is not verified, KYC required" << endl;
            return;
        }

        if (voter.hasVoted)
        {
            cout << "Voter has already voted." << endl;
            return;
        }

        parties[partId].voteCount++;
        voter.hasVoted = true;

        cout << "Vote cast successfully." << endl;
    }
    void deleteParty(string partyId)
    {
        auto it = parties.find(partyId);

        if (it == parties.end())
        {
            cout << "User with " << partyId << " does not exist\n";
            return;
        }

        if (it->second.voteCount > 0)
        {
            cout << "Cannot delete party after votes are cast.\n";
            return;
        }

        if (it == parties.end())
        {
            cout << "User with " << partyId << " does not exist\n";
            return;
        }

        parties.erase(it);
        cout << "Account with " << partyId << " deleted successfully\n";
    }

    void displayResult()
    {
        if (parties.empty())
        {
            cout << "No parties available.\n";
            return;
        }

        bool anyVote = false;
        for (auto &p : parties)
        {
            if (p.second.voteCount > 0)
            {
                anyVote = true;
                break;
            }
        }

        if (!anyVote)
        {
            cout << "No votes cast yet.\n";
            return;
        }
        auto it = max_element(
            parties.begin(),
            parties.end(),
            [](const auto &a, const auto &b)
            {
                return a.second.voteCount < b.second.voteCount;
            });

        if (it != parties.end())
        {
            cout << "Winner Party ID: " << it->first << " (" << it->second.partyName << ")" << endl;

            cout << "Votes: " << it->second.voteCount << endl;
        }
    }
    void displayAllResults()
    {
        for (auto &p : parties)
        {
            cout << p.second.partyName << " : " << p.second.voteCount << endl;
        }
    }
};

int main()
{
    VotingSystem vs;

    while (true)
    {
        cout << " <---------------- Voting operation menu -------------->" << endl;
        cout << "1. Add Voter" << endl;
        cout << "2. Add Party" << endl;
        cout << "3. Cast Voter/party" << endl;
        cout << "4. Display result" << endl;
        cout << "5. KYC Verification" << endl;
        cout << "6. Delete Voter" << endl;
        cout << "7. Delete Party" << endl;
        cout << "8. View All Result" << endl;
        cout << "9. Exit" << endl;

        int choice;
        cout << "Enter the choice of your operation:\n";
        cin >> choice;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input.Please enter a valid choice" << endl;
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (choice == 9)
        {
            cout << "Thank you for visiting Us, Have a Good Day Ahead!" << endl;
            break;
        }

        string name, phoneNumber, partyName, partyId;
        long int voterId;
        int age;

        switch (choice)
        {
        case 1:
            cout << "Enter name:\n";
            getline(cin, name);

            cout << "Enter your age:\n";
            cin >> age;

            cout << "Enter your phone number:\n";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, phoneNumber);

            vs.addVoter(name, age, phoneNumber);
            break;

        case 2:
            cout << "Enter Party Name:\n";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, partyName);

            vs.addParty(partyName);
            break;

        case 3:
            cout << "Enter voterId:" << endl;
            cin >> voterId;

            cout << "Enter party Id:" << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, partyId);

            vs.castVote(voterId, partyId);
            break;

        case 4:
            vs.displayResult();
            break;

        case 5:
            cout << "Enter your voterId" << endl;
            cin >> voterId;

            vs.KYCVerification(voterId);
            break;

        case 6:
            cout << "Enter your voterId" << endl;
            cin >> voterId;

            vs.deleteVoter(voterId);
            break;

        case 7:
            cout << "Enter partyId" << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, partyId);
            vs.deleteParty(partyId);
            break;

        case 8:
            vs.displayAllResults();
            break;

        default:
            cout << "Invalid Choice" << endl;
        }
    }
    return 0;
}