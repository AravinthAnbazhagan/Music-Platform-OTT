#ifndef PROVIDERREGISTER_H_INCLUDED
#define PROVIDERREGISTER_H_INCLUDED

#include <bits/stdc++.h>

using namespace std;

// Registration implementation for providers
void providerRegister() {
    string filename = R"(C:\Users\aravi\Downloads\ascii-text-art (3).txt)";
    ifstream inputFile(filename);
    string line;
    while (std::getline(inputFile, line)) {
        cout << line << endl;
    }
    inputFile.close();
    cout << "\n\n";


    string username, password, confirmPassword, email;

    cout << "Enter Username     : ";
    cin >> username;

    cout << "Enter email        : ";
    cin >> email;

    pwd:
    cout << "Enter Password     : ";
    cin >> password;

    cout << "Confirm Password   : ";
    cin >> confirmPassword;

    if (password != confirmPassword) {
        cout << "Passwords do not match. Registration failed.\n";
        goto pwd;
    }

    Provider p1(username, password);
    p1.insertIntoDatabase();
}

#endif // PROVIDERREGISTER_H_INCLUDED
