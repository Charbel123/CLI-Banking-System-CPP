#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

int loggedUser = -1;
string filename = "usersDB.txt";

class User;
void registerUser(vector<User> &users);
void logout(const string &filename, vector<User> &users);


enum UserType
{
  ADMIN,
  NORMAL
};

class User
{
private:
  int ID;
  string username;
  string password;
  float balance;
  UserType userType;

public:
  User(int ID, string username, string password, float balance, UserType utype) : ID(ID), username(username), password(password), balance(balance), userType(utype) {}
  
  void changePassword()
  {
    string oldPassword, newPassword, newPasswordCheck;
    cout << "Enter old password: ";
    cin >> oldPassword;

    if (oldPassword != password)
    {
      cout << "Incorrect Password. Failed.\n";
      return;
    }

    do
    {
      cout << "Enter new password: ";
      cin >> newPassword;
      cout << "Confirm new password: ";
      cin >> newPasswordCheck;

      if (newPassword == newPasswordCheck)
      {
        cout << "Password changed successfully.\n";
        password = newPassword;
      }
      else
      {
        cout << "Passwords do not match. Try again.\n";
      }
    } while (newPassword != newPasswordCheck);
  }

  void withdraw()
  {
    float amt;
    cout << "Enter amount to withdraw: ";
    cin >> amt;

    if (amt > balance)
    {
      cout << "Insufficient funds in your account for this transaction.\n";
      return;
    }

    balance -= amt;
    cout << "Transaction successful.\n";
  }

  void deposit()
  {
    float amt;
    cout << "Enter amount to deposit: ";
    cin >> amt;

    balance += amt;
    cout << "Transaction successful.\n";
  }

  void deposit(vector<User> &users)
  {
    string username;
    float amt;
    cout << "Who do you want to deposit for: ";
    cin >> username;

    bool userFound = false;
    do
    {
      for (User &user : users)
      {
        if (username == user.getUsername())
        {
          userFound = true;
          user.deposit();
          break;
        }
      }

      if (!userFound)
      {
        cout << "User not found. Transaction failed. Try again.\n";
      }
    } while (!userFound);
  }

  void checkBalance() const
  {
    cout << "Your current balance is: " << balance << endl;
  }

  void showMenu(vector<User> &users) {
    if (userType == ADMIN) {
      cout << "\n--- Admin Menu ---\n";
      cout << "1. Deposit money for Client\n2. Register new client\n3. Change password\n4. Logout\n";
      cout << "Enter your choice: ";
      int choice;
      cin >> choice;
      switch (choice) {
        case 1:
          deposit(users);
          break;
        case 2:
          registerUser(users);
          break;
        case 3:
          this->changePassword();
          break;
        case 4:
          logout(filename, users);
          break;
        default:
          cout << "Invalid choice. Please try again.\n";
      }
    } else {
      cout << "\n--- Client Menu ---\n";
      cout << "1. Withdraw cash\n2. Deposit money\n3. Check Balance\n4. Change password\n5. Logout\n";
      cout << "Enter your choice: ";
      int choice;
      cin >> choice;
      switch (choice) {
        case 1:
          this->withdraw();
          break;
        case 2:
          this->deposit();
          break;
        case 3:
          this->checkBalance();
          break;
        case 4:
          this->changePassword();
          break;
        case 5:
          logout(filename, users);
          break;
        default:
          cout << "Invalid choice. Please try again.\n";
      }
    }
  }
  
  // Getters for private members. These are used to access private members from outside the class
  int getID() const
  {
    return ID;
  }
  string getUsername() const
  {
    return username;
  }
  string getPassword() const
  {
    return password;
  }
  float getBalance() const
  {
    return balance;
  }
  UserType getUType() const
  {
    return userType;
  }
};

int generateID()
{
  string IDStr;

  for (int i = 0; i < 8; i++)
  {
    IDStr += to_string(rand() % 11);
  }

  return stoi(IDStr);
}

void saveData(const string &filename, const vector<User> &users)
{
  ofstream outFile(filename);
  if (!outFile.is_open())
  {
    cerr << "Error occurred while saving." << endl;
    return;
  }

  for (const User &user : users)
  {
    outFile << user.getID() << "," << user.getUsername() << "," << user.getPassword() << "," << user.getBalance() << "," << user.getUType() << endl;
  }

  cout << "Data saved successfully." << endl;
}

vector<User> loadData(string &filename)
{
  vector<User> users;
  ifstream inFile(filename);

  if (!inFile.is_open())
  {
    cout << "File: " << filename << " not found. Creating a new one...\n";
    ofstream createFile(filename);

    User adminUser(generateID(), "admin", "admin123", 0.0, ADMIN);
    users.push_back(adminUser);
    saveData(filename, users);

    createFile.close();
  }

  string line, IDStr, username, password, balanceStr, UTypeStr;
  while (getline(inFile, line))
  {
    istringstream ss(line);

    getline(ss, IDStr, ',');
    getline(ss, username, ',');
    getline(ss, password, ',');
    getline(ss, balanceStr, ',');
    getline(ss, UTypeStr);

    int ID = stoi(IDStr);
    float balance = stof(balanceStr);
    UserType uType = static_cast<UserType>(stoi(UTypeStr));

    users.emplace_back(ID, username, password, balance, uType);
  }

  return users;
}

void loginUser(const vector<User> &users)
{
  cout << "Enter username: ";
  string username;
  cin >> username;

  bool userFound = false;
  for (const User &user : users)
  {
    if (user.getUsername() == username)
    {
      userFound = true;
      int index = &user - &users[0]; // Get the index of the user in the vector
      int attempts = 3;
      do
      {
        cout << "Enter password: ";
        string password;
        cin >> password;

        if (password != user.getPassword())
        {
          attempts--;
          cout << "Wrong password. " << attempts << " left.\n";
          continue;
        }

        cout << "Logged in successfully.\n";
        loggedUser = index;
        return;
      } while (attempts != 0);
    }
  }
  if (!userFound)
  {
    cout << "User not found. Consider Registering first?\n";
  }
}

void logout(const string &filename, vector<User> &users)
{
  loggedUser = -1;
  saveData(filename, users);
  cout << "You have successfully logged out.\n";
}

string lcText(string text)
{
  for (int i = 0; i < text.length(); i++)
  {
    text[i] = tolower(text[i]);
  }
  return text;
}

void registerUser(vector<User> &users)
{
  bool userExists;

  string username, utype;
  UserType uType;

  do
  {
    cout << "Enter account type (admin/client): ";
    cin >> utype;
    utype = lcText(utype);
    if (utype != "admin" && utype != "client")
    {
      cout << "Kindly enter either 'admin' or 'client'. Try again.\n";
      continue;
    }

    uType = (utype == "admin") ? ADMIN : NORMAL;
    break;

  } while (true);

  do
  {
    cout << "Enter username: ";
    cin >> username;

    userExists = false;

    for (User& user : users)
    {
      if (user.getUsername() == username)
      {
        userExists = true;
        cout << "Username is already taken. Try again.\n";
        break;
      }
    }
  } while (userExists);

  string password, passwordCheck;
  do
  {
    cout << "Enter your password: ";
    cin >> password;
    cout << "Confirm your password: ";
    cin >> passwordCheck;

    if (password != passwordCheck)
    {
      cout << "Passwords do not match. Try again.\n";
      continue;
    }

  } while (password != passwordCheck);
  
  cout << "You have successfully been registered. You are now logged in.\n";
  users.emplace_back(generateID(), username, password, 0.0, uType);
  loggedUser = users.size() - 1;
}

void displayMenu(vector<User> &users) {
  if (loggedUser == -1) {
    cout << "\n--- User Menu ---\n";
    cout << "1. Admin Login\n2. Client Login\n3. Exit\n";
    cout << "Enter your choice: ";
    int choice;
    cin >> choice;
    switch (choice) {
      case 1:
        loginUser(users);
        break;
      case 2:
        loginUser(users);
        break;
      case 3:
        exit(0);
      default:
        cout << "Invalid choice. Please try again.\n";
    }
  } else {
    users[loggedUser].showMenu(users);
  }
}

int main()
{
  srand(time(0));
  cout << "***WELCOME TO E-CASH SERVICES***\n";
  vector<User> users = loadData(filename);
  while (true)
  {
    displayMenu(users);
  }
  
  return 0;
}