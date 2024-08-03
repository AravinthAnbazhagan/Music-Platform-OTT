#include <iostream>
#include <windows.h>
#include <mysql.h>
#include <string>
#include <sstream>
#include "userPage.h"
#include "providerPage.h"
#include "playSong.h"
#include "AdminPage.h"
//#include "jaiRec.h"
#include "playSong.h"


using namespace std;


// Connecting to the database -----------------


/* Start Appache and Mysql */


int main() {
    string filename = R"(C:\Users\aravi\Downloads\ascii-text-art.txt)";
    ifstream inputFile(filename);
    string line;
    while (std::getline(inputFile, line)) {
        cout << line << endl;
    }
    inputFile.close();
    cout << "\n\n";

    //playSongMain();
    //reccommand();
    //playSongInvoke();
    //plSong();

    int roleChoice;
    bool running = true;

    while (running) {
        loadUsers();
        loadProviders();

        cout << setw(2) << "1. " << "User\n";
        cout << setw(2) << "2. " << "Provider\n";
        cout << setw(2) << "3. " << "Admin\n";
        cout << setw(2) << "4. " << "Exit\n";
        cout << "Select who you are to continue journey... : ";
        cin >> roleChoice;
        cout << "\n\n";

        switch (roleChoice) {
            case 1:
                displayUserMenu();
                break;
            case 2:
                displayProviderMenu();
                break;
            case 3:
                adminMenu();
                break;
            case 4:
                running = false;
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    }

    cout << "Exiting program.\n";
    return 0;
}


