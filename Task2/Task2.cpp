#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Contact 
{
private:
    string name;
    string phoneNumber;

public:
    Contact(const string& name, const string& phoneNumber)
        : name(name), phoneNumber(phoneNumber) {}

    string getName() const 
    {
        return name;
    }

    string getPhoneNumber() const 
    {
        return phoneNumber;
    }

    void showContact() const
    {
        cout << "Name: " << name << ", Phone Number: " << phoneNumber << endl;
    }
};

class ContactList
{
private:
    vector<Contact> contacts;

public:
    void addContact(const string& name, const string& phoneNumber) 
    {
        contacts.push_back(Contact(name, phoneNumber));
        cout << "Contact added.\n";
    }

    void showAllContacts() const
    {
        if (contacts.empty())
        {
            cout << "No contacts available.\n";
            return;
        }

        cout << "Contacts:\n";
        for (const auto& contact : contacts)
        {
            contact.showContact();
        }
    }

    void removeContact(const string& name)
    {
        auto it = remove_if(contacts.begin(), contacts.end(),
            [&name](const Contact& contact)
            {
                return contact.getName() == name;
            });

        if (it != contacts.end())
        {
            contacts.erase(it, contacts.end());
            cout << "Contact removed.\n";
        }
        else
        {
            cout << "Contact not found.\n";
        }
    }
};

void displayMenu()
{
    cout << "\nContact Management System\n";
    cout << "1. Add Contact\n";
    cout << "2. View Contacts\n";
    cout << "3. Delete Contact\n";
    cout << "4. Exit\n";
    cout << "Choose an option: ";
}

int main() {
    ContactList manager;
    int choice;
    string name,
           phoneNumber;

    while (true)
    {
        displayMenu();
        cin >> choice;

        switch (choice) 
        {
        case 1:
            cout << "Enter Name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter Phone Number: ";
            getline(cin, phoneNumber);
            manager.addContact(name, phoneNumber);
            break;
        case 2:
            manager.showAllContacts();
            break;
        case 3:
            cout << "Enter Name to Delete: ";
            cin.ignore();
            getline(cin, name);
            manager.removeContact(name);
            break;
        case 4:
            cout << "Goodbye!\n";
            return 0;
        default:
            cout << "Invalid option. Please try again.\n";
        }
    }

    return 0;
}
