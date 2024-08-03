#ifndef PODCASTPAGE_H_INCLUDED
#define PODCASTPAGE_H_INCLUDED

#include <bits/stdc++.h>

using namespace std;

// Podcast class definition
class Podcast {
private:
    string name;
    float duration;
    string genre;
    string language;
    string series;
    string path;

public:
    // Constructor
    Podcast(const string& name, float duration, const string& genre, const string& language, const string& series, const string& path)
        : name(name), duration(duration), genre(genre), language(language), series(series), path(path) {}

    // Getters
    string getName() const { return name; }
    float getDuration() const { return duration; }
    string getGenre() const { return genre; }
    string getLanguage() const { return language; }
    string getSeries() const { return series; }
    string getPath() const { return path; }

    void insertIntoDatabase() {
        MYSQL *con = mysql_init(nullptr);

        con = mysql_real_connect(con, "localhost", "aravinth", "1234", "soundcloud", 0, nullptr, 0);

        stringstream ss;
        ss << "INSERT INTO podcasts(name, duration, genre, language, series, path) VALUES('"
           << name << "', " << duration << ", '" << genre << "', '" << language << "', '"
           << series << "', '" << path << "')";

        string query = ss.str();

        mysql_query(con, query.c_str());

        cout << "Podcast inserted successfully." << endl;
    }

};

vector<Podcast> podcasts;

void loadPodcasts() {
    MYSQL* con = mysql_init(nullptr);

    con = mysql_real_connect(con, "localhost", "aravinth", "1234", "soundcloud", 0, NULL, 0);

    mysql_query(con, "SELECT name, duration, genre, language, series, path FROM podcasts");

    MYSQL_RES *result = mysql_store_result(con);

    int num_fields = mysql_num_fields(result);
    MYSQL_ROW row;

    podcasts.clear(); // Clear the vector before refilling it

    while ((row = mysql_fetch_row(result))) {
        string name = row[0] ? row[0] : "";
        float duration = row[1] ? stof(row[1]) : 0.0;
        string genre = row[2] ? row[2] : "";
        string language = row[3] ? row[3] : "";
        string series = row[4] ? row[4] : "";
        string path = row[5] ? row[5] : "";

        podcasts.emplace_back(name, duration, genre, language, series, path);
    }

    mysql_free_result(result);
}

/*void displayPodcasts() {
    cout << "Name | Duration | Genre | Language | Series | Path" << endl;
    for (const auto &podcast : podcasts) {
        podcast.display();
    }
}*/




/*
void deletePodcast(MYSQL *con) {
    string name;
    cout << "Enter the name of the podcast to delete: ";
    cin.ignore();
    getline(cin, name);

    stringstream ss;
    ss << "DELETE FROM podcasts WHERE name = '" << name << "'";
    string query = ss.str();

    if (mysql_query(con, query.c_str())) {
        finish_with_error(con);
    }

    auto it = remove_if(podcasts.begin(), podcasts.end(), [&name](const Podcast &p) {
        return p.getName() == name;
    });

    if (it != podcasts.end()) {
        podcasts.erase(it, podcasts.end());
        podcastTree.deleteNode(name);
        cout << "Podcast deleted successfully." << endl;
    } else {
        cout << "Podcast not found in the local storage." << endl;
    }
}*/

#endif // PODCASTPAGE_H_INCLUDED
