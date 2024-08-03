#ifndef PROVIDERLOGIN_H_INCLUDED
#define PROVIDERLOGIN_H_INCLUDED

#include <bits/stdc++.h>
#include "searchProvider.h"
#include "providerActivePage.h"

using namespace std;

void providerLogin() {
    string filename = R"(C:\Users\aravi\Downloads\ascii-text-art (4).txt)";
    ifstream inputFile(filename);
    string line;
    while (std::getline(inputFile, line)) {
        cout << line << endl;
    }
    inputFile.close();
    cout << "\n\n";

    string username, password;

    cout << "Enter Username     : ";
    cin >> username;

    cout << "Enter Password     : ";
    cin >> password;
    cout << "\n";

    Provider p1(username, password);
    loadProviders();

    AVLProviderTree tree;

    for(auto provider: providers) {
        tree.insert(provider);
    }

    Provider* foundProvider = tree.find(username);


    if (foundProvider && foundProvider->getPassword() == password) {
        providerName = foundProvider->getUsername();
        cout << "Login Successful... \nNow You can start your work..!\n\n" << endl;
        curProvider = foundProvider;
        providerWorkMenu();


    } else {
        cout << "User name or password doesn't exist. Do re-login or create a new account.\n\n" << endl;
    }

}

#endif // PROVIDERLOGIN_H_INCLUDED
