#ifndef RECOMMANDATION_H_INCLUDED
#define RECOMMANDATION_H_INCLUDED

void loadUserHistory(std::vector<Song> &userHistory) {
    MYSQL* conn = mysql_init(0);

    conn = mysql_real_connect(conn, "localhost", "aravinth", "1234", "soundcloud", 0, NULL, 0);
    if (!conn) {
        std::cerr << "Error connecting to MySQL database: " << mysql_error(conn) << std::endl;
        return;
    }

    std::string query = "SELECT s.* FROM user_history uh JOIN songs s ON uh.songid = s.id";
    const char* selectQ = query.c_str();
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
        //int id = row[0] ? std::stoi(row[0]) : 0;
        std::string name = row[1] ? row[1] : "";
        std::string artist = row[2] ? row[2] : "";
        float duration = row[3] ? std::stof(row[3]) : 0.0f;
        std::string language = row[4] ? row[4] : "";
        std::string genre = row[5] ? row[5] : "";
        std::string album = row[6] ? row[6] : "";
        std::string path = row[7] ? row[7] : "";

        Song song(name, artist, duration, language, genre, album, path);
        userHistory.push_back(song);
    }

    mysql_free_result(result);
    mysql_close(conn);
}

void loadUserGenres(std::vector<Song> &userGenres) {
    MYSQL* conn = mysql_init(0);

    conn = mysql_real_connect(conn, "localhost", "aravinth", "1234", "soundcloud", 0, NULL, 0);
    if (!conn) {
        std::cerr << "Error connecting to MySQL database: " << mysql_error(conn) << std::endl;
        return;
    }

    std::string query = "SELECT s.* FROM user_genres ug JOIN songs s ON ug.genre = s.genre";
    const char* selectQ = query.c_str();
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
        //int id = row[0] ? std::stoi(row[0]) : 0;
        std::string name = row[1] ? row[1] : "";
        std::string artist = row[2] ? row[2] : "";
        float duration = row[3] ? std::stof(row[3]) : 0.0f;
        std::string language = row[4] ? row[4] : "";
        std::string genre = row[5] ? row[5] : "";
        std::string album = row[6] ? row[6] : "";
        std::string path = row[7] ? row[7] : "";

        Song song(name, artist, duration, language, genre, album, path);
        userGenres.push_back(song);
    }

    mysql_free_result(result);
    mysql_close(conn);
}

void loadUserArtists(std::vector<Song> &userArtists) {
    MYSQL* conn = mysql_init(0);

    conn = mysql_real_connect(conn, "localhost", "aravinth", "1234", "soundcloud", 0, NULL, 0);
    if (!conn) {
        std::cerr << "Error connecting to MySQL database: " << mysql_error(conn) << std::endl;
        return;
    }

    std::string query = "SELECT s.* FROM user_artists ua JOIN songs s ON ua.artistid = s.id";
    const char* selectQ = query.c_str();
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
        //int id = row[0] ? std::stoi(row[0]) : 0;
        std::string name = row[1] ? row[1] : "";
        std::string artist = row[2] ? row[2] : "";
        float duration = row[3] ? std::stof(row[3]) : 0.0f;
        std::string language = row[4] ? row[4] : "";
        std::string genre = row[5] ? row[5] : "";
        std::string album = row[6] ? row[6] : "";
        std::string path = row[7] ? row[7] : "";

        Song song(name, artist, duration, language, genre, album, path);
        userArtists.push_back(song);
    }

    mysql_free_result(result);
    mysql_close(conn);
}

void loadUserLanguages(std::vector<Song> &userLanguages) {
    MYSQL* conn = mysql_init(0);

    conn = mysql_real_connect(conn, "localhost", "aravinth", "1234", "soundcloud", 0, NULL, 0);
    if (!conn) {
        std::cerr << "Error connecting to MySQL database: " << mysql_error(conn) << std::endl;
        return;
    }

    std::string query = "SELECT s.* FROM user_languages ul JOIN songs s ON ul.language = s.language";
    const char* selectQ = query.c_str();
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
        //int id = row[0] ? std::stoi(row[0]) : 0;
        std::string name = row[1] ? row[1] : "";
        std::string artist = row[2] ? row[2] : "";
        float duration = row[3] ? std::stof(row[3]) : 0.0f;
        std::string language = row[4] ? row[4] : "";
        std::string genre = row[5] ? row[5] : "";
        std::string album = row[6] ? row[6] : "";
        std::string path = row[7] ? row[7] : "";

        Song song(name, artist, duration, language, genre, album, path);
        userLanguages.push_back(song);
    }

    mysql_free_result(result);
    mysql_close(conn);
}

/*
class Graph {
private:
    std::unordered_map<Song, std::unordered_map<Song, float>> adjList;

public:
    void addEdge(const Song& from, const Song& to, float weight) {
        adjList[from][to] = weight;
        adjList[to][from] = weight; // Assuming undirected graph
    }
};

Graph formGraph(const std::vector<Song>& userHistory, const std::vector<Song>& userArtists,
const std::vector<Song>& userLanguages, const std::vector<Song>& userGenres) {
    Graph graph;
    vstd::random_device rd;
    std::mt19937 gen(rd());

    // Shuffle each vector
    std::vector<Song> shuffledUserHistory = userHistory;
    std::shuffle(shuffledUserHistory.begin(), shuffledUserHistory.end(), gen);

    std::vector<Song> shuffledUserArtists = userArtists;
    std::shuffle(shuffledUserArtists.begin(), shuffledUserArtists.end(), gen);

    std::vector<Song> shuffledUserLanguages = userLanguages;
    std::shuffle(shuffledUserLanguages.begin(), shuffledUserLanguages.end(), gen);

    std::vector<Song> shuffledUserGenres = userGenres;
    std::shuffle(shuffledUserGenres.begin(), shuffledUserGenres.end(), gen);

    // Get 5 songs from each vector
    int numSongs = 5;
    for (int i = 0; i < numSongs; ++i) {
        graph.addEdge(shuffledUserHistory[i], shuffledUserArtists[i], numSongs - i);
        graph.addEdge(shuffledUserArtists[i], shuffledUserLanguages[i], numSongs - i);
        graph.addEdge(shuffledUserLanguages[i], shuffledUserGenres[i], numSongs - i);
    }

    return graph;
}*/


#endif // RECOMMANDATION_H_INCLUDED
