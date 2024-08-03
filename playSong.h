#ifndef PLAYSONG_H_INCLUDED
#define PLAYSONG_H_INCLUDED


#include <windows.h>
#include <mmsystem.h>
#include <iostream>
#include <vector>
#include <string>
#include <conio.h> // For _kbhit() and _getch()

#pragma comment(lib, "winmm.lib")

using namespace std;


// Global variables
//vector<Song> playlist;
size_t currentSongIndex = 1;
bool isPaused = false;

// Function to play the song at the given index
void playSong(size_t index) {
    if (index < songs.size()) {
        //string curSong = songs[index].getPath();
        string curSong = "Vaathi Coming.wav";
        cout << "Now playing: " << curSong << endl;
        PlaySound(TEXT(curSong.c_str()), NULL, SND_ASYNC | SND_FILENAME);
        isPaused = false;
    } else {
        cout << "Invalid song index." << endl;
    }
}

// Function to pause the playback
void pauseSong() {
    if (!isPaused) {
        cout << "Paused." << endl;
        PlaySound(NULL, NULL, SND_PURGE);
        isPaused = true;
    } else {
        cout << "Already paused." << endl;
    }
}

// Function to resume the playback
void resumeSong() {
    if (isPaused) {
        cout << "Resumed." << endl;
        playSong(currentSongIndex);
    } else {
        cout << "Playback is not paused." << endl;
    }
}

// Function to skip to the next song
void skipForward() {
    if (currentSongIndex + 1 < songs.size()) {
        currentSongIndex++;
        playSong(currentSongIndex);
    } else {
        cout << "No more songs in the playlist." << endl;
    }
}

// Function to skip to the previous song
void skipBackward() {
    if (currentSongIndex > 0) {
        currentSongIndex--;
        playSong(currentSongIndex);
    } else {
        cout << "This is the first song in the playlist." << endl;
    }
}

// Function to stop the playback
void stopSong() {
    cout << "Stopped." << endl;
    PlaySound(NULL, NULL, SND_PURGE);
    isPaused = false;
}

// Function to display the menu
void displayMenu() {
    cout << "Press 1 to pause the song." << endl;
    cout << "Press 2 to resume the song." << endl;
    cout << "Press 3 to skip forward the song." << endl;
    cout << "Press 4 to skip backward the song." << endl;
    cout << "Press q to quit." << endl;
}

// Function to handle user input
void handleUserInput() {
    if (_kbhit()) {
        char key = _getch();
        switch (key) {
            case '1':
                pauseSong();
                break;
            case '2':
                resumeSong();
                break;
            case '3':
                skipForward();
                break;
            case '4':
                skipBackward();
                break;
            case 'q':
                stopSong();
                return;
                break;
            default:
                cout << "Invalid input." << endl;
                break;
        }
    }
}



int playSongInvoke() {
    // Sample playlist


    // Play the first song
    playSong(currentSongIndex);
    displayMenu();

    // Main loop to handle user input
    while (true) {
        // Check for user input
        handleUserInput();
        // Sleep briefly to reduce CPU usage
        Sleep(100);
    }

    return 0;
}

#endif // PLAYSONG_H_INCLUDED



