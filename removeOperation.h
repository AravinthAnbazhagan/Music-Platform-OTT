#ifndef REMOVEOPERATION_H_INCLUDED
#define REMOVEOPERATION_H_INCLUDED

int removeSongOrAlbum() {
    if(!curProvider->checkLicenseStatus()){
        cout << "Your license expired... You cannot remove song\n\n";
        return 0;
    }

    string choice;
    cout << "Do you want to delete a (s)ingle song or an entire (a)lbum? (s/a): ";
    cin >> choice;

    cin.ignore();  // Ignore the remaining newline character

    if (choice == "s" || choice == "S") {
        string delSong;
        cout << "Enter song Name to delete: ";
        getline(cin, delSong);

        // Check if the song exists in providerSongs
        auto it = find_if(providerSongs.begin(), providerSongs.end(), [&delSong](const Song& s) {
            return s.getName() == delSong;
        });

        if (it == providerSongs.end()) {
            cerr << "Song '" << delSong << "' not found in provider's songs." << endl;
            return 1;  // Return 1 to indicate song not found in provider's list
        }

        // Connect to the database
        MYSQL* conn = mysql_init(nullptr);

        conn = mysql_real_connect(conn, "localhost", "aravinth", "1234", "soundcloud", 0, NULL, 0);
        if (!conn) {
            cerr << "Error connecting to MySQL database: " << mysql_error(conn) << endl;
            return 0;
        }

        // Begin transaction
        if (mysql_query(conn, "START TRANSACTION")) {
            cerr << "Error starting transaction: " << mysql_error(conn) << endl;
            mysql_close(conn);
            return 0;
        }

        // Delete the song entry from provider_songs table
        string query = "DELETE FROM provider_songs WHERE songid IN (SELECT id FROM songs WHERE name = '" + delSong + "')";
        if (mysql_query(conn, query.c_str())) {
            cerr << "Error executing SQL query: " << mysql_error(conn) << endl;
            mysql_query(conn, "ROLLBACK");  // Rollback transaction on error
            mysql_close(conn);
            return 0;
        }

        // Delete the song from the database
        query = "DELETE FROM songs WHERE name = '" + delSong + "'";
        if (mysql_query(conn, query.c_str())) {
            cerr << "Error executing SQL query: " << mysql_error(conn) << endl;
            mysql_query(conn, "ROLLBACK");  // Rollback transaction on error
            mysql_close(conn);
            return 0;
        }

        // Commit transaction
        if (mysql_query(conn, "COMMIT")) {
            cerr << "Error committing transaction: " << mysql_error(conn) << endl;
            mysql_query(conn, "ROLLBACK");  // Rollback transaction on error
            mysql_close(conn);
            return 0;
        }

        cout << "Song '" << delSong << "' removed successfully." << endl;

        mysql_close(conn);
        return 1;  // Return 1 for success
    } else if (choice == "a" || choice == "A") {
        string delAlbum;
        cout << "Enter album Name to delete: ";
        getline(cin, delAlbum);

        // Check if any song from the album exists in providerSongs
        bool found = false;
        for (const auto& song : providerSongs) {
            if (song.getAlbum() == delAlbum) {
                found = true;
                break;
            }
        }

        if (!found) {
            cerr << "Album '" << delAlbum << "' not found in provider's songs." << endl;
            return 1;  // Return 1 to indicate album not found in provider's list
        }

        // Connect to the database
        MYSQL* conn = mysql_init(nullptr);

        conn = mysql_real_connect(conn, "localhost", "aravinth", "1234", "soundcloud", 0, NULL, 0);
        if (!conn) {
            cerr << "Error connecting to MySQL database: " << mysql_error(conn) << endl;
            return 0;
        }

        // Begin transaction
        if (mysql_query(conn, "START TRANSACTION")) {
            cerr << "Error starting transaction: " << mysql_error(conn) << endl;
            mysql_close(conn);
            return 0;
        }

        // Delete the album entries from provider_songs table
        string query = "DELETE FROM provider_songs WHERE songid IN (SELECT id FROM songs WHERE album = '" + delAlbum + "')";
        if (mysql_query(conn, query.c_str())) {
            cerr << "Error executing SQL query: " << mysql_error(conn) << endl;
            mysql_query(conn, "ROLLBACK");  // Rollback transaction on error
            mysql_close(conn);
            return 0;
        }

        // Delete the album from the database
        query = "DELETE FROM songs WHERE album = '" + delAlbum + "'";
        if (mysql_query(conn, query.c_str())) {
            cerr << "Error executing SQL query: " << mysql_error(conn) << endl;
            mysql_query(conn, "ROLLBACK");  // Rollback transaction on error
            mysql_close(conn);
            return 0;
        }

        // Commit transaction
        if (mysql_query(conn, "COMMIT")) {
            cerr << "Error committing transaction: " << mysql_error(conn) << endl;
            mysql_query(conn, "ROLLBACK");  // Rollback transaction on error
            mysql_close(conn);
            return 0;
        }

        cout << "Album '" << delAlbum << "' removed successfully." << endl;

        mysql_close(conn);
        return 1;  // Return 1 for success
    } else {
        cerr << "Invalid choice. Please enter 's' for single song or 'a' for album." << endl;
        return 0;  // Return 0 for invalid choice
    }
}


int removePodcast() {
    if(!curProvider->checkLicenseStatus()){
        cout << "Your license expired... You cannot remove podcast\n\n";
        return 0;
    }

    string choice;
    cout << "Do you want to delete a (s)ingle podcast or an entire (s)eries? (s/ser): ";
    cin >> choice;

    cin.ignore();  // Ignore the remaining newline character

    if (choice == "s" || choice == "S") {
        string delPodcast;
        cout << "Enter podcast Name to delete: ";
        getline(cin, delPodcast);

        // Check if the podcast exists in providerPodcasts
        auto it = find_if(providerPodcasts.begin(), providerPodcasts.end(), [&delPodcast](const Podcast& p) {
            return p.getName() == delPodcast;
        });

        if (it == providerPodcasts.end()) {
            cerr << "Podcast '" << delPodcast << "' not found in provider's podcasts." << endl;
            return 1;  // Return 1 to indicate podcast not found in provider's list
        }

        // Connect to the database
        MYSQL* conn = mysql_init(nullptr);

        conn = mysql_real_connect(conn, "localhost", "aravinth", "1234", "soundcloud", 0, NULL, 0);
        if (!conn) {
            cerr << "Error connecting to MySQL database: " << mysql_error(conn) << endl;
            return 0;
        }

        // Begin transaction
        if (mysql_query(conn, "START TRANSACTION")) {
            cerr << "Error starting transaction: " << mysql_error(conn) << endl;
            mysql_close(conn);
            return 0;
        }

        // Delete the podcast entry from provider_podcasts table (assuming a similar structure exists)
        string query = "DELETE FROM provider_podcasts WHERE podcastid IN (SELECT id FROM podcasts WHERE name = '" + delPodcast + "')";
        if (mysql_query(conn, query.c_str())) {
            cerr << "Error executing SQL query: " << mysql_error(conn) << endl;
            mysql_query(conn, "ROLLBACK");  // Rollback transaction on error
            mysql_close(conn);
            return 0;
        }

        // Delete the podcast from the database
        query = "DELETE FROM podcasts WHERE name = '" + delPodcast + "'";
        if (mysql_query(conn, query.c_str())) {
            cerr << "Error executing SQL query: " << mysql_error(conn) << endl;
            mysql_query(conn, "ROLLBACK");  // Rollback transaction on error
            mysql_close(conn);
            return 0;
        }

        // Commit transaction
        if (mysql_query(conn, "COMMIT")) {
            cerr << "Error committing transaction: " << mysql_error(conn) << endl;
            mysql_query(conn, "ROLLBACK");  // Rollback transaction on error
            mysql_close(conn);
            return 0;
        }

        cout << "Podcast '" << delPodcast << "' removed successfully." << endl;

        mysql_close(conn);
        return 1;  // Return 1 for success

    } else if (choice == "ser" || choice == "SER") {
        string delSeries;
        cout << "Enter series Name to delete: ";
        getline(cin, delSeries);

        // Check if any podcast from the series exists in providerPodcasts
        bool found = false;
        for (const auto& podcast : providerPodcasts) {
            if (podcast.getSeries() == delSeries) {
                found = true;
                break;
            }
        }

        if (!found) {
            cerr << "Series '" << delSeries << "' not found in provider's podcasts." << endl;
            return 1;  // Return 1 to indicate series not found in provider's list
        }

        // Connect to the database
        MYSQL* conn = mysql_init(nullptr);

        conn = mysql_real_connect(conn, "localhost", "aravinth", "1234", "soundcloud", 0, NULL, 0);
        if (!conn) {
            cerr << "Error connecting to MySQL database: " << mysql_error(conn) << endl;
            return 0;
        }

        // Begin transaction
        if (mysql_query(conn, "START TRANSACTION")) {
            cerr << "Error starting transaction: " << mysql_error(conn) << endl;
            mysql_close(conn);
            return 0;
        }

        // Delete the series entries from provider_podcasts table (assuming a similar structure exists)
        string query = "DELETE FROM provider_podcasts WHERE podcastid IN (SELECT id FROM podcasts WHERE series = '" + delSeries + "')";
        if (mysql_query(conn, query.c_str())) {
            cerr << "Error executing SQL query: " << mysql_error(conn) << endl;
            mysql_query(conn, "ROLLBACK");  // Rollback transaction on error
            mysql_close(conn);
            return 0;
        }

        // Delete the series from the database
        query = "DELETE FROM podcasts WHERE series = '" + delSeries + "'";
        if (mysql_query(conn, query.c_str())) {
            cerr << "Error executing SQL query: " << mysql_error(conn) << endl;
            mysql_query(conn, "ROLLBACK");  // Rollback transaction on error
            mysql_close(conn);
            return 0;
        }

        // Commit transaction
        if (mysql_query(conn, "COMMIT")) {
            cerr << "Error committing transaction: " << mysql_error(conn) << endl;
            mysql_query(conn, "ROLLBACK");  // Rollback transaction on error
            mysql_close(conn);
            return 0;
        }

        cout << "Series '" << delSeries << "' removed successfully." << endl;

        mysql_close(conn);
        return 1;  // Return 1 for success

    } else {
        cerr << "Invalid choice. Please enter 's' for single podcast or 'ser' for series." << endl;
        return 0;  // Return 0 for invalid choice
    }
}


int removeAd() {
    if(!curProvider->checkLicenseStatus()){
        cout << "Your license expired... You cannot remove advertisement\n\n";
        return 0;
    }


    string delAd;
    cout << "Enter Ad Name to delete: ";
    cin.ignore();
    getline(cin, delAd);

    // Check if the ad exists in providerAds
    auto it = find_if(providerAds.begin(), providerAds.end(), [&delAd](const Ad& ad) {
        return ad.getName() == delAd;
    });

    if (it == providerAds.end()) {
        cerr << "Ad '" << delAd << "' not found in provider's ads." << endl;
        return 1;  // Return 1 to indicate ad not found in provider's list
    }

    // Connect to the database
    MYSQL* conn = mysql_init(nullptr);

    conn = mysql_real_connect(conn, "localhost", "aravinth", "1234", "soundcloud", 0, NULL, 0);
    if (!conn) {
        cerr << "Error connecting to MySQL database: " << mysql_error(conn) << endl;
        return 0;
    }

    // Delete the ad from the database
    string query = "DELETE FROM ads WHERE name = '" + delAd + "'";
    if (mysql_query(conn, query.c_str())) {
        cerr << "Error executing SQL query: " << mysql_error(conn) << endl;
        mysql_close(conn);
        return 0;
    }

    cout << "Ad '" << delAd << "' removed successfully." << endl;

    mysql_close(conn);
    return 1;  // Return 1 for success
}

#endif // REMOVEOPERATION_H_INCLUDED
