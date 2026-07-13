#include <iostream>
#include <cstdio>
#include <fstream>
#include <string>

using namespace std;

// Function Declarations
void registerUser();
void loginUser();
void changePassword();
void forgotPassword();
void deleteAccount();
void viewUsers();
void totalUsers();
bool userExists(string username);

// Check if username already exists
bool userExists(string username)
{
    ifstream file("users.txt");

    string user, pass, answer;

    while (file >> user >> pass >> answer)
    {
        if (user == username)
        {
            file.close();
            return true;
        }
    }

    file.close();
    return false;
}

// ================= REGISTER =================

void registerUser()
{
    string username;
    string password;
    string confirmPassword;
    string securityAnswer;

    cout << "\n========== REGISTER ==========\n";

    cout << "Enter Username : ";
    cin >> username;

    if (userExists(username))
    {
        cout << "\nUsername already exists.\n";
        return;
    }

    cout << "Enter Password : ";
    cin >> password;

    if (password.length() < 6)
    {
        cout << "Password must contain at least 6 characters.\n";
        return;
    }

    cout << "Confirm Password : ";
    cin >> confirmPassword;

    if (password != confirmPassword)
    {
        cout << "Passwords do not match.\n";
        return;
    }

    cout << "\nSecurity Question\n";
    cout << "What is your favourite color?\n";
    cout << "Answer : ";
    cin >> securityAnswer;

    ofstream file("users.txt", ios::app);

    file << username << " "
         << password << " "
         << securityAnswer << endl;

    file.close();

    cout << "\nRegistration Successful!\n";
}

// ================= LOGIN =================

void loginUser()
{
    string username;
    string password;

    string user;
    string pass;
    string answer;

    cout << "\n========== LOGIN ==========\n";

    cout << "Username : ";
    cin >> username;

    cout << "Password : ";
    cin >> password;

    ifstream file("users.txt");

    while (file >> user >> pass >> answer)
    {
        if (username == user && password == pass)
        {
            cout << "\nLogin Successful!\n";
            cout << "Welcome " << username << "!\n";

            file.close();
            return;
        }
    }

    file.close();

    cout << "\nInvalid Username or Password.\n";
}
// ================= CHANGE PASSWORD =================

void changePassword()
{
    string username, oldPassword, newPassword;
    string user, pass, answer;

    cout << "\n========== CHANGE PASSWORD ==========\n";

    cout << "Enter Username : ";
    cin >> username;

    cout << "Enter Old Password : ";
    cin >> oldPassword;

    ifstream file("users.txt");
    ofstream temp("temp.txt");

    bool found = false;

    while (file >> user >> pass >> answer)
    {
        if (user == username && pass == oldPassword)
        {
            found = true;

            cout << "Enter New Password : ";
            cin >> newPassword;

            if (newPassword.length() < 6)
            {
                cout << "Password must contain at least 6 characters.\n";
                temp << user << " " << pass << " " << answer << endl;
            }
            else
            {
                temp << user << " " << newPassword << " " << answer << endl;
                cout << "\nPassword Changed Successfully.\n";
            }
        }
        else
        {
            temp << user << " " << pass << " " << answer << endl;
        }
    }

    file.close();
    temp.close();

    remove("users.txt");
    rename("temp.txt", "users.txt");

    if (!found)
    {
        cout << "\nInvalid Username or Password.\n";
    }
}

// ================= FORGOT PASSWORD =================

void forgotPassword()
{
    string username;
    string securityAnswer;

    string user, pass, answer;

    cout << "\n========== FORGOT PASSWORD ==========\n";

    cout << "Enter Username : ";
    cin >> username;

    cout << "Answer Security Question\n";
    cout << "What is your favourite color?\n";
    cout << "Answer : ";
    cin >> securityAnswer;

    ifstream file("users.txt");
    ofstream temp("temp.txt");

    bool found = false;

    while (file >> user >> pass >> answer)
    {
        if (user == username && answer == securityAnswer)
        {
            found = true;

            string newPassword;

            cout << "Enter New Password : ";
            cin >> newPassword;

            temp << user << " " << newPassword << " " << answer << endl;

            cout << "\nPassword Reset Successfully.\n";
        }
        else
        {
            temp << user << " " << pass << " " << answer << endl;
        }
    }

    file.close();
    temp.close();

    remove("users.txt");
    rename("temp.txt", "users.txt");

    if (!found)
    {
        cout << "\nUsername or Security Answer is incorrect.\n";
    }
}

// ================= DELETE ACCOUNT =================

void deleteAccount()
{
    string username;
    string password;

    string user, pass, answer;

    char choice;

    cout << "\n========== DELETE ACCOUNT ==========\n";

    cout << "Enter Username : ";
    cin >> username;

    cout << "Enter Password : ";
    cin >> password;

    cout << "Are you sure? (Y/N) : ";
    cin >> choice;

    if (choice != 'Y' && choice != 'y')
    {
        cout << "\nAccount Deletion Cancelled.\n";
        return;
    }

    ifstream file("users.txt");
    ofstream temp("temp.txt");

    bool found = false;

    while (file >> user >> pass >> answer)
    {
        if (user == username && pass == password)
        {
            found = true;
            continue;
        }

        temp << user << " " << pass << " " << answer << endl;
    }

    file.close();
    temp.close();

    remove("users.txt");
    rename("temp.txt", "users.txt");

    if (found)
        cout << "\nAccount Deleted Successfully.\n";
    else
        cout << "\nInvalid Username or Password.\n";
}
// ================= VIEW USERS =================

void viewUsers()
{
    ifstream file("users.txt");

    string user, pass, answer;

    int count = 1;

    cout << "\n========== REGISTERED USERS ==========\n";

    while (file >> user >> pass >> answer)
    {
        cout << count << ". " << user << endl;
        count++;
    }

    if (count == 1)
    {
        cout << "No users found.\n";
    }

    file.close();
}

// ================= TOTAL USERS =================

void totalUsers()
{
    ifstream file("users.txt");

    string user, pass, answer;

    int count = 0;

    while (file >> user >> pass >> answer)
    {
        count++;
    }

    file.close();

    cout << "\nTotal Registered Users : " << count << endl;
}

// ================= MAIN FUNCTION =================

int main()
{
    int choice;

    do
    {
        cout << "\n";
        cout << "==========================================\n";
        cout << "      LOGIN & REGISTRATION SYSTEM\n";
        cout << "==========================================\n";
        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "3. Change Password\n";
        cout << "4. Forgot Password\n";
        cout << "5. Delete Account\n";
        cout << "6. View Registered Users\n";
        cout << "7. Total Registered Users\n";
        cout << "8. Exit\n";
        cout << "==========================================\n";
        cout << "Enter your choice : ";

        cin >> choice;

        switch (choice)
        {
        case 1:
            registerUser();
            break;

        case 2:
            loginUser();
            break;

        case 3:
            changePassword();
            break;

        case 4:
            forgotPassword();
            break;

        case 5:
            deleteAccount();
            break;

        case 6:
            viewUsers();
            break;

        case 7:
            totalUsers();
            break;

        case 8:
            cout << "\nThank you for using the system.\n";
            break;

        default:
            cout << "\nInvalid Choice! Please try again.\n";
        }

    } while (choice != 8);

    return 0;
}