#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <windows.h>
#include <mysql.h>
#include <iomanip>
#include <fstream>


vector<int> getMultipleChoices(int maxChoice) {
    vector<int> choices;
    string input;
    getline(cin >> ws, input);  // Get the entire line of input
    istringstream stream(input);
    int choice;
    while (stream >> choice) {
        if (choice >= 1 && choice <= maxChoice) {
            choices.push_back(choice);
        } else {
            cout << "Invalid choice: " << choice << "\n";
        }
    }
    return choices;
}


void userRegister() {
    string username, email, password, confirmPassword;
    int age;

    string filename = R"(C:\Users\aravi\Downloads\ascii-text-art (1).txt)";
    ifstream inputFile(filename);
    string line;
    while (std::getline(inputFile, line)) {
        cout << line << endl;
    }
    inputFile.close();
    cout << "\n\n";

    cout << "Enter Username     : ";
    cin >> username;

    cout << "Enter Email        : ";
    cin >> email;

    pwd:
    cout << "Enter Password     : ";
    cin >> password;

    cout << "Confirm Password   : ";
    cin >> confirmPassword;

    if (password != confirmPassword) {
        cout << "Passwords do not match. Registration failed.\n";
        goto pwd;
    }

    cout << "Enter Age          : ";
    cin >> age;
    cout << "\n";

    cout << "Select your language in below options. \nYou can choose multiple languages...\n";
    vector<string> languages = {"English", "Tamil", "Hindi", "Telugu", "Kannada", "Malayalam", "Bengali", "Spanish", "French", "German"};
    for (size_t i = 0; i < languages.size(); ++i) {
        cout << setw(2) << i + 1 << ". " << languages[i] << "\n";
    }
    cout << "Select Language(s) : ";

    vector<int> languageChoices = getMultipleChoices(languages.size());
    vector<string> selectedLanguages;
    for (int choice : languageChoices) {
        selectedLanguages.push_back(languages[choice - 1]);
    }
    cout << "\n\n";


    cout << "Select your favorite genres as much as you want... :\n";
    vector<string> genres = {"Love", "Beast", "Mass Hits", "Alone", "Melting", "Vibe", "Party", "Sad", "Classical", "Pop"};
    for (size_t i = 0; i < genres.size(); ++i) {
        cout << setw(2) << i + 1 << ". " << genres[i] << "\n";
    }
    cout << "Select Genre(s): ";

    vector<int> genreChoices = getMultipleChoices(genres.size());
    vector<string> selectedGenres;
    for (int choice : genreChoices) {
        selectedGenres.push_back(genres[choice - 1]);
    }
    cout << "\n\n";

    cout << "Select your favorite artists in below option. \nArtists are from your favorite languages.You can choose multiple languages...\n";
    vector<string> artists;
    for (const string& lang : selectedLanguages) {
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
    }


    for (size_t i = 0; i < artists.size(); i++) {
        cout << i + 1 << ". " << artists[i] << endl;
    }


    cout << "Select Artists(s): ";
    vector<int> artistChoices = getMultipleChoices(artists.size());
    vector<string> selectedArtists;
    for (int choice : artistChoices) {
        selectedArtists.push_back(artists[choice - 1]);
    }
    cout << "\n\n";

    string uType = "regular";

    User u1(username, email, password, uType, age, selectedLanguages, selectedGenres, selectedArtists);
    u1.insertIntoDatabase();
}

