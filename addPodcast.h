#ifndef ADDPODCAST_H_INCLUDED
#define ADDPODCAST_H_INCLUDED

#include <bits/stdc++.h>
#include "podcastPage.h"

using namespace std;

int updateProviderPodcast(const string& providerName, const string& podcastName){
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    // Initialize connection
    conn = mysql_init(NULL);

    // Connect to the database
    conn = mysql_real_connect(conn, "localhost", "aravinth", "1234", "soundcloud", 0, NULL, 0);

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

    // Retrieve song ID
    query = "SELECT id FROM podcasts WHERE name = '" + podcastName + "'";
    if (mysql_query(conn, query.c_str())) {
        cerr << "Error querying database: " << mysql_error(conn) << endl;
        return 1;
    }
    res = mysql_store_result(conn);
    row = mysql_fetch_row(res);
    int pId = atoi(row[0]);
    mysql_free_result(res);

    // Insert into providerSong table
    query = "INSERT INTO provider_podcasts (pid, podcastid) VALUES (" + to_string(providerId) + ", " + to_string(pId) + ")";
    if (mysql_query(conn, query.c_str())) {
        cerr << "Error inserting into provider_podcasts table: " << mysql_error(conn) << endl;
        return 1;
    }

    // Close connection
    mysql_close(conn);
}

void addPodcast() {
    string name, genre, language, series;
    float duration;
    int c;

    cout << "Enter podcast name        : ";
    cin.ignore();
    getline(cin, name);

    cout << "Enter podcast duration    : ";
    cin >> duration;
    cout << endl;

    cout << "Select genre of the podcast from the below options...\n";
    vector<string> genres = {"Comedy", "Drama", "Education", "History", "Motivation", "News", "Romantic", "Sports", "Travel"};

    for(int i=0; i<genres.size(); i++){
        cout << setw(2) << i + 1 << ". " << genres[i] << endl;
    }
    cout << "Select an option          : ";
    cin >> c;
    genre = genres[c-1];
    cout << endl;

    cout << "Choose song's language in the options given below...\n";
    vector<string> languages = {"English", "Tamil", "Hindi", "Telugu", "Kannada", "Malayalam", "Bengali", "Spanish", "French", "German"};
    for (size_t i = 0; i < languages.size(); ++i) {
        cout << setw(2) << i + 1 << ". " << languages[i] << "\n";
    }
    cout << "Choose Language          : ";
    cin >> c;
    language = languages[c-1];
    cout << endl;

    cout << "Enter podcast series: ";
    cin.ignore();
    getline(cin, series);
    cout << endl;

    string path = name + ".mp3"; // automatically append .mp3 to the song name

    Podcast p1(name, duration, genre, language, series, path);
    p1.insertIntoDatabase();
    updateProviderPodcast(providerName, name);
}

#endif // ADDPODCAST_H_INCLUDED
