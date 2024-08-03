#ifndef ADSPAGE_H_INCLUDED
#define ADSPAGE_H_INCLUDED

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
        ss << "INSERT INTO ads(name, duration, path) VALUES('"
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

    con = mysql_real_connect(con, "localhost", "your_username", "your_password", "your_database_name", 0, NULL, 0);
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


#endif // ADSPAGE_H_INCLUDED



/******

#include <bits/stdc++.h>
#include <mysql/mysql.h>

using namespace std;

// Ad class definition



int main() {
    // Example usage
    Ad newAd("Sample Ad", 30.0, "path/to/ad.mp3");
    newAd.insertIntoDatabase();

    loadAds();
    for (const Ad& ad : ads) {
        cout << "Ad Name: " << ad.getName() << ", Duration: " << ad.getDuration() << ", Path: " << ad.getPath() << endl;
    }

    return 0;
}

*****************/

