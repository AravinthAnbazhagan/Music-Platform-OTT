#ifndef ADMINPROVIDERPAGE_H_INCLUDED
#define ADMINPROVIDERPAGE_H_INCLUDED


#include <bits/stdc++.h>
#include "searchProvider.h"
#include "providerActivePage.h"
#include "providerPage.h"


bool removeFromProviderVector(const string& username) {
    for (auto it = providers.begin(); it != providers.end(); ++it) {
        if (it->getUsername() == username) {
            providers.erase(it);
            return true;
        }
    }
    return false;
}

bool removeFromProviderDatabase(const string& username) {
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

    string query = "DELETE FROM providers WHERE name = '" + username + "'";
    if (mysql_query(conn, query.c_str())) {
        cerr << "DELETE failed: " << mysql_error(conn) << endl;
        mysql_close(conn);
        return false;
    }

    mysql_close(conn);
    return true;
}

void deleteProvider() {
    string username;
    cout << "Enter provider username to delete: ";
    cin.ignore();
    getline(cin, username);

    if (removeFromProviderVector(username)) {
        if (removeFromProviderDatabase(username)) {
            cout << "Provider " << username << " deleted successfully." << endl;
        } else {
            cout << "Failed to delete provider " << username << " from database." << endl;
        }
    } else {
        cout << "Provider " << username << " not found in vector." << endl;
    }
}

void showProviderDetails() {
    /*string name;
    cout << "Enter provider name to show details: ";
    cin.ignore();
    getline(cin, name);*/
    cout << "Provider Details:" << endl;
    cout << setw(25) << left << "Name";
    cout << setw(20) << left << "Password";
    cout << setw(15) << left << "License Status" << endl;
    //cout << setw(25) << left << "License Expiry Date" << endl;

    for (auto provider : providers) {
        //if (provider.getUsername() == name) {
            string active = (provider.checkLicenseStatus()) ? "Active" : "Inactive";
            cout << setw(25) << left << provider.getUsername();
            cout << setw(20) << left << provider.getPassword();
            cout << setw(15) << left << active << endl;
            //cout << setw(25) << left << provider.getLicenceExpDate() << endl;
            //return;
        //}
    }
    cout << endl;
}

void manageProvidersMenu() {
    int choice;
    Provider* foundProvider;
    AVLProviderTree tree;
    string username;
    do {
        cout << "\nManage Providers Menu" << endl;
        cout << "1. Delete Provider" << endl;
        cout << "2. Show Provider Details" << endl;
        cout << "3. Search Provider" << endl;
        cout << "4. Back to Admin Menu" << endl;
        cout << "Please select an option (1-4): ";
        cin >> choice;

        switch (choice) {
            case 1:
                deleteProvider();
                loadProviders();
                break;
            case 2:
                showProviderDetails();
                break;
            case 3:


                cout << "Enter Username     : ";
                cin >> username;

                cout << "\n";

                loadProviders();



                for(auto provider: providers) {
                    tree.insert(provider);
                }

                foundProvider = tree.find(username);


                if (foundProvider) {
                    cout << "Provider Found\n\n";
                } else {
                    cout << "Provider Not Found\n\n";
                }
                break;
            case 4:
                cout << "Returning to Admin Menu..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 4);
}


#endif // ADMINPROVIDERPAGE_H_INCLUDED
