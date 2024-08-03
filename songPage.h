#ifndef SONGPAGE_H_INCLUDED
#define SONGPAGE_H_INCLUDED

#include <bits/stdc++.h>

using namespace std;

class Song {
private:
    string name;
    string artist;
    float duration; // duration in seconds
    string language;
    string genre;
    string path;
    string album;

public:
    // Constructor
    Song(string name, string artist, int duration, string language, string genre, string path, string album)
        : name(name), artist(artist), duration(duration), language(language), genre(genre), path(path), album(album) {}

    // Getter functions
    string getName() const { return name; }
    string getArtist() const { return artist; }
    float getDuration() const { return duration; }
    string getLanguage() const { return language; }
    string getGenre() const { return genre; }
    string getPath() const { return path; }
    string getAlbum() const { return album; }


    void insertIntoDatabase() const {
        // Connect to MySQL Server
        MYSQL* conn;
        conn = mysql_init(0);
        conn = mysql_real_connect(conn, "localhost", "aravinth", "1234", "soundcloud", 0, NULL, 0);
        if (conn == NULL) {
            cout << "Failed to connect to database: " << mysql_error(conn) << endl;
            return;
        }

        // Prepare data for insertion
        stringstream ss;
        ss << "INSERT INTO songs (name, artist, duration, language, genre, path, album) VALUES ('"
           << name << "', '" << artist << "', " << duration << ", '" << language << "', '"
           << genre << "', '" << path << "', '" << album << "')";

        // Convert the query to a string
        string query = ss.str();
        const char* q = query.c_str();

        // Execute the INSERT query
        int qstate = mysql_query(conn, q);
        if (qstate == 0) {
            cout << "Song insertion successful..!\n" << endl;
        } else {
            cout << "Song insertion failed: " << mysql_error(conn) << endl;
        }

        // Clean up the connection
        mysql_close(conn);
    }
};

vector<Song> songs;

void loadSongs(std::vector<Song> &songs) {
    MYSQL* conn = mysql_init(0);

    conn = mysql_real_connect(conn, "localhost", "aravinth", "1234", "soundcloud", 0, NULL, 0);
    if (!conn) {
        std::cerr << "Error connecting to MySQL database: " << mysql_error(conn) << std::endl;
        return;
    }

    std::string selectQuery = "SELECT * FROM songs";
    const char* selectQ = selectQuery.c_str();
    int selectQState = mysql_query(conn, selectQ);

    if (selectQState != 0) {
        std::cerr << "Error executing SQL query: " << mysql_error(conn) << std::endl;
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
        std::string name = row[1] ? row[1] : "";
        std::string artist = row[2] ? row[2] : "";
        float duration = row[3] ? std::stof(row[3]) : 0.0f;
        std::string language = row[4] ? row[4] : "";
        std::string genre = row[5] ? row[5] : "";
        std::string path = row[7] ? row[7] : "";
        std::string album = row[6] ? row[6] : "";

        Song song(name, artist, duration, language, genre, path, album);
        songs.push_back(song);
    }

    mysql_free_result(result);
    mysql_close(conn);
}




#endif



