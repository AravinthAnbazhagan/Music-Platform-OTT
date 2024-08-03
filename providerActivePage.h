#ifndef PROVIDERACTIVEPAGE_H_INCLUDED
#define PROVIDERACTIVEPAGE_H_INCLUDED

#include <bits/stdc++.h>
#include "addSong.h"
#include "addPodcast.h"
#include "addAds.h"
#include "removeOperation.h"
#include "showOperationProvider.h"
#include "searchOptionProvider.h"
#include "searchProvider.h"

using namespace std;

void providerSongMenu(){
    int choice;
    while (true) {
        loadProviderSongs(providerName);
        cout << "What do you want to do...\n";
        cout << "1. Show\n";
        cout << "2. Add\n";
        cout << "3. Remove\n";
        cout << "4. Search\n";
        cout << "5. Exit\n";
        cout << "Select an option: ";
        cin >> choice;
        cout << "\n\n";

        switch (choice) {
            case 1:
                showSongs();
                break;
            case 2:
                addSong();
                break;
            case 3:
                removeSongOrAlbum();
                break;
            case 4:
                searchSongs();
                break;
            case 5:
                break;
            default:
                cout << "Invalid option, please try again.\n";
        }
        if(choice == 5)  break;
    }
}

void LicenseMenu(){
    loadProviderPodcasts(providerName);
    AVLProviderTree tree;

    for(auto provider: providers) {
        tree.insert(provider);
    }

    Provider* foundProvider = tree.find(providerName);
    int choice;
    while (true) {

        cout << "What do you want to do...\n";
        cout << "1. Check Status\n";
        cout << "2. Renewal\n";
        cout << "3. Exit\n";
        cout << "Select an option: ";
        cin >> choice;
        cout << "\n\n";

        switch (choice) {
            case 1:
                if(foundProvider->checkLicenseStatus()){
                    cout << "Your have access to add song..!\n\n";
                }
                else{
                    cout << "Your license expired..!\n\n";
                }
                break;
            case 2:
                foundProvider->renewLicense();
                break;
            case 3:
                break;
            default:
                cout << "Invalid option, please try again.\n";
        }
        if(choice == 3)  break;
    }

}

void providerPodcastMenu(){
    int choice;
    while (true) {
        loadProviderPodcasts(providerName);
        cout << "What do you want to do...\n";
        cout << "1. Show\n";
        cout << "2. Add\n";
        cout << "3. Remove\n";
        cout << "4. Search\n";
        cout << "5. Exit\n";
        cout << "Select an option: ";
        cin >> choice;
        cout << "\n\n";

        switch (choice) {
            case 1:
                showPodcasts();
                break;
            case 2:
                addPodcast();
                break;
            case 3:
                removePodcast();
                break;
            case 4:
                searchPodcasts();
                break;
            case 5:
                break;
            default:
                cout << "Invalid option, please try again.\n";
        }
        if(choice == 5)  break;
    }
}


void providerAdsMenu(){
    int choice;
    while (true) {
        loadProviderAds(providerName);
        cout << "What do you want to do...\n";
        cout << "1. Show\n";
        cout << "2. Add\n";
        cout << "3. Remove\n";
        cout << "4. Search\n";
        cout << "5. Exit\n";
        cout << "Select an option: ";
        cin >> choice;
        cout << "\n\n";

        switch (choice) {
            case 1:
                showAds();
                break;
            case 2:
                addAd();
                break;
            case 3:
                removeAd();
                break;
            case 4:
                searchAds();
                break;
            case 5:
                break;
            default:
                cout << "Invalid option, please try again.\n";
        }
        if(choice == 5)  break;
    }
}


void providerWorkMenu() {
    int choice;
    while (true) {
        cout << "What do you want to manage...\n";
        cout << "1. Song\n";
        cout << "2. Podcast\n";
        cout << "3. advertisement\n";
        cout << "4. Licence Information\n";
        cout << "5. Exit\n";
        cout << "Select an option: ";
        cin >> choice;
        cout << "\n\n";

        switch (choice) {
            case 1:
                providerSongMenu();
                break;
            case 2:
                providerPodcastMenu();
                break;
            case 3:
                providerAdsMenu();
                break;
            case 4:
                LicenseMenu();
            case 5:
                break;
            default:
                cout << "Invalid option, please try again.\n";
        }
        if(choice == 5)     break;
        cout << "\n\n";
    }
}


#endif // PROVIDERACTIVEPAGE_H_INCLUDED



/***************************

#include <iostream>
#include <sstream>
#include <mysql/mysql.h>

using namespace std;

class Provider {
private:
    string username;
    string password;
    bool active;
    tm licenceExpDate;

public:
    Provider(string uname, string pwd)
        : username(uname), password(pwd), active(false) {
            // Initialize licenceExpDate with a default value
            time_t t = time(0);
            localtime_r(&t, &licenceExpDate);
        }

    Provider(string uname, string pwd, bool active, tm led)
        : username(uname), password(pwd), active(active), licenceExpDate(led) {}

    string getUsername() const { return username; }
    string getPassword() const { return password; }
    bool getActiveState() const { return active; }
    tm getLicenceExpDate() const { return licenceExpDate; }

    void insertIntoDatabase() const {
        MYSQL* conn;

        conn = mysql_init(0);
        conn = mysql_real_connect(conn, "localhost", "aravinth", "1234", "soundcloud", 0, NULL, 0);
        if (conn == NULL) {
            cout << "Failed to connect to database: " << mysql_error(conn) << endl;
            return;
        }

        // Prepare data for insertion
        stringstream ss;
        ss << "INSERT INTO providers (name, password) VALUES ('" << username << "', '" << password << "')";

        // Convert the query to a string
        string query = ss.str();
        const char* q = query.c_str();

        if (mysql_query(conn, q)) {
            cout << "Account creation Failed. Do re-registration.\n\n" << endl;
        } else {
            cout << "Provider registered successfully!\n";
            cout << "Welcome to our application. You successfully created your account. \nNow you can start you can continue your journey by doing log-in...!\n\n";
        }

        mysql_close(conn);
    }



};


***************************/
