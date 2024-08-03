#ifndef ADDADS_H_INCLUDED
#define ADDADS_H_INCLUDED

#include <bits/stdc++.h>
#include "adsPage.h"

using namespace std;

int updateProviderAd(const string& providerName, const string& adName) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    // Initialize connection
    conn = mysql_init(NULL);

    // Connect to the database
    conn = mysql_real_connect(conn, "localhost", "aravinth", "1234", "soundcloud", 0, NULL, 0);

    if (conn == nullptr) {
        cerr << "Error connecting to MySQL database: " << mysql_error(conn) << endl;
        return 1;
    }

    string query;

    // Retrieve provider ID
    query = "SELECT id FROM providers WHERE name = '" + providerName + "'";
    if (mysql_query(conn, query.c_str())) {
        cerr << "Error querying database: " << mysql_error(conn) << endl;
        return 1;
    }
    res = mysql_store_result(conn);
    row = mysql_fetch_row(res);
    int providerId = atoi(row[0]);
    mysql_free_result(res);

    // Retrieve ad ID
    query = "SELECT id FROM ads WHERE name = '" + adName + "'";
    if (mysql_query(conn, query.c_str())) {
        cerr << "Error querying database: " << mysql_error(conn) << endl;
        return 1;
    }
    res = mysql_store_result(conn);
    row = mysql_fetch_row(res);
    int adId = atoi(row[0]);
    mysql_free_result(res);

    // Insert into provider_ad table
    query = "INSERT INTO provider_ads (pid, adsid) VALUES (" + to_string(providerId) + ", " + to_string(adId) + ")";
    if (mysql_query(conn, query.c_str())) {
        cerr << "Error inserting into provider_ads table: " << mysql_error(conn) << endl;
        return 1;
    }

    // Close connection
    mysql_close(conn);

    return 0;
}

void addAd() {
    string name, path;
    float duration;
    int c;

    cout << "Enter ad name        : ";
    cin.ignore();
    getline(cin, name);

    cout << "Enter ad duration    : ";
    cin >> duration;
    cout << endl;

    path = name + ".mp3"; // automatically append .mp3 to the ad name

    Ad a1(name, duration, path);
    a1.insertIntoDatabase();

    updateProviderAd(providerName, name);
}




#endif // ADDADS_H_INCLUDED



/**********************

#ifndef ADDAD_H_INCLUDED
#define ADDAD_H_INCLUDED

#include <bits/stdc++.h>
#include <mysql/mysql.h>

using namespace std;

// Ad class definition
class Ad {
private:
    string name;
    float duration;
    string path;

public:
    // Constructor
    Ad(const string& name, float duration, const string& path)
        : name(name), duration(duration), path(path) {}

    // Getters
    string getName() const { return name; }
    float getDuration() const { return duration; }
    string getPath() const { return path; }

    void insertIntoDatabase() {
        MYSQL *con = mysql_init(nullptr);

        con = mysql_real_connect(con, "localhost", "aravinth", "1234", "soundcloud", 0, nullptr, 0);
        if (con == nullptr) {
            cerr << "Error connecting to MySQL database: " << mysql_error(con) << endl;
            return;
        }

        stringstream ss;
        ss << "INSERT INTO ad(name, duration, path) VALUES('"
           << name << "', " << duration << ", '" << path << "')";

        string query = ss.str();

        if (mysql_query(con, query.c_str())) {
            cerr << "Error executing SQL query: " << mysql_error(con) << endl;
        } else {
            cout << "Ad inserted successfully." << endl;
        }

        mysql_close(con);
    }
};

vector<Ad> ads;

void loadAds() {
    MYSQL* con = mysql_init(nullptr);

    con = mysql_real_connect(con, "localhost", "aravinth", "1234", "soundcloud", 0, NULL, 0);
    if (con == nullptr) {
        cerr << "Error connecting to MySQL database: " << mysql_error(con) << endl;
        return;
    }

    if (mysql_query(con, "SELECT name, duration, path FROM ad")) {
        cerr << "Error executing SQL query: " << mysql_error(con) << endl;
        mysql_close(con);
        return;
    }

    MYSQL_RES *result = mysql_store_result(con);
    if (!result) {
        cerr << "Error retrieving result set: " << mysql_error(con) << endl;
        mysql_close(con);
        return;
    }

    int num_fields = mysql_num_fields(result);
    MYSQL_ROW row;

    ads.clear(); // Clear the vector before refilling it

    while ((row = mysql_fetch_row(result))) {
        string name = row[0] ? row[0] : "";
        float duration = row[1] ? stof(row[1]) : 0.0;
        string path = row[2] ? row[2] : "";

        ads.emplace_back(name, duration, path);
    }

    mysql_free_result(result);
    mysql_close(con);
}


#endif // ADDAD_H_INCLUDED




****************************/
