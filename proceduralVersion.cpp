#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <ctime>

using namespace std;

const int MAX_USERS = 1000;
const string FILENAME = "usersDB.txt";

int loggedUser = -1;

// Arrays to simulate a user database
int IDs[MAX_USERS];
string usernames[MAX_USERS];
string passwords[MAX_USERS];
float balances[MAX_USERS];
int userTypes[MAX_USERS]; // 0 for ADMIN, 1 for NORMAL
int userCount = 0;

int generateID() {
    string IDStr;
    for (int i = 0; i < 8; i++) {
        IDStr += to_string(rand() % 10);
    }
    return stoi(IDStr);
}

string lcText(string text) {
    for (char &c : text) c = tolower(c);
    return text;
}

void saveData() {
    ofstream outFile(FILENAME);
    for (int i = 0; i < userCount; i++) {
        outFile << IDs[i] << "," << usernames[i] << "," << passwords[i] << "," << balances[i] << "," << userTypes[i] << endl;
    }
    outFile.close();
}

void loadData() {
    ifstream inFile(FILENAME);
    if (!inFile.is_open()) {
        ofstream createFile(FILENAME);
        createFile.close();
        return;
    }
    string line;
    while (getline(inFile, line)) {
        stringstream ss(line);
        string IDStr, uname, pwd, balanceStr, typeStr;
        getline(ss, IDStr, ',');
        getline(ss, uname, ',');
        getline(ss, pwd, ',');
        getline(ss, balanceStr, ',');
        getline(ss, typeStr);

        IDs[userCount] = stoi(IDStr);
        usernames[userCount] = uname;
        passwords[userCount] = pwd;
        balances[userCount] = stof(balanceStr);
        userTypes[userCount] = stoi(typeStr);
        userCount++;
    }
    inFile.close();
}

void logout() {
    loggedUser = -1;
    saveData();
    cout << "You have successfully logged out.\n";
}

void changePassword() {
    string oldPassword, newPassword, confirmPassword;
    cout << "Enter old password: ";
    cin >> oldPassword;
    if (oldPassword != passwords[loggedUser]) {
        cout << "Incorrect password.\n";
        return;
    }
    do {
        cout << "Enter new password: ";
        cin >> newPassword;
        cout << "Confirm new password: ";
        cin >> confirmPassword;
    } while (newPassword != confirmPassword);

    passwords[loggedUser] = newPassword;
    cout << "Password changed successfully.\n";
}

void withdraw() {
    float amount;
    cout << "Enter amount to withdraw: ";
    cin >> amount;
    if (amount > balances[loggedUser]) {
        cout << "Insufficient funds.\n";
    } else {
        balances[loggedUser] -= amount;
        cout << "Transaction successful.\n";
    }
}

void deposit() {
    float amount;
    cout << "Enter amount to deposit: ";
    cin >> amount;
    balances[loggedUser] += amount;
    cout << "Transaction successful.\n";
}

void depositForClient() {
    string uname;
    cout << "Enter username to deposit for: ";
    cin >> uname;
    for (int i = 0; i < userCount; i++) {
        if (usernames[i] == uname) {
            float amt;
            cout << "Enter amount: ";
            cin >> amt;
            balances[i] += amt;
            cout << "Transaction successful.\n";
            return;
        }
    }
    cout << "User not found.\n";
}

void checkBalance() {
    cout << "Your current balance is: " << balances[loggedUser] << endl;
}

void registerUser() {
    string uname, pwd, confirmPwd, type;
    int utype;
    do {
        cout << "Enter account type (admin/client): ";
        cin >> type;
        type = lcText(type);
    } while (type != "admin" && type != "client");
    utype = (type == "admin") ? 0 : 1;

    while (true) {
        cout << "Enter username: ";
        cin >> uname;
        bool exists = false;
        for (int i = 0; i < userCount; i++) {
            if (usernames[i] == uname) {
                exists = true;
                cout << "Username already taken.\n";
                break;
            }
        }
        if (!exists) break;
    }

    do {
        cout << "Enter password: ";
        cin >> pwd;
        cout << "Confirm password: ";
        cin >> confirmPwd;
    } while (pwd != confirmPwd);

    IDs[userCount] = generateID();
    usernames[userCount] = uname;
    passwords[userCount] = pwd;
    balances[userCount] = 0.0f;
    userTypes[userCount] = utype;
    loggedUser = userCount;
    userCount++;
    cout << "Registration successful.\n";
}

void loginUser() {
    string uname, pwd;
    cout << "Enter username: ";
    cin >> uname;
    for (int i = 0; i < userCount; i++) {
        if (usernames[i] == uname) {
            int attempts = 3;
            while (attempts--) {
                cout << "Enter password: ";
                cin >> pwd;
                if (pwd == passwords[i]) {
                    loggedUser = i;
                    cout << "Logged in successfully.\n";
                    return;
                }
                cout << "Wrong password. Attempts left: " << attempts << endl;
            }
            return;
        }
    }
    cout << "User not found.\n";
}

void adminMenu() {
    int choice;
    cout << "\n--- Admin Menu ---\n";
    cout << "1. Deposit for Client\n2. Register Client\n3. Change Password\n4. Logout\nEnter choice: ";
    cin >> choice;
    switch (choice) {
        case 1: depositForClient(); break;
        case 2: registerUser(); break;
        case 3: changePassword(); break;
        case 4: logout(); break;
        default: cout << "Invalid choice.\n";
    }
}

void clientMenu() {
    int choice;
    cout << "\n--- Client Menu ---\n";
    cout << "1. Withdraw\n2. Deposit\n3. Check Balance\n4. Change Password\n5. Logout\nEnter choice: ";
    cin >> choice;
    switch (choice) {
        case 1: withdraw(); break;
        case 2: deposit(); break;
        case 3: checkBalance(); break;
        case 4: changePassword(); break;
        case 5: logout(); break;
        default: cout << "Invalid choice.\n";
    }
}

void displayMenu() {
    if (loggedUser == -1) {
        int choice;
        cout << "\n--- Main Menu ---\n";
        cout << "1. Admin Login\n2. Client Login\n3. Exit\nEnter choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
            case 2: loginUser(); break;
            case 3: exit(0);
            default: cout << "Invalid choice.\n";
        }
    } else {
        if (userTypes[loggedUser] == 0)
            adminMenu();
        else
            clientMenu();
    }
}

int main() {
    srand(time(0));
    loadData();
    while (true) {
        displayMenu();
    }
    return 0;
}
