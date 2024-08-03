#ifndef SEARCHOPTIONPROVIDER_H_INCLUDED
#define SEARCHOPTIONPROVIDER_H_INCLUDED

void searchSongs() {
    string searchTerm;
    char choice;

    cout << "How do you want to search...?" << endl;
    cout << "1. Song name" << endl;
    cout << "2. Album name" << endl;
    cout << "Enter your choice         : ";
    cin >> choice;

    bool searchBySongName = (choice == '1');

    if (searchBySongName)
        cout << "Enter song name to search : ";
    else
        cout << "Enter album name to search: ";

    cin.ignore(); // Ignore any previous input
    getline(cin, searchTerm);

    // Print table header
    cout << setw(25) << left << "Name";
    cout << setw(25) << left << "Artist";
    cout << setw(15) << left << "Duration";
    cout << setw(20) << left << "Language";
    cout << setw(20) << left << "Genre";
    cout << setw(30) << left << "Album";
    cout << setw(30) << left << "Path";
    cout << endl;

    // Print separator line
    cout << setfill('-') << setw(145) << "-" << endl;
    cout << setfill(' ');

    // Search for the song by name or album
    for (const auto& song : songs) {
        if (searchBySongName) {
            if (song.getName() == searchTerm) {
                // Print song details
                cout << setw(25) << left << song.getName();
                cout << setw(25) << left << song.getArtist();
                cout << setw(15) << left << song.getDuration();
                cout << setw(20) << left << song.getLanguage();
                cout << setw(20) << left << song.getGenre();
                cout << setw(30) << left << song.getAlbum();
                cout << setw(30) << left << song.getPath();
                cout << endl;
                return; // Stop after finding the first matching song
            }
        } else { // Search by album
            if (song.getAlbum() == searchTerm) {
                // Print song details
                cout << setw(25) << left << song.getName();
                cout << setw(25) << left << song.getArtist();
                cout << setw(15) << left << song.getDuration();
                cout << setw(20) << left << song.getLanguage();
                cout << setw(20) << left << song.getGenre();
                cout << setw(30) << left << song.getAlbum();
                cout << setw(30) << left << song.getPath();
                cout << endl;
            }
        }
    }

    // If song not found
    if (searchBySongName)
        cout << "Song '" << searchTerm << "' not found." << endl;
    else
        cout << "No songs found for album '" << searchTerm << "'." << endl;
    cout << "\n";
}


void searchPodcasts() {
    string searchTerm;
    char choice;

    cout << "How do you want to search....?" << endl;
    cout << "1. Podcast name" << endl;
    cout << "2. Series name" << endl;
    cout << "Enter your choice             : ";
    cin >> choice;

    bool searchByPodcastName = (choice == '1');

    if (searchByPodcastName)
        cout << "Enter podcast name to search  : ";
    else
        cout << "Enter series name to search   : ";

    cin.ignore(); // Ignore any previous input
    getline(cin, searchTerm);

    // Print table header
    cout << setw(25) << left << "Name";
    cout << setw(25) << left << "Duration";
    cout << setw(30) << left << "Language";
    cout << setw(30) << left << "Path";
    cout << endl;

    // Print separator line
    cout << setfill('-') << setw(110) << "-" << endl;
    cout << setfill(' ');

    // Search for the podcast by name or series
    for (const auto& podcast : podcasts) {
        if (searchByPodcastName) {
            if (podcast.getName() == searchTerm) {
                // Print podcast details
                cout << setw(25) << left << podcast.getName();
                cout << setw(25) << left << podcast.getDuration();
                cout << setw(30) << left << podcast.getLanguage();
                cout << setw(30) << left << podcast.getPath();
                cout << endl;
                return; // Stop after finding the first matching podcast
            }
        } else { // Search by series
            if (podcast.getSeries() == searchTerm) {
                // Print podcast details
                cout << setw(25) << left << podcast.getName();
                cout << setw(25) << left << podcast.getDuration();
                cout << setw(30) << left << podcast.getLanguage();
                cout << setw(30) << left << podcast.getPath();
                cout << endl;
            }
        }
    }

    // If podcast not found
    if (searchByPodcastName)
        cout << "Podcast '" << searchTerm << "' not found." << endl;
    else
        cout << "No podcasts found for series '" << searchTerm << "'." << endl;
    cout << "\n";
}

void searchAds() {
    string searchTerm;

    cout << "Enter ad name to search: ";
    cin.ignore(); // Ignore any previous input
    getline(cin, searchTerm);

    // Print table header
    cout << setw(25) << left << "Name";
    cout << setw(15) << left << "Duration";
    cout << setw(30) << left << "Path";
    cout << endl;

    // Print separator line
    cout << setfill('-') << setw(70) << "-" << endl;
    cout << setfill(' ');

    // Search for the ad by name
    for (const auto& ad : ads) {
        if (ad.getName() == searchTerm) {
            // Print ad details
            cout << setw(25) << left << ad.getName();
            cout << setw(15) << left << ad.getDuration();
            cout << setw(30) << left << ad.getPath();
            cout << endl;
            return; // Stop after finding the first matching ad
        }
    }

    // If ad not found
    cout << "Ad '" << searchTerm << "' not found." << endl;
    cout << endl;
}



#endif // SEARCHOPTIONPROVIDER_H_INCLUDED
