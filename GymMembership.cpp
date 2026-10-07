#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Person
{
protected:
    int id;
    string name;
    int age;
    string phone;

public:
    Person()
    {
        id = 0;
        name = "";
        age = 0;
        phone = "";
    }

    int getId()
    {
        return id;
    }

    string getName()
    {
        return name;
    }

    void displayPerson()
    {
        cout << "\nMember ID   : " << id;
        cout << "\nName        : " << name;
        cout << "\nAge         : " << age;
        cout << "\nPhone       : " << phone;
    }
};

class Member : public Person
{
private:
    string plan;
    int months;
    float monthlyFee;

public:
    Member() : Person()
    {
        plan = "";
        months = 0;
        monthlyFee = 0;
    }

    void selectPlan(int choice)
    {
        if (choice == 1)
        {
            plan = "Basic";
            monthlyFee = 800;
        }
        else if (choice == 2)
        {
            plan = "Standard";
            monthlyFee = 1200;
        }
        else if (choice == 3)
        {
            plan = "Premium";
            monthlyFee = 1600;
        }
        else
        {
            cout << "\nInvalid plan. Basic plan selected.";
            plan = "Basic";
            monthlyFee = 800;
        }
    }

    void selectPlan(string p)
    {
        plan = p;

        if (plan == "Basic")
            monthlyFee = 800;
        else if (plan == "Standard")
            monthlyFee = 1200;
        else if (plan == "Premium")
            monthlyFee = 1600;
        else
        {
            plan = "Basic";
            monthlyFee = 800;
        }
    }

    void input()
    {
        cout << "\nEnter Member ID: ";
        cin >> id;

        cin.ignore();

        cout << "Enter Name: ";
        getline(cin, name);

        cout << "Enter Age: ";
        cin >> age;

        cout << "Enter Phone Number: ";
        cin >> phone;

        cout << "\n----- MEMBERSHIP PLANS -----";
        cout << "\n1. Basic    - Rs. 800/month";
        cout << "\n2. Standard - Rs. 1200/month";
        cout << "\n3. Premium  - Rs. 1600/month";

        int choice;

        cout << "\nEnter Plan: ";
        cin >> choice;

        selectPlan(choice);

        cout << "Enter Duration (months): ";
        cin >> months;
    }

    float calculateBill()
    {
        return monthlyFee * months;
    }

    // Display complete member information
    void display()
    {
        displayPerson();

        cout << "\nPlan        : " << plan;
        cout << "\nDuration    : " << months << " months";
        cout << "\nMonthly Fee : Rs. " << monthlyFee;
        cout << "\nTotal Bill  : Rs. " << calculateBill();
    }

    void update()
    {
        cin.ignore();

        cout << "\nEnter New Name: ";
        getline(cin, name);

        cout << "Enter New Age: ";
        cin >> age;

        cout << "Enter New Phone Number: ";
        cin >> phone;

        cout << "\nMember details updated successfully.";
    }

    string getPlan()
    {
        return plan;
    }

    int getMonths()
    {
        return months;
    }

    float getMonthlyFee()
    {
        return monthlyFee;
    }

    void save(ofstream &file)
    {
        file << id << endl;
        file << name << endl;
        file << age << endl;
        file << phone << endl;
        file << plan << endl;
        file << months << endl;
        file << monthlyFee << endl;
    }

    void load(ifstream &file)
    {
        file >> id;
        file.ignore();

        getline(file, name);

        file >> age;
        file >> phone;
        file >> plan;
        file >> months;
        file >> monthlyFee;
    }
};

class Gym
{
private:
    Member members[50];
    int count;

public:
    Gym()
    {
        count = 0;
    }

    void addMember()
    {
        if (count >= 50)
        {
            cout << "\nGym is full.";
            return;
        }

        cout << "\n===== ADD MEMBER =====";

        members[count].input();

        count++;

        saveData();

        cout << "\nMember added successfully.";
        cout << "\nData saved automatically.";
    }

    void displayMembers()
    {
        if (count == 0)
        {
            cout << "\nNo members found.";
            return;
        }

        cout << "\n===== ALL MEMBERS =====";

        for (int i = 0; i < count; i++)
        {
            cout << "\n\nMember " << i + 1;
            members[i].display();
        }
    }

    void searchMember()
    {
        int id;

        cout << "\nEnter Member ID to search: ";
        cin >> id;

        for (int i = 0; i < count; i++)
        {
            if (members[i].getId() == id)
            {
                cout << "\n===== MEMBER FOUND =====";
                members[i].display();
                return;
            }
        }
        cout << "\nMember not found.";
    }

    void updateMember()
    {
        int id;

        cout << "\nEnter Member ID to update: ";
        cin >> id;

        for (int i = 0; i < count; i++)
        {
            if (members[i].getId() == id)
            {
                members[i].update();

                saveData();

                cout << "\nData saved automatically.";
                return;
            }
        }
        cout << "\nMember not found.";
    }

    void deleteMember()
    {
        int id;

        cout << "\nEnter Member ID to delete: ";
        cin >> id;

        for (int i = 0; i < count; i++)
        {
            if (members[i].getId() == id)
            {
                for (int j = i; j < count - 1; j++)
                {
                    members[j] = members[j + 1];
                }

                count--;

                saveData();

                cout << "\nMember deleted successfully.";
                cout << "\nData saved automatically.";
                return;
            }
        }

        cout << "\nMember not found.";
    }

    void saveData()
    {
        ofstream file("gym_members.txt");

        if (!file)
        {
            cout << "\nUnable to open file.";
            return;
        }

        for (int i = 0; i < count; i++)
        {
            members[i].save(file);
        }

        file.close();
    }

    void loadData()
    {
        ifstream file("gym_members.txt");

        if (!file)
        {
            return;
        }

        count = 0;

        while (file && count < 50)
        {
            members[count].load(file);

            if (file)
                count++;
        }

        file.close();
    }

    // Menu
    void menu()
    {
        int choice;

        do
        {
            cout << "\n\n--------------------------------";
            cout << "\n      GYM MEMBERSHIP SYSTEM";
            cout << "\n--------------------------------";

            cout << "\n1. Add Member";
            cout << "\n2. Display Members";
            cout << "\n3. Search Member";
            cout << "\n4. Update Member";
            cout << "\n5. Delete Member";
            cout << "\n6. Exit";

            cout << "\n\nEnter your choice: ";
            cin >> choice;

            switch (choice)
            {
            case 1:
                addMember();
                break;

            case 2:
                displayMembers();
                break;

            case 3:
                searchMember();
                break;

            case 4:
                updateMember();
                break;

            case 5:
                deleteMember();
                break;

            case 6:
                saveData();
                cout << "\nThank you for using the Gym Membership System.";
                break;

            default:
                cout << "\nInvalid choice.";
            }

        } while (choice != 6);
    }
};

int main()
{
    Gym gym;

    gym.loadData();

    gym.menu();

    return 0;
}
