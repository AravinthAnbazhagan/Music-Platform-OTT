#ifndef SHOWOPERATIONPROVIDER_H_INCLUDED
#define SHOWOPERATIONPROVIDER_H_INCLUDED

#include <iomanip> // for std::setw

void showSongs() {
    // Check if the vector is empty
    if (providerSongs.empty()) {
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
    for (const auto& song : providerSongs) {
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


void showPodcasts() {
    if (providerPodcasts.empty()) {
        cout << "No podcasts available." << endl;
        return;
    }

    // Define table headers
    cout << left << setw(20) << "Name"
         << setw(10) << "Duration"
         << setw(15) << "Genre"
         << setw(15) << "Language"
         << setw(20) << "Series"
         << setw(30) << "Path" << endl;

    // Print a line to separate headers from the content
    cout << string(110, '-') << endl;

    // Loop through the providerPodcasts vector and print each podcast in table format
    for (const auto& podcast : providerPodcasts) {
        cout << left << setw(20) << podcast.getName()
             << setw(10) << podcast.getDuration()
             << setw(15) << podcast.getGenre()
             << setw(15) << podcast.getLanguage()
             << setw(20) << podcast.getSeries()
             << setw(30) << podcast.getPath() << endl;
    }
    cout << "\n";
}


void showAds() {
    // Print table header
    cout << setw(20) << left << "Name";
    cout << setw(10) << left << "Duration";
    cout << setw(30) << left << "Path";
    cout << endl;

    // Print separator line
    cout << setfill('-') << setw(60) << "-" << endl;
    cout << setfill(' ');

    // Print each ad's details
    for (const auto& ad : providerAds) {
        cout << setw(20) << left << ad.getName();
        cout << setw(10) << left << ad.getDuration();
        cout << setw(30) << left << ad.getPath();
        cout << endl;
    }
    cout << "\n";
}

#endif // SHOWOPERATIONPROVIDER_H_INCLUDED
