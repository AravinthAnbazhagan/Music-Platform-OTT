#ifndef USERPAGE_H_INCLUDED
#define USERPAGE_H_INCLUDED

#include <bits/stdc++.h>
#include "songPage.h"

using namespace std;

//vector<Song> relatedSongs;

// User class Implementation
class User {
private:
    string username;
    string email;
    string password;
    string userType;
    int age;
    vector<string> selectedLanguages;
    vector<string> selectedGenres;
    vector<string> selectedArtists;

public:
    // Constructor
    User(const string& username, const string& email, const string& password, const string& uType, int age,
         const vector<string>& selectedLanguages, const vector<string>& selectedGenres,
         const vector<string>& selectedArtists)
        : username(username), email(email), password(password), userType(uType), age(age),
          selectedLanguages(selectedLanguages), selectedGenres(selectedGenres),
          selectedArtists(selectedArtists) {}

    // Getters
    string getUsername() const { return username; }
    string getEmail() const { return email; }
    string getPassword() const { return password; }
    int getAge() const { return age; }
    string getUserType() const { return userType; }
    vector<string> getSelectedLanguages() const { return selectedLanguages; }
    vector<string> getSelectedGenres() const { return selectedGenres; }
    vector<string> getSelectedArtists() const { return selectedArtists; }

    bool operator<(const User& other) const {
        return username < other.username;
    }

    bool operator==(const User& other) const {
        return username == other.username;
    }

    // Function to insert user data into the database
    void insertIntoDatabase() const {
        // Connect to MySQL Server
        MYSQL* conn;
        conn = mysql_init(0);
        conn = mysql_real_connect(conn, "localhost", "aravinth", "1234", "soundcloud", 0, NULL, 0);
        if (conn == NULL) {
            cout << "Failed to connect to database: " << mysql_error(conn) << endl;
            // Handle the error appropriately
        }

        // Prepare data for insertion
        string userType = "regular";
        stringstream ss;

        // Execute the INSERT query
        // Construct the SQL query with placeholders
        ss << "INSERT INTO `users` (username, email, password, age, usertype) VALUES ('" << username << "', '" << email << "', '" << password << "', " << age << ", '" << userType << "')";

        // Convert the query to a string
        string query = ss.str();
        const char* q = query.c_str();

        int qstate = mysql_query(conn, q);
        if(qstate == 0){
            cout << "Registration successful..!\n" << endl;
            int userID = mysql_insert_id(conn);

            //cout << "User ID : " << userID << endl;
            insertUserLanguages(conn, userID);
            insertUserGenres(conn, userID);
            insertUserArtists(conn, userID);
            cout << "Welcome to our application. You successfully created your account. \nNow you can start you can continue your journey by doing log-in...!\n\n";
        }
        else{
            cout << "Account creation Failed. Do re-registration.\n\n" << endl;
        }
    }

    void insertUserLanguages(MYSQL* conn, int userID) const {
        for (const string& lang : selectedLanguages) {
            stringstream ss;
            ss << "INSERT INTO `user_languages` (userid, language) VALUES (" << userID << ", '" << lang << "')";
            string query = ss.str();
            const char* q = query.c_str();
            int qstate = mysql_query(conn, q);
            if (qstate != 0) {
                cout << "Invalid Language selection : " << mysql_error(conn) << endl;
            }
        }
    }

    void insertUserGenres(MYSQL* conn, int userID) const {
        for (const string& genre : selectedGenres) {
            stringstream ss;
            ss << "INSERT INTO `user_genres` (userid, genre) VALUES (" << userID << ", '" << genre << "')";
            string query = ss.str();
            const char* q = query.c_str();
            int qstate = mysql_query(conn, q);
            if (qstate != 0) {
                cout << "Invalid genre selection : " << mysql_error(conn) << endl;
            }
        }
    }

    void insertUserArtists(MYSQL* conn, int userID) const {
        for (const string& artist : selectedArtists) {
            // Check if the artist exists in the artists table
            string selectQuery = "SELECT id FROM artists WHERE name = '" + artist + "'";
            const char* selectQ = selectQuery.c_str();
            int selectQState = mysql_query(conn, selectQ);
            if (selectQState != 0) {
                cout << "Failed to select artist: " << mysql_error(conn) << endl;
                continue; // Skip to the next artist if selection fails
            }

            MYSQL_RES* result = mysql_store_result(conn);
            if (result == NULL) {
                cout << "Failed to store result: " << mysql_error(conn) << endl;
                continue; // Skip to the next artist if result cannot be stored
            }

            MYSQL_ROW row = mysql_fetch_row(result);
            if (row == NULL) {
                cout << "Artist '" << artist << "' does not exist in the database." << endl;
                mysql_free_result(result);
                continue; // Skip to the next artist if artist not found
            }

            int artistID = atoi(row[0]);
            mysql_free_result(result);

            // Insert the artist into the user_artists table
            stringstream ss;
            ss << "INSERT INTO `user_artists` (userid, artistid) VALUES (" << userID << ", " << artistID << ")";
            string query = ss.str();
            const char* q = query.c_str();
            int qstate = mysql_query(conn, q);
            if (qstate != 0) {
                cout << "Insert artist selection : " << mysql_error(conn) << endl;
            }
        }
    }
};

class UserSubscription {
public:
    std::string username;
    std::string subscriptionPlan;
    std::tm expiryDate;

    UserSubscription(const std::string &username, const std::string &subscriptionPlan, const std::tm &expiryDate)
        : username(username), subscriptionPlan(subscriptionPlan), expiryDate(expiryDate) {}

    void display() const {
        std::cout << "Username: " << username << std::endl;
        std::cout << "Subscription Plan: " << subscriptionPlan << std::endl;
        std::cout << "Expiry Date: " << std::put_time(&expiryDate, "%Y-%m-%d") << std::endl;
    }
};


// -------------------------------------------------------------------------------------------------------------------------------------------------------
vector<User> users; //********* To store all existing users *********
// Loading all users existing in the database. This process require below four functions and 'users' -> global variable
vector<std::string> getUserLanguages(int userId, MYSQL* conn) {
    std::vector<std::string> languages;
    std::string query = "SELECT language FROM user_languages WHERE userid = " + std::to_string(userId);
    const char* q = query.c_str();
    int qstate = mysql_query(conn, q);
    if (!qstate) {
        MYSQL_RES* result = mysql_store_result(conn);
        if (result) {
            MYSQL_ROW row;
            while ((row = mysql_fetch_row(result))) {
                languages.push_back(row[0]);
            }
            mysql_free_result(result);
        }
    } else {
        cerr << "Error executing query: " << mysql_error(conn) << std::endl;
    }
    return languages;
}

vector<string> getUserGenres(int userId, MYSQL* conn) {
    vector<string> genres;
    string query = "SELECT genre FROM user_genres WHERE userid = " + std::to_string(userId);
    const char* q = query.c_str();
    int qstate = mysql_query(conn, q);
    if (!qstate) {
        MYSQL_RES* result = mysql_store_result(conn);
        if (result) {
            MYSQL_ROW row;
            while ((row = mysql_fetch_row(result))) {
                genres.push_back(row[0]);
            }
            mysql_free_result(result);
        }
    } else {
        cerr << "Error executing query: " << mysql_error(conn) << std::endl;
    }
    return genres;
}

vector<string> getArtistNamesForUser(MYSQL* conn, int userId) {
    vector<string> artistNamesVec;

    // Construct the SQL query
    string query = "SELECT name FROM artists WHERE id IN (SELECT artistid FROM user_artists WHERE userid = " + to_string(userId) + ")";
    const char* q = query.c_str();

    // Execute SQL query
    int qstate = mysql_query(conn, q);
    if (qstate != 0) {
        cerr << "Error executing SQL query: " << mysql_error(conn) << std::endl;
        return artistNamesVec; // Return empty vector in case of error
    }

    // Get query result
    MYSQL_RES* result = mysql_store_result(conn);
    if (!result) {
        cerr << "Error retrieving result set: " << mysql_error(conn) << endl;
        return artistNamesVec; // Return empty vector in case of error
    }

    // Fetch rows and store artist names in the vector
    MYSQL_ROW row;
    while ((row = mysql_fetch_row(result))) {
        artistNamesVec.push_back(row[0]);
    }
    // Free result set
    mysql_free_result(result);

    return artistNamesVec;
}

string userName;

void loadUsers() {
    MYSQL* conn = mysql_init(nullptr);

    conn = mysql_real_connect(conn, "localhost", "aravinth", "1234", "soundcloud", 0, NULL, 0);
    if (!conn) {
        std::cerr << "Error connecting to MySQL database: " << mysql_error(conn) << std::endl;
        return;
    }

    //vector<User> users;

    string selectQuery = "SELECT username, email, password, age, usertype, id FROM `users`";
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
        string uname = row[0] ? row[0] : "";
        string mail = row[1] ? row[1] : "";
        string pwd = row[2] ? row[2] : "";
        int age = row[3] ? stoi(row[3]) : 0;
        string userType = row[4] ? row[4] : "";
        int id = row[5] ? stoi(row[5]) : 0;

        vector<string> languages = getUserLanguages(id, conn);
        vector<string> genres = getUserGenres(id, conn);
        vector<string> artists = getArtistNamesForUser(conn, id);


        User u(uname, mail, pwd, userType, age, languages, genres, artists);
        users.push_back(u);
    }
    mysql_free_result(result);
    mysql_close(conn);

    // Output the retrieved data
    /*for (const auto& user : users) {
        cout << "Username: " << user.getUsername() << endl;
        cout << "Email: " << user.getEmail() << endl;
        cout << "Password: " << user.getPassword() << endl;
        cout << "User Type: " << user.getUserType() << endl;
        cout << "Age: " << user.getAge() << endl;

        cout << "Selected Languages: ";
        for (const auto& lang : user.getSelectedLanguages()) {
            cout << lang << " ";
        }
        cout << endl;

        cout << "Selected Genres: ";
        for (const auto& genre : user.getSelectedGenres()) {
            cout << genre << " ";
        }
        cout << endl;

        cout << "Selected Artists: ";
        for (const auto& artist : user.getSelectedArtists()) {
            cout << artist << " ";
        }
        cout << endl;

        cout << "--------------------------" << endl;

 }*/
}

std::tm parseDate(const std::string &dateStr) {
    std::tm tm = {};
    std::istringstream ss(dateStr);
    ss >> std::get_time(&tm, "%Y-%m-%d");
    return tm;
}

vector<UserSubscription> userSubscriptions;

void loadUserSubscriptions() {
    MYSQL* conn = mysql_init(nullptr);

    if (!conn) {
        std::cerr << "MySQL initialization failed" << std::endl;
        return;
    }

    conn = mysql_real_connect(conn, "localhost", "aravinth", "1234", "soundcloud", 0, NULL, 0);
    if (!conn) {
        std::cerr << "Error connecting to MySQL database: " << mysql_error(conn) << std::endl;
        return;
    }

    // Query to retrieve user subscriptions with usernames and subscription names
    std::string query = R"(
        SELECT users.username, subscriptions.name, user_subscriptions.exp_date
        FROM user_subscriptions
        JOIN users ON user_subscriptions.user_id = users.id
        JOIN subscriptions ON user_subscriptions.sid = subscriptions.id
    )";
    int queryState = mysql_query(conn, query.c_str());

    if (queryState != 0) {
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
        std::string username = row[0] ? row[0] : "";
        std::string subscriptionPlan = row[1] ? row[1] : "";
        std::tm expiryDate = row[2] ? parseDate(row[2]) : std::tm{};

        UserSubscription userSubscription(username, subscriptionPlan, expiryDate);
        userSubscriptions.push_back(userSubscription);
    }

    mysql_free_result(result);
    mysql_close(conn);
}



// ---------------------------------------------------------------------------------------------------------------------------------------------------------

//******** Implementation of user registeration and login functions are in below header files **********
#include "userLogin.h"
#include "userRegister.h"

// menu for user !!!
void displayUserMenu() {
    int choice;
    while(true){
        cout << "Welcome user...\n";
        cout << setw(2) << "1. " << "Login\n";
        cout << setw(2) << "2. " << "Register\n";
        cout << "What do you want to do    : ";
        cin >> choice;
        cout << "\n\n";

        switch (choice) {
            case 1:
                userLogin();
                break;
            case 2:
                userRegister();
                break;
            default:
                cout << "Invalid choice. Retry..!\n\n";
                break;
        }
    }
}

#endif // USERPAGE_H_INCLUDED