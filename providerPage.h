#ifndef PROVIDERPAGE_H_INCLUDED
#define PROVIDERPAGE_H_INCLUDED

#include <bits/stdc++.h>
#include "songPage.h"
#include "podcastPage.h"
#include "adsPage.h"
//#include "searchSong.h"

using namespace std;

// Conversion from string to time - for license expiry date
tm stringToTm(const string& dateString) {
    tm timeStruct = {};
    istringstream ss(dateString);
    ss >> get_time(&timeStruct, "%Y-%m-%d %H:%M:%S");
    return timeStruct;
}

// Provider class implementation
class Provider {
private:
    string username;
    string password;
    bool active;
    tm licenceExpDate;

public:
    Provider(string uname, string pwd)
        : username(uname), password(pwd)  {}

    Provider(string uname, string pwd, bool active, tm led)
        : username(uname), password(pwd), active(active), licenceExpDate(led)  {}

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
            //cout << "Failed to insert data: " << mysql_error(conn) << endl;
            cout << "Account creation Failed. Do re-registration.\n\n" << endl;
        } else {
            cout << "Provider registered successfully!\n";
            cout << "Welcome to our application. You successfully created your account. \nNow you can start you can continue your journey by doing log-in...!\n\n";
        }



        mysql_close(conn);
    }

    bool checkLicenseStatus () {
        time_t now = time(0);
        tm now_tm;
        localtime_r(&now, &now_tm);

        if (difftime(mktime(&licenceExpDate), now) > 0) {
            return true; // License is active
        } else {
            return false; // License has expired
        }
    }

    void renewLicense() {
    int choice;
    cout << "Choose a renewal plan:\n";
    cout << "1. One month - $30\n";
    cout << "2. Two months - $50\n";
    cout << "3. Three months - $75\n";
    cin >> choice;

    int additionalMonths = 0;
    switch(choice) {
        case 1:
            additionalMonths = 1;
            break;
        case 2:
            additionalMonths = 2;
            break;
        case 3:
            additionalMonths = 3;
            break;
        default:
            cout << "Invalid choice!\n";
            return;
    }

    // Calculate the new expiry date
    licenceExpDate.tm_mon += additionalMonths;
    // Normalize the date structure
    mktime(&licenceExpDate);

    // Update the expiry date in the database
    MYSQL* conn;
    conn = mysql_init(0);
    if (conn == NULL) {
        cout << "mysql_init() failed\n";
        return;
    }

    conn = mysql_real_connect(conn, "localhost", "aravinth", "1234", "soundcloud", 0, NULL, 0);
    if (conn == NULL) {
        cout << "Failed to connect to database: " << mysql_error(conn) << endl;
        mysql_close(conn);
        return;
    }

    stringstream ss;
    ss << "UPDATE providers SET license_expiry_date = '"
       << (1900 + licenceExpDate.tm_year) << "-"
       << (1 + licenceExpDate.tm_mon) << "-"
       << licenceExpDate.tm_mday
       << "' WHERE name = '" << username << "'";

    cout << ss.str() << endl;


    string query = ss.str();
    const char* q = query.c_str();

    if (mysql_query(conn, q)) {
        cout << "Failed to update license expiry date: " << mysql_error(conn) << endl;
    } else {
        cout << "License renewed successfully!\n";
    }

    mysql_close(conn);
    }


};

// -------------------------------------------------------------------------------------------------------------------------------------------------------
vector<Provider> providers;   // Global variable to store all providers
string providerName;
Provider* curProvider;

// The below function is for loading all the providers from the database
void loadProviders() {
    MYSQL* conn = mysql_init(0);

    conn = mysql_real_connect(conn, "localhost", "aravinth", "1234", "soundcloud", 0, NULL, 0);
    if (!conn) {
        cerr << "Error connecting to MySQL database: " << mysql_error(conn) << endl;
        return;
    }

    string selectQuery = "SELECT * FROM `providers`";
    const char* selectQ = selectQuery.c_str();
    int selectQState = mysql_query(conn, selectQ);

    if (selectQState != 0) {
        cerr << "Error executing SQL query: " << mysql_error(conn) << endl;
        mysql_close(conn);
        return;
    }

    MYSQL_RES* result = mysql_store_result(conn);
    if (!result) {
        std::cerr << "Error retrieving result set: " << mysql_error(conn) << std::endl;
        mysql_close(conn);
        return;
    }

    MYSQL_ROW row;

    while ((row = mysql_fetch_row(result))) {
        string pname = row[1] ? row[1] : "";
        string pwd = row[2] ? row[2] : "";
        bool active = (stoi(row[3]) == 0) ? false : true;
        tm led = row[4] ? stringToTm(row[4]) : tm{};

        Provider p(pname, pwd, active, led);
        providers.push_back(p);
    }
    mysql_free_result(result);
    mysql_close(conn);
}
// --------------------------------------------------------------------------------------------------------------------------------------------------------


vector<Podcast> providerPodcasts;
vector<Song> providerSongs;
vector<Ad> providerAds;

int loadProviderPodcasts(const string& providerName) {
    MYSQL* conn = mysql_init(nullptr);

    conn = mysql_real_connect(conn, "localhost", "aravinth", "1234", "soundcloud", 0, NULL, 0);
    if (!conn) {
        cerr << "Error connecting to MySQL database: " << mysql_error(conn) << endl;
        return 0;
    }

    string query;

    // Retrieve provider ID
    query = "SELECT id FROM providers WHERE name = '" + providerName + "'";
    if (mysql_query(conn, query.c_str())) {
        cerr << "Error querying database: " << mysql_error(conn) << endl;
        return 1;
    }
    MYSQL_RES* res = mysql_store_result(conn);
    MYSQL_ROW row = mysql_fetch_row(res);
    int providerId = atoi(row[0]);
    mysql_free_result(res);

    string selectQuery = "select * from podcasts where id IN(select podcastid from provider_podcasts where pid = " + to_string(providerId) + ")";
    if (mysql_query(conn, selectQuery.c_str())) {
        cerr << "Error executing SQL query: " << mysql_error(conn) << endl;
        mysql_close(conn);
        return 0;
    }

    MYSQL_RES* result = mysql_store_result(conn);
    if (!result) {
        cerr << "Error retrieving result set: " << mysql_error(conn) << endl;
        mysql_close(conn);
        return 0;
    }

    while ((row = mysql_fetch_row(result))) {
        string name = row[1] ? row[1] : "";
        int duration = row[2] ? stoi(row[2]) : 0;
        string genre = row[3] ? row[3] : "";
        string language = row[4] ? row[4] : "";
        string series = row[5] ? row[5] : "";
        string path = row[6] ? row[6] : "";

        Podcast p(name, duration, genre, language, series, path);
        providerPodcasts.push_back(p);
    }


    /*for(auto p : providerPodcasts) {
        cout << "Name :  " << p.getName() << endl;

    }*/

    mysql_free_result(result);
    mysql_close(conn);
}

int loadProviderSongs(const string& providerName) {
    providerSongs.clear();  // Clear the vector before loading new songs
    MYSQL* conn = mysql_init(nullptr);

    conn = mysql_real_connect(conn, "localhost", "aravinth", "1234", "soundcloud", 0, NULL, 0);
    if (!conn) {
        cerr << "Error connecting to MySQL database: " << mysql_error(conn) << endl;
        return 0;
    }

    string query;

    // Retrieve provider ID
    query = "SELECT id FROM providers WHERE name = '" + providerName + "'";
    if (mysql_query(conn, query.c_str())) {
        cerr << "Error querying database: " << mysql_error(conn) << endl;
        mysql_close(conn);
        return 1;
    }
    MYSQL_RES* res = mysql_store_result(conn);
    if (!res) {
        cerr << "Error retrieving result set: " << mysql_error(conn) << endl;
        mysql_close(conn);
        return 1;
    }
    MYSQL_ROW row = mysql_fetch_row(res);
    if (!row) {
        cerr << "Provider not found" << endl;
        mysql_free_result(res);
        mysql_close(conn);
        return 1;
    }
    int providerId = atoi(row[0]);
    mysql_free_result(res);

    // Fetch songs associated with the provider
    string selectQuery = "SELECT * FROM songs WHERE id IN (SELECT songid FROM provider_songs WHERE pid = " + to_string(providerId) + ")";
    if (mysql_query(conn, selectQuery.c_str())) {
        cerr << "Error executing SQL query: " << mysql_error(conn) << endl;
        mysql_close(conn);
        return 0;
    }

    MYSQL_RES* result = mysql_store_result(conn);
    if (!result) {
        cerr << "Error retrieving result set: " << mysql_error(conn) << endl;
        mysql_close(conn);
        return 0;
    }

    while ((row = mysql_fetch_row(result))) {
        string name = row[1] ? row[1] : "";
        string artist = row[2] ? row[2] : "";
        float duration = row[3] ? stof(row[3]) : 0.0;
        string language = row[4] ? row[4] : "";
        string genre = row[5] ? row[5] : "";
        string path = row[6] ? row[6] : "";
        string album = row[7] ? row[7] : "";

        Song s(name, artist, duration, language, genre, path, album);
        providerSongs.push_back(s);
    }

    // Output the fetched songs
    /*cout << "Songs provided by " << providerName << ":" << endl;
    for (const auto& s : providerSongs) {
        cout << "Name: " << s.getName() << ", Artist: " << s.getArtist() << ", Duration: " << s.getDuration()
             << ", Language: " << s.getLanguage() << ", Genre: " << s.getGenre() << ", Album: " << s.getAlbum() << endl;
    }*/

    mysql_free_result(result);
    mysql_close(conn);

    return 1;  // Return 1 for success
}

int loadProviderAds(const string& providerName) {
    providerAds.clear();  // Clear the vector before loading new ads
    MYSQL* conn = mysql_init(nullptr);

    conn = mysql_real_connect(conn, "localhost", "aravinth", "1234", "soundcloud", 0, NULL, 0);
    if (!conn) {
        cerr << "Error connecting to MySQL database: " << mysql_error(conn) << endl;
        return 0;
    }

    string query;

    // Retrieve provider ID
    query = "SELECT id FROM providers WHERE name = '" + providerName + "'";
    if (mysql_query(conn, query.c_str())) {
        cerr << "Error querying database: " << mysql_error(conn) << endl;
        mysql_close(conn);
        return 1;
    }
    MYSQL_RES* res = mysql_store_result(conn);
    if (!res) {
        cerr << "Error retrieving result set: " << mysql_error(conn) << endl;
        mysql_close(conn);
        return 1;
    }
    MYSQL_ROW row = mysql_fetch_row(res);
    if (!row) {
        cerr << "Provider not found" << endl;
        mysql_free_result(res);
        mysql_close(conn);
        return 1;
    }
    int providerId = atoi(row[0]);
    mysql_free_result(res);

    // Fetch ads associated with the provider
    string selectQuery = "SELECT * FROM ads WHERE id IN (SELECT adsid FROM provider_ads WHERE pid = " + to_string(providerId) + ")";
    if (mysql_query(conn, selectQuery.c_str())) {
        cerr << "Error executing SQL query: " << mysql_error(conn) << endl;
        mysql_close(conn);
        return 0;
    }

    MYSQL_RES* result = mysql_store_result(conn);
    if (!result) {
        cerr << "Error retrieving result set: " << mysql_error(conn) << endl;
        mysql_close(conn);
        return 0;
    }

    while ((row = mysql_fetch_row(result))) {
        string name = row[1] ? row[1] : "";
        float duration = row[2] ? stof(row[2]) : 0.0f;
        string path = row[3] ? row[3] : "";

        Ad ad(name, duration, path);
        providerAds.push_back(ad);
    }

    // Output the fetched ads
    /*cout << "Ads provided by " << providerName << ":" << endl;
    for (const auto& ad : providerAds) {
        cout << "Name: " << ad.getName() << ", Duration: " << ad.getDuration() << ", Path: " << ad.getPath() << endl;
    }*/

    mysql_free_result(result);
    mysql_close(conn);

    return 1;  // Return 1 for success
}


// This is to search the provider in the "providers" -> using AVL tree for login

#include "providerRegister.h"
#include "providerLogin.h"




void displayProviderMenu() {
    int choice;
    while(true){
        cout << "Welcome provider...\n";
        cout << setw(2) << "1. " << "Login\n";
        cout << setw(2) << "2. " << "Register\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cout << "\n\n";

        switch (choice) {
            case 1:
                providerLogin();
                break;
            case 2:
                providerRegister();
                break;
            default:
                cout << "Invalid choice.\n";
                break;
        }
    }
}

#endif




