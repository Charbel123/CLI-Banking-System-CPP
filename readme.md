# Banking System (Procedural C++) - Documentation

## ✨ Project Overview

This is a simple console-based banking system implemented in C++ using procedural programming. It allows admins and clients to log in, manage user accounts, perform transactions like deposit and withdrawal, and track balances. The system simulates real-world banking logic with file-based data storage and basic security checks.

---

## 🎯 Objectives

* Simulate a banking system in a simple, clear way.
* Allow registration and management of users.
* Provide admin/client account types with different permissions.
* Demonstrate file handling and persistent storage.
* Practice procedural programming principles.

---

## 🔑 Features

| Feature               | Description                                                               |
| --------------------- | ------------------------------------------------------------------------- |
| **User Registration** | Admins can create new client or admin accounts.                           |
| **Login System**      | Users can log in with a username and password.                            |
| **Admin Menu**        | Admins can deposit for users, register users, change password, or logout. |
| **Client Menu**       | Clients can deposit, withdraw, check balance, change password, or logout. |
| **Data Persistence**  | Data is saved to and loaded from a file (`usersDB.txt`).                  |
| **Session Control**   | Logged-in user is tracked using an index.                                 |
| **Password Security** | Passwords must be confirmed during registration or password change.       |
| **Exit Option**       | Program exits cleanly with option 3 on main menu.                         |

---

## 📊 Program Structure

```
main.cpp
|
├── main()                     // Entry point
│   └── while loop             // Repeats menu based on login state
|
├── displayMenu()             // Shows menus based on user type
├── registerUser()            // Adds new users
├── loginUser()               // Authenticates existing users
├── logout()                  // Saves data and resets session
|
├── withdraw(), deposit(), checkBalance(), changePassword()
├── saveData(), loadData()   // File handling
├── lcText()                 // Lowercases strings
└── generateID()             // Generates unique 8-digit ID
```

---

## 📃 File Storage Format

Data is stored in a plain text file `usersDB.txt`.

**Format per line:**

```
ID,username,password,balance,userType
```

**Example:**

```
10384729,jane,secure123,1500.00,1
```

* `userType = 0` means Admin
* `userType = 1` means Client

---

## 🧰 How It Works (User Scenarios)

### 👨‍💼 Admin Login & Actions

1. Launch program
2. Select `1. Admin Login`
3. Enter correct username/password
4. Access admin menu:

   * Deposit money for a client
   * Register new user
   * Change password
   * Logout

### 💳 Client Actions

1. Select `2. Client Login`
2. Enter credentials
3. Perform any of:

   * Withdraw money
   * Deposit money
   * Check balance
   * Change password
   * Logout

### 📅 Registering New Users

* Only admins can register new users
* Username must be unique
* Password must be confirmed
* New user is logged in after registration

---

## 🔄 Important Concepts

* **Procedural Logic:** No classes/structs. Logic is broken into small functions.
* **File I/O:** Uses `ifstream` and `ofstream` to persist data.
* **Session State:** Tracks current user via index `loggedUser`.
* **Random ID Generation:** Uses `rand()` and `time(0)` in `main()` to seed randomness.

---

## 🚀 How to Compile and Run

### Using Terminal:

```bash
g++ -o bankingSystem main.cpp
./bankingSystem
```

### On Visual Studio:

* Open the project.
* Press `Ctrl + F5` to build and run.

---

## ⚠️ Notes and Best Practices

* Run program in the same folder as `usersDB.txt`.
* Always logout to ensure data is saved.
* Only admins can register other users.
* Use strong passwords.

---

## 📄 Contribution Guide (For Group Members)

* You can add more features as new `void` functions.
* Follow naming convention and comment clearly.
* To add a new menu option:

  1. Add it to `displayMenu()` or relevant menu.
  2. Implement logic in a new function.
  3. Update file saving if needed.

---

## 🎉 Final Note

This system is a foundational project for understanding user management, file handling, and menu-driven console interfaces. It's ideal for group projects or beginner training. Feel free to modify or expand its capabilities!
