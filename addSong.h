#ifndef ADDSONG_H_INCLUDED
#define ADDSONG_H_INCLUDED

#include <bits/stdc++.h>
//#include "providerLogin.h"
#include "songPage.h"

using namespace std;

int updateProviderSong(const string& providerName, const string& songName){
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
    query = "SELECT id FROM songs WHERE name = '" + songName + "'";
    if (mysql_query(conn, query.c_str())) {
        cerr << "Error querying database: " << mysql_error(conn) << endl;
        return 1;
    }
    res = mysql_store_result(conn);
    row = mysql_fetch_row(res);
    int songId = atoi(row[0]);
    mysql_free_result(res);

    // Insert into providerSong table
    query = "INSERT INTO provider_songs (pid, songid) VALUES (" + to_string(providerId) + ", " + to_string(songId) + ")";
    if (mysql_query(conn, query.c_str())) {
        cerr << "Error inserting into provider_songs table: " << mysql_error(conn) << endl;
        return 1;
    }

    // Close connection
    mysql_close(conn);
}

void addSong() {
    if(!curProvider->checkLicenseStatus()){
        cout << "Your license expired... You cannot add song\n\n";
        return;
    }

    string name;
    string artist;
    float duration; // using float as per the given requirement
    string lang;
    string genre;
    string album;
    int c;

    cout << "Enter song name          : ";
    cin.ignore();
    getline(cin, name);

    cout << "Enter duration           : ";
    cin >> duration;
    cout << "\n";

    cout << "Choose song's language in the options given below...\n";
    vector<string> languages = {"English", "Tamil", "Hindi", "Telugu", "Kannada", "Malayalam", "Bengali", "Spanish", "French", "German", "Chinese"};
    for (size_t i = 0; i < languages.size(); ++i) {
        cout << setw(2) << i + 1 << ". " << languages[i] << "\n";
    }
    cout << "Choose Language          : ";
    cin >> c;
    lang = languages[c-1];
    cout << "\n";

    cout << "Enter Artist of the song.\nIf the artist not present in the option type -1... ";
    vector<string> artists;
    if (lang == "English") {
        artists.insert(artists.end(), {"Adele", "Ed Sheeran", "Taylor Swift", "Beyoncé", "Drake", "Rihanna", "Justin Bieber", "Ariana Grande", "Coldplay", "Bruno Mars"});
    } else if (lang == "Tamil") {
        artists.insert(artists.end(), {"A.R. Rahman", "Ilaiyaraaja", "Yuvan Shankar Raja", "Harris Jayaraj", "Anirudh Ravichander", "S. P. Balasubrahmanyam", "Sid Sriram", "Shreya Ghoshal", "D. Imman", "Vijay Antony"});
    } else if (lang == "Hindi") {
        artists.insert(artists.end(), {"Arijit Singh", "Neha Kakkar", "Atif Aslam", "Shreya Ghoshal", "Rahat Fateh Ali Khan", "Armaan Malik", "Badshah", "Neha Kakkar", "Sonu Nigam", "Sunidhi Chauhan"});
    } else if (lang == "Telugu") {
        artists.insert(artists.end(), {"A. R. Rahman", "Devi Sri Prasad (DSP)", "Sid Sriram", "Shreya Ghoshal", "K.S. Chithra", "Vijay Yesudas", "Geetha Madhuri", "S. P. Balasubrahmanyam", "Shreemani", "Ramajogayya Sastry"});
    } else if (lang == "Kannada") {
        artists.insert(artists.end(), {"Rajesh Krishnan", "Sonu Nigam", "Shreya Ghoshal", "Vijay Prakash", "Arjun Janya", "Sanjith Hegde", "Hamsalekha", "Chinmayi", "Puneeth Rajkumar", "Raghu Dixit"});
    } else if (lang == "Malayalam") {
        artists.insert(artists.end(), {"K.J. Yesudas", "Shreya Ghoshal", "Vineeth Sreenivasan", "K.S. Chithra", "Vijay Yesudas", "Gopi Sundar", "M. G. Sreekumar", "Shweta Mohan", "Haricharan", "Rimi Tomy"});
    } else if (lang == "Bengali") {
        artists.insert(artists.end(), {"Anupam Roy", "Arijit Singh", "Shreya Ghoshal", "Rupankar Bagchi", "Lata Mangeshkar", "Kishore Kumar", "Nachiketa Chakraborty", "Shaan", "Babul Supriyo", "Monali Thakur"});
    } else if (lang == "Spanish") {
        artists.insert(artists.end(), {"Enrique Iglesias", "Shakira", "Ricky Martin", "Maluma", "Daddy Yankee", "Luis Fonsi", "Juanes", "Marc Anthony", "Alejandro Sanz", "Bad Bunny"});
    } else if (lang == "French") {
        artists.insert(artists.end(), {"Edith Piaf", "Jacques Brel", "Charles Aznavour", "Serge Gainsbourg", "Johnny Hallyday", "Édith Piaf", "Dalida", "Zaz", "Stromae", "Vanessa Paradis"});
    } else if (lang == "German") {
        artists.insert(artists.end(), {"Rammstein", "Herbert Grönemeyer", "Helene Fischer", "Die Ärzte", "Nena", "Peter Maffay", "Xavier Naidoo", "Sarah Connor", "Kraftwerk", "Marianne Rosenberg"});
    } else if (lang == "Chinese") {
        artists.insert(artists.end(), {"Jay Chou", "Teresa Teng", "Faye Wong", "Jacky Cheung", "A-Mei (Zhang Huimei)", "Eason Chan", "Stefanie Sun", "Leehom Wang", "Alan Tam", "Twins (Gillian Chung & Charlene Choi)"});
    }

    for (size_t i = 0; i < artists.size(); i++) {
        cout << i + 1 << ". " << artists[i] << endl;
    }
    //artist = artists[i];

    cout << "Enter option : ";
    cin >> c;

    if(c == -1){
        cout << "Enter artist name     : ";
        cin.ignore();
        getline(cin, artist);

        MYSQL* conn;
        conn = mysql_init(nullptr);

        conn = mysql_real_connect(conn, "localhost", "aravinth", "1234", "soundcloud", 0, NULL, 0);

        stringstream ss;

        ss << "INSERT INTO `artists` (name) VALUES ('" << artist << "')";

        // Convert the query to a string
        string query = ss.str();
        const char* q = query.c_str();

        // Execute the INSERT query
        int qstate = mysql_query(conn, q);
        mysql_close(conn);

    } else {
        artist = artists[c-1];
    }
    cout << "\n";

    cout << "Choose song's genre in the options given below...\n";
    vector<string> genres = {"Love", "Beast", "Mass Hits", "Alone", "Melting", "Vibe", "Party", "Sad", "Classical", "Pop"};
    for (size_t i = 0; i < genres.size(); ++i) {
        cout << setw(2) << i + 1 << ". " << genres[i] << "\n";
    }
    cout << "Select Genre        : ";
    cin >> c;
    genre = genres[c-1];

    cout << "Enter album name    : ";
    cin.ignore();
    getline(cin, album);

    string path = name+".mp3";
    cout << "\n";

    Song s(name, artist, duration, lang, genre, path, album);

    s.insertIntoDatabase();
    updateProviderSong(providerName, name);
}

#endif // ADDSONG_H_INCLUDED
