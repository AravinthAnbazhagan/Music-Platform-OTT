#ifndef PLAYLISTPAGE_H_INCLUDED
#define PLAYLISTPAGE_H_INCLUDED

#include "userLogin.h"
#include "jaiRec.h"

// Define the Playlist class
class Playlist {
private:
    string name;
    vector<Song> songs;

public:
    // Constructor

    Playlist(const string& name) : name(name) {}

    Playlist(const string& name, const vector<Song>& songs)
        : name(name), songs(songs) {}

    string getName() const { return name; }

    vector<Song> getSongs()const { return songs; }

    void showSongs() {
        cout << "Playlist name : " << name << endl;
        // Check if the vector is empty
        if (songs.empty()) {
            cout << "No songs available." << endl;
            return;
        }

        // Define the width for each column
        const int nameWidth = 20;
        const int artistWidth = 20;
        const int durationWidth = 10;
        const int languageWidth = 10;
        const int genreWidth = 15;
        const int pathWidth = 25;
        const int albumWidth = 20;

        // Print the table header
        cout << left << setw(nameWidth) << "Name"
             << left << setw(artistWidth) << "Artist"
             << left << setw(durationWidth) << "Duration"
             << left << setw(languageWidth) << "Language"
             << left << setw(genreWidth) << "Genre"
             << left << setw(pathWidth) << "Path"
             << left << setw(albumWidth) << "Album"
             << endl;

        cout << string(nameWidth + artistWidth + durationWidth + languageWidth + genreWidth + pathWidth + albumWidth, '-') << endl;

        // Print each song in the table
        for (const auto& song : songs) {
            cout << left << setw(nameWidth) << song.getName()
                 << left << setw(artistWidth) << song.getArtist()
                 << left << setw(durationWidth) << song.getDuration()
                 << left << setw(languageWidth) << song.getLanguage()
                 << left << setw(genreWidth) << song.getGenre()
                 << left << setw(pathWidth) << song.getPath()
                 << left << setw(albumWidth) << song.getAlbum()
                 << endl;
        }
        cout << "\n";
    }

    void addPlaylistToDatabase() {
        cout << userName << " " << name <<  endl;
        MYSQL* conn;
        conn = mysql_init(0);
        conn = mysql_real_connect(conn, "localhost", "aravinth", "1234", "soundcloud", 0, NULL, 0);
        if (!conn) {
            cout << "Connection error.\n";
            return;
        }

        // Step 1: Retrieve the userid from the users table
        std::string selectQuery = "SELECT id FROM users WHERE username = '" + userName + "'";
        if (mysql_query(conn, selectQuery.c_str())) {
            std::cerr << "Error executing SELECT query: " << mysql_error(conn) << std::endl;
            return;
        }

        MYSQL_RES* result = mysql_store_result(conn);

        MYSQL_ROW row = mysql_fetch_row(result);

        int userId = atoi(row[0]);
        mysql_free_result(result);

        // Step 2: Insert the new playlist into the user_playlists table
        std::string insertQuery = "INSERT INTO user_playlists (userid, playlistname) VALUES (" + std::to_string(userId) + ", '" + name + "')";
        if (mysql_query(conn, insertQuery.c_str())) {
            std::cerr << "Couldn't add the playlist: " << mysql_error(conn) << "\n\n";
            return;
        }

        std::cout << "Playlist added successfully.\n\n";
    }

    void addSongToPlaylist( string Pname, string songName) {

        cout << Pname << " " << songName << endl;
        //songName = "Yemanja";
        // Establish MySQL connection
        MYSQL* conn = mysql_init(0);
        conn = mysql_real_connect(conn, "localhost", "aravinth", "1234", "soundcloud", 0, NULL, 0);
        if (conn == NULL) {
            cerr << "Failed to connect to database: " << mysql_error(conn) << endl;
            return;
        }

        // Step 1: Retrieve the userid from the users table
        string selectUserQuery = "SELECT id FROM users WHERE username = '" + userName + "'";
        if (mysql_query(conn, selectUserQuery.c_str())) {
            cerr << "Error executing SELECT query for user id: " << mysql_error(conn) << endl;
            mysql_close(conn);
            return;
        }

        MYSQL_RES* userResult = mysql_store_result(conn);
        if (userResult == NULL) {
            cerr << "Failed to store user query result: " << mysql_error(conn) << endl;
            mysql_free_result(userResult);
            mysql_close(conn);
            return;
        }

        MYSQL_ROW userRow = mysql_fetch_row(userResult);
        if (userRow == NULL) {
            cerr << "User not found: " << userName << endl;
            mysql_free_result(userResult);
            mysql_close(conn);
            return;
        }

        int userId = atoi(userRow[0]);
        mysql_free_result(userResult);

        // Step 2: Retrieve the songid from the songs table
        string selectSongQuery = "SELECT id FROM songs WHERE name = '" + songName + "'";
        if (mysql_query(conn, selectSongQuery.c_str())) {
            cerr << "Error executing SELECT query for song id: " << mysql_error(conn) << endl;
            mysql_close(conn);
            return;
        }

        MYSQL_RES* songResult = mysql_store_result(conn);
        if (songResult == NULL) {
            cerr << "Failed to store song query result: " << mysql_error(conn) << endl;
            mysql_free_result(songResult);
            mysql_close(conn);
            return;
        }

        MYSQL_ROW songRow = mysql_fetch_row(songResult);
        if (songRow == NULL) {
            cerr << "Song not found: " << songName << endl;
            mysql_free_result(songResult);
            mysql_close(conn);
            return;
        }

        int songId = atoi(songRow[0]);
        mysql_free_result(songResult);

        // Step 3: Insert the userid, playlistname, and songid into the user_playlist_songs table
        string insertQuery = "INSERT INTO user_playlist_songs (userid, playlistname, songid) VALUES ("
                              + to_string(userId) + ", '" + Pname + "', " + to_string(songId) + ")";
        if (mysql_query(conn, insertQuery.c_str())) {
            cerr << "Error executing INSERT query: " << mysql_error(conn) << endl;
            mysql_close(conn);
            return;
        }

        cout << "Song added to playlist successfully." << endl;

        // Close MySQL connection
        mysql_close(conn);
    }

    void deleteSongFromPlaylist(string Pname, string songName) {
        // Establish MySQL connection
        MYSQL* conn = mysql_init(0);
        conn = mysql_real_connect(conn, "localhost", "aravinth", "1234", "soundcloud", 0, NULL, 0);
        if (conn == NULL) {
            cerr << "Failed to connect to database: " << mysql_error(conn) << endl;
            return;
        }

        // Step 1: Retrieve the userid from the users table
        string selectUserQuery = "SELECT id FROM users WHERE username = '" + userName + "'";
        if (mysql_query(conn, selectUserQuery.c_str())) {
            cerr << "Error executing SELECT query for user id: " << mysql_error(conn) << endl;
            mysql_close(conn);
            return;
        }

        MYSQL_RES* userResult = mysql_store_result(conn);
        if (userResult == NULL) {
            cerr << "Failed to store user query result: " << mysql_error(conn) << endl;
            mysql_free_result(userResult);
            mysql_close(conn);
            return;
        }

        MYSQL_ROW userRow = mysql_fetch_row(userResult);
        if (userRow == NULL) {
            cerr << "User not found: " << userName << endl;
            mysql_free_result(userResult);
            mysql_close(conn);
            return;
        }

        int userId = atoi(userRow[0]);
        mysql_free_result(userResult);

        // Step 2: Retrieve the songid from the songs table
        string selectSongQuery = "SELECT id FROM songs WHERE name = '" + songName + "'";
        if (mysql_query(conn, selectSongQuery.c_str())) {
            cerr << "Error executing SELECT query for song id: " << mysql_error(conn) << endl;
            mysql_close(conn);
            return;
        }

        MYSQL_RES* songResult = mysql_store_result(conn);
        if (songResult == NULL) {
            cerr << "Failed to store song query result: " << mysql_error(conn) << endl;
            mysql_free_result(songResult);
            mysql_close(conn);
            return;
        }

        MYSQL_ROW songRow = mysql_fetch_row(songResult);
        if (songRow == NULL) {
            cerr << "Song not found: " << songName << endl;
            mysql_free_result(songResult);
            mysql_close(conn);
            return;
        }

        int songId = atoi(songRow[0]);
        mysql_free_result(songResult);

        // Step 3: Delete the entry from the user_playlist_songs table
        string deleteQuery = "DELETE FROM user_playlist_songs WHERE userid = " + to_string(userId) +
                             " AND playlistname = '" + Pname + "' AND songid = " + to_string(songId);
        if (mysql_query(conn, deleteQuery.c_str())) {
            cerr << "Error executing DELETE query: " << mysql_error(conn) << endl;
            mysql_close(conn);
            return;
        }

        cout << "Song removed from playlist successfully." << endl;

        // Close MySQL connection
        mysql_close(conn);
    }
};


// Loading playlists of a particular user
vector<Playlist> userPlaylists;

// Function to load playlists from the database
void loadPlaylists() {
    MYSQL* con = mysql_init(nullptr);

    con = mysql_real_connect(con, "localhost", "aravinth", "1234", "soundcloud", 0, nullptr, 0);

    // Retrieve the userid from the users table
    string selectUserQuery = "SELECT id FROM users WHERE username = '" + userName + "'";
    if (mysql_query(con, selectUserQuery.c_str())) {
        cerr << "Error executing SELECT query for userid: " << mysql_error(con) << endl;
        mysql_close(con);
        return;
    }

    MYSQL_RES* userResult = mysql_store_result(con);
    if (!userResult) {
        cerr << "Error storing result for userid: " << mysql_error(con) << endl;
        mysql_close(con);
        return;
    }

    MYSQL_ROW userRow = mysql_fetch_row(userResult);
    if (!userRow) {
        cerr << "Error: User not found" << endl;
        mysql_free_result(userResult);
        mysql_close(con);
        return;
    }

    int userId = atoi(userRow[0]);
    mysql_free_result(userResult);

    // Retrieve playlists for the user
    string selectPlaylistsQuery = "SELECT playlistname FROM user_playlists WHERE userid = " + to_string(userId);
    if (mysql_query(con, selectPlaylistsQuery.c_str())) {
        cerr << "Error executing SELECT query for playlists: " << mysql_error(con) << endl;
        mysql_close(con);
        return;
    }

    MYSQL_RES* playlistResult = mysql_store_result(con);
    if (!playlistResult) {
        cerr << "Error storing result for playlists: " << mysql_error(con) << endl;
        mysql_close(con);
        return;
    }

    userPlaylists.clear(); // Clear the vector before refilling it

    MYSQL_ROW playlistRow;
    while ((playlistRow = mysql_fetch_row(playlistResult))) {
        string playlistName = playlistRow[0] ? playlistRow[0] : "";
        //Playlist playlist(playlistName);   // Playlist name

        // Retrieve songs for each playlist
        string selectSongsQuery = "SELECT s.name, s.artist, s.duration, s.language, s.genre, s.path, s.album "
              "FROM user_playlist_songs ups "
              "JOIN songs s ON ups.songid = s.id "
              "WHERE ups.userid = " + to_string(userId) + " AND ups.playlistname = '" + playlistName + "'";

        if (mysql_query(con, selectSongsQuery.c_str())) {
            cerr << "Error executing SELECT query for songs: " << mysql_error(con) << endl;
            mysql_free_result(playlistResult);
            mysql_close(con);
            return;
        }

        MYSQL_RES* songResult = mysql_store_result(con);
        if (!songResult) {
            cerr << "Error storing result for songs: " << mysql_error(con) << endl;
            mysql_free_result(playlistResult);
            mysql_close(con);
            return;
        }

        vector<Song> curSongs;
        MYSQL_ROW songRow;
        while ((songRow = mysql_fetch_row(songResult))) {
            string name = songRow[0] ? songRow[0] : "";
            string artist = songRow[1] ? songRow[1] : "";
            float duration = songRow[2] ? atof(songRow[2]) : 0.0;
            string language = songRow[3] ? songRow[3] : "";
            string genre = songRow[4] ? songRow[4] : "";
            string path = songRow[5] ? songRow[5] : "";
            string album = songRow[6] ? songRow[6] : "";

            // Create a Song object with the retrieved values
            Song song(name, artist, duration, language, genre, path, album);

            // Add the song to the playlist
            curSongs.push_back(song);
        }
        Playlist pl(playlistName, curSongs);

        userPlaylists.push_back(pl);

        mysql_free_result(songResult);
    }

    mysql_free_result(playlistResult);
    mysql_close(con);

   /* for(auto pl : userPlaylists) {
        cout << pl.getName() << endl;

    }*/
}








#include "searchplaylist.h"
#include "PLCreateShowRemove.h"
#include "addRemoveSongFromPlaylist.h"

void playlistMenu() {
    int choice;
    int sub_choice;
    string searchName, Pname, songName;
    Playlist* pl = nullptr;

    while (true) {
        cout << "Main Menu:\n";
        cout << "1. Create Playlist\n";
        cout << "2. Show Playlist\n";
        cout << "3. Remove Playlist\n";
        cout << "4. Add Song to Playlist\n";
        cout << "5. Remove song from playlist\n";
        cout << "6. Search Playlist\n";
        cout << "7. Exit\n";
        cout << "Enter option      : ";
        cin >> choice;
        cout << endl;

        switch (choice) {
            case 1:
                createPlaylist();
                break;
            case 2:
                showPlaylist();
                break;
            case 3:
                removePlaylist();
                break;
            case 4:
                cout << "Enter Playlist Name To Add Song    : ";
                cin.ignore();
                getline(cin,Pname);
                cout << "Enter The Song Name                : ";
                getline(cin,songName);
                pl = searchPlaylist(Pname);
                if (!pl) {
                    cout << "Playlist not found..\n\n";
                } else {
                    pl->addSongToPlaylist(Pname,songName);
                }
                //cout << "Has to be implemented..\n";
                break;
            case 5:
                cout << "Enter Playlist Name To Add Song    : ";
                cin.ignore();
                getline(cin,Pname);
                cout << "Enter The Song Name                : ";
                getline(cin,songName);
                pl = searchPlaylist(Pname);
                if (!pl) {
                    cout << "Playlist not found..\n\n";
                } else {
                    pl->deleteSongFromPlaylist(Pname,songName);
                }
                break;
            case 6:
                cout << "Enter playlist name to search   : ";
                cin.ignore();
                cin >> searchName;
                pl = searchPlaylist(searchName);
                if (!pl) {
                    cout << "Playlist not found..\n\n";
                } else {

                    while (true) {
                        loadPlaylists();
                        cout << "Enter what do you want to do...\n";
                        cout << "1. Show Playlist Songs\n";
                        cout << "2. Play Playlist\n";
                        cout << "3. Exit\n";
                        cout << "Enter option      : ";
                        cin >> sub_choice;
                        cout << endl;

                        switch (sub_choice) {
                            case 1:
                                pl->showSongs();
                                break;
                            case 2:
                                //cout << "Has to be implemented..\n\n";
                                //show(pl);
                                pl->showSongs();
                                break;
                            case 3:
                                break;
                            default:
                                cout << "Invalid choice. Try again...\n\n";
                        }
                        if (sub_choice == 3) break;
                    }
                }
                break;
            case 7:
                break;
            default:
                cout << "Invalid choice. Try again...\n\n";
        }
        if(choice == 7)     break;
    }
}

#endif // PLYLISTPAGE_H_INCLUDED



















/**************************************************



};

int main() {
    MYSQL* conn = mysql_init(nullptr);

    conn = mysql_real_connect(conn, "localhost", "aravinth", "1234", "soundcloud", 0, NULL, 0);
    if (!conn) {
        std::cerr << "Error connecting to MySQL database: " << mysql_error(conn) << std::endl;
        return 1;
    }

    std::string userName = "exampleUser"; // Replace with actual username
    std::string playlistName = "My Playlist"; // Replace with actual playlist name
    std::string songName = "exampleSong"; // Replace with actual song name

    Playlist playlist(playlistName);
    playlist.addSongToPlaylist(conn, userName, songName);

    mysql_close(conn);
    return 0;
}




*******************************************/
