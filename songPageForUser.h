#ifndef SONGPAGEFORUSER_H_INCLUDED
#define SONGPAGEFORUSER_H_INCLUDED

#include <bits/stdc++.h>
#include "searchSong.h"
#include "playlistPage.h"
#include "jaiSub.h"
#include "jaiRec.h"

using namespace std;

void userWorkMenu() {
    int choice;
    while(true){
        cout << "Enter what do you want to do...\n";
        cout << "1. Listen Song\n";
        cout << "2. Search Song\n";
        cout << "3. Manage Playlist\n";
        cout << "4. Subscription\n";
        cout << "5. Exit\n";
        cout << "Enter option   : ";
        cin >> choice;
        cout << endl;

        switch(choice) {
        case 1:
            //cout << "Has to be implemented..\n";
            show(recommandedSongs);
            break;
        case 2:
            searchSong();
            break;
        case 3:
            playlistMenu();
            break;
        case 4:
            subscriptionWork();
            break;
        case 5:
            break;
        default:
            cout << "Invalid choice. Try again...\n\n";
        }
        if(choice == 5)     break;
    }
}

#endif // SONGPAGEFORUSER_H_INCLUDED
