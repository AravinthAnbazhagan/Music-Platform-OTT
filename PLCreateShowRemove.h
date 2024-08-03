#ifndef PLCREATESHOWREMOVE_H_INCLUDED
#define PLCREATESHOWREMOVE_H_INCLUDED



void createPlaylist() {
    string plName;
    cout << "Enter Playlist name: ";
    cin.ignore();
    getline(cin, plName);

    cout << "Hii";
    Playlist pl(plName);
    pl.addPlaylistToDatabase();
}

void showPlaylist() {
    loadPlaylists();
    cout << "Your Playlists are...\n";
    for(int i=0; i<userPlaylists.size(); i++) {
        cout << i+1 << ". "<< userPlaylists[i].getName() << endl;
    }
    cout << endl;

    int choice;
    while(true){
        loadPlaylists();
        cout << "Enter what do you want to do...\n";
        cout << "1. Show Playlist Songs\n";
        cout << "2. Play Playlist\n";
        cout << "3. Exit\n";
        cout << "Enter option      : ";
        cin >> choice;
        cout << endl;

        switch(choice) {
        case 1:
            int p;
            cout << "Enter Playlist number : ";
            cin >> p;
            userPlaylists[p-1].showSongs();
            break;
        case 2:
            cout << "Has to be implemented..\n\n";
            break;
        case 3:
            break;
        default:
            cout << "Invalid choice. Try again...\n\n";
        }
        if(choice == 3)     break;
    }
}

    // Function to remove a playlist based on user input
void removePlaylist() {
    string name;

    cout << "Enter the name of the playlist to remove   : ";
    cin.ignore();
    getline(cin, name);

    // Connect to the database
    MYSQL* conn;
    conn = mysql_init(0);
    conn = mysql_real_connect(conn, "localhost", "aravinth", "1234", "soundcloud", 0, NULL, 0);
    if (!conn)  return;

    // Remove the playlist from the vector
    auto it = remove_if(userPlaylists.begin(), userPlaylists.end(), [&](const Playlist& p) {
        return p.getName() == name;
    });

    if (searchPlaylist(name)){
        cout << "Playlist not found." << endl;
        return;
    }

    std::string selectQuery = "SELECT id FROM users WHERE username = '" + userName + "'";
    if (mysql_query(conn, selectQuery.c_str())) {
        std::cerr << "Error executing SELECT query: " << mysql_error(conn) << std::endl;
        return;
    }

    MYSQL_RES* result = mysql_store_result(conn);

    MYSQL_ROW row = mysql_fetch_row(result);

    int userId = atoi(row[0]);
    mysql_free_result(result);

    // Remove the playlist from the database
    string deleteQuery = "DELETE FROM user_playlists WHERE playlistname = '" + name + "' AND userid = " + to_string(userId);

    if (mysql_query(conn, deleteQuery.c_str())) {
        std::cerr << "Failed to delete playlist : " << mysql_error(conn) << std::endl;
        return;
    }

    // Close the database connection
    mysql_close(conn);
}



#endif // PLCREATESHOWREMOVE_H_INCLUDED




/*******************************



// Operator overloading for merging playlists
Playlist operator+(const Playlist& other) const {
    Playlist mergedPlaylist(this->name + " & " + other.name);
    mergedPlaylist.songs = this->songs;
    mergedPlaylist.songs.insert(mergedPlaylist.songs.end(), other.songs.begin(), other.songs.end());
    return mergedPlaylist;
}

// Function to find a playlist by name in a vector of playlists
Playlist* findPlaylistByName(vector<Playlist>& playlists, const string& name) {
    for (Playlist& playlist : playlists) {
        if (playlist.getName() == name) {
            return &playlist;
        }
    }
    return nullptr;
}


// Function to execute a query and handle errors
bool executeQuery(MYSQL* conn, const string& query) {
    if (mysql_query(conn, query.c_str())) {
        cerr << "Query failed: " << mysql_error(conn) << endl;
        return false;
    }
    return true;
}

// Function to merge two playlists based on user input
void mergePlaylists(vector<Playlist>& playlists) {
    string name1, name2, newName;

    cout << "Enter the name of the first playlist to merge: ";
    getline(cin, name1);
    cout << "Enter the name of the second playlist to merge: ";
    getline(cin, name2);

    Playlist* playlist1 = findPlaylistByName(playlists, name1);
    Playlist* playlist2 = findPlaylistByName(playlists, name2);

    if (!playlist1 || !playlist2) {
        cout << "One or both playlists not found." << endl;
        return;
    }

    cout << "Enter the name for the new merged playlist: ";
    getline(cin, newName);

    Playlist mergedPlaylist = *playlist1 + *playlist2;
    mergedPlaylist.setName(newName);

    // Connect to the database
    MYSQL* conn = connectDatabase();
    if (!conn) return;

    // Remove the old playlists from the database
    string deleteQuery1 = "DELETE FROM playlists WHERE playlistname = '" + name1 + "'";
    string deleteQuery2 = "DELETE FROM playlists WHERE playlistname = '" + name2 + "'";

    if (!executeQuery(conn, deleteQuery1) || !executeQuery(conn, deleteQuery2)) {
        mysql_close(conn);
        return;
    }

    // Insert the new merged playlist into the database
    string insertQuery = "INSERT INTO playlists (playlistname) VALUES ('" + newName + "')";
    if (!executeQuery(conn, insertQuery)) {
        mysql_close(conn);
        return;
    }

    // Close the database connection
    mysql_close(conn);

    // Remove the old playlists from the vector
    playlists.erase(remove_if(playlists.begin(), playlists.end(), [&](const Playlist& p) {
        return p.getName() == name1 || p.getName() == name2;
    }), playlists.end());

    // Add the new merged playlist to the vector
    playlists.push_back(mergedPlaylist);

    cout << "Merged playlist created: " << mergedPlaylist.getName() << endl;
}









// Function to remove a playlist based on user input
void removePlaylist(vector<Playlist>& playlists) {
    string name;

    cout << "Enter the name of the playlist to remove: ";
    getline(cin, name);

    // Connect to the database
    MYSQL* conn = connectDatabase();
    if (!conn) return;

    // Remove the playlist from the vector
    auto it = remove_if(playlists.begin(), playlists.end(), [&](const Playlist& p) {
        return p.getName() == name;
    });

    if (it == playlists.end()){
        cout << "Playlist not found." << endl;
        return;
    }

    std::string selectQuery = "SELECT id FROM users WHERE username = '" + userName + "'";
    if (mysql_query(conn, selectQuery.c_str())) {
        std::cerr << "Error executing SELECT query: " << mysql_error(conn) << std::endl;
        return;
    }

    MYSQL_RES* result = mysql_store_result(conn);

    MYSQL_ROW row = mysql_fetch_row(result);

    int userId = atoi(row[0]);
    mysql_free_result(result);

    // Remove the playlist from the database
    string deleteQuery = "DELETE FROM playlists WHERE playlistname = '" + name + "' AND userid = " +to_string(userId) "'";
    if (mysql_query(conn, deleteQuery.c_str())) {
        std::cerr << "Failed to delete playlist : " << mysql_error(conn) << std::endl;
        return;
    }

    // Close the database connection
    mysql_close(conn);
}

int main() {
    // Vector of playlists
    vector<Playlist> playlists = {
        Playlist("Rock Classics"),
        Playlist("Pop Hits"),
        Playlist("Jazz Essentials"),
        Playlist("Classical Favorites"),
        Playlist("Electronic Beats")
    };

    int choice;
    cout << "Enter 1 to merge playlists or 2 to remove a playlist: ";
    cin >> choice;
    cin.ignore(); // to ignore the newline character left in the buffer by cin

    if (choice == 1) {
        mergePlaylists(playlists);
    } else if (choice == 2) {
        removePlaylist(playlists);
    } else {
        cout << "Invalid choice." << endl;
    }

    // Display all playlists to verify
    cout << "Current playlists:" << endl;
    for (const Playlist& playlist : playlists) {
        cout << playlist.getName() << endl;
    }

    return 0;
}




******************************/
