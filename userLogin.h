#ifndef USERLOGIN_H_INCLUDED
#define USERLOGIN_H_INCLUDED

#include <bits/stdc++.h>
#include "searchUser.h"
#include "songPageForUser.h"
#include "recommandation.h";
#include "jaiRec.h"


using namespace std;


vector<Song> userHistory;
vector<Song> userGenres;
vector<Song> userArtists;
vector<Song> userLanguages;
vector<Song> relatedSongs;

// LOG-IN function for user - if success -> song Page for user,  else -> login or registration
void userLogin() {
    string filename = R"(C:\Users\aravi\Downloads\ascii-text-art (2).txt)";
    ifstream inputFile(filename);
    string line;
    while (getline(inputFile, line)) {
        cout << line << endl;
    }
    inputFile.close();
    cout << "\n\n";

    loadUsers();
    AVLTree<User> myAVL;

    for (int i=0; i<users.size(); i++){
        myAVL.insert(users[i]);
    }
    string username, password;



    cout << "Enter Username     : ";
    cin >> username;

    cout << "Enter Password     : ";
    cin >> password;
    cout << "\n";

    User* user = myAVL.searchByUsername(username);
    if (user && user->getPassword() == password) {
        cout << "Login Successful... \nNow You can listen to your favorite songs..!\n\n" << endl;
        userName=user->getUsername();
        loadUserHistory(userHistory);
        loadUserGenres(userGenres);
        loadUserArtists(userArtists);
        loadUserLanguages(userLanguages);
        for(auto s : userHistory) {
            relatedSongs.push_back(s);
        }
        for(auto s : userGenres) {
            relatedSongs.push_back(s);
        }
        for(auto s : userArtists) {
            relatedSongs.push_back(s);
        }
        for(auto s : userLanguages) {
            relatedSongs.push_back(s);
        }

        loadPlaylists();
        reccommand();
        userWorkMenu();
    } else {
        cout << "User name or password doesn't exist. Do re-login or create a new account.\n\n" << endl;
    }
}

#endif // USERLOGIN_H_INCLUDED
