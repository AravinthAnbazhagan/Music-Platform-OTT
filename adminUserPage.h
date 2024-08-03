#ifndef ADMINUSERPAGE_H_INCLUDED
#define ADMINUSERPAGE_H_INCLUDED

#include <bits/stdc++.h>
#include "searchUser.h"
#include "userPage.h"
#include "userPage.h"


bool removeFromDatabase(string username) {
    MYSQL* conn = mysql_init(nullptr);
    if (conn == nullptr) {
        cerr << "MySQL initialization failed" << endl;
        return false;
    }

    conn = mysql_real_connect(conn, "localhost", "aravinth", "1234", "soundcloud", 0, nullptr, 0);
    if (conn == nullptr) {
        cerr << "Error connecting to MySQL database: " << mysql_error(conn) << endl;
        return false;
    }

    string query = "DELETE FROM users WHERE username = '" + username + "'";
    if (mysql_query(conn, query.c_str())) {
        cerr << "DELETE failed: " << mysql_error(conn) << endl;
        mysql_close(conn);
        return false;
    }

    mysql_close(conn);
    return true;
}

void deleteUser() {
    string username;
    cout << "Enter username to delete: ";
    cin.ignore();
    getline(cin, username);

        if (removeFromDatabase(username)) {
            cout << "User " << username << " deleted successfully." << endl;
        } else {
            cout << "Failed to delete user " << username << " from database." << endl;
        }

}

void showUserDetails() {
    /*string username;
    cout << "Enter username to show details: ";
    cin.ignore();
    getline(cin, username);*/
    cout << "User Details:" << endl;
    cout << setw(20) << left << "Username";
    cout << setw(25) << left << "Email";
    cout << setw(15) << left << "Age";
    cout << setw(15) << left << "User Type" << endl;

    for (const auto& user : users) {
        //if (user.getUsername()== username) {
            cout << setw(20) << left << user.getUsername();
            cout << setw(25) << left << user.getEmail();
            cout << setw(15) << left << user.getAge() ;
            cout << setw(15) << left << user.getUserType()<< endl;
            //return;
        //}
    }
    cout << endl;
}

void manageUsersMenu() {
    int choice;
    string username;
    AVLTree<User> myAVL;
    User* user;
    do {
        cout << "\nManage Users Menu" << endl;
        cout << "1. Delete User" << endl;
        cout << "2. Show User Details" << endl;
        cout << "3. Search User" << endl;
        cout << "4. Back to Admin Menu" << endl;
        cout << "Please select an option (1-4): ";
        cin >> choice;

        switch (choice) {
            case 1:
                deleteUser();
                loadUsers();
                break;
            case 2: {
                showUserDetails();
                break;
            }
            case 3:
                loadUsers();


                for (int i=0; i<users.size(); i++){
                    myAVL.insert(users[i]);
                }

                cout << "Enter Username     : ";
                cin >> username;

                cout << "\n";

                user = myAVL.searchByUsername(username);
                if (user) {
                    cout << "User Found\n";
                } else {
                    cout << "User Not Found\n";               }
                break;
            case 4:
                cout << "Returning to Admin Menu..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 4);
}

#endif // ADMINUSERPAGE_H_INCLUDED
