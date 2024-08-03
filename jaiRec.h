#ifndef JAIREC_H_INCLUDED
#define JAIREC_H_INCLUDED

#include "userLogin.h"
#include "songPage.h"


vector<Song> recommandedSongs;

// Create the adjacency matrix
std::vector<std::vector<int>> createAdjacencyMatrix(const std::vector<Song>& songs) {
    int n = songs.size();
    std::vector<std::vector<int>> adjMatrix(n, std::vector<int>(n, 0));

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (songs[i].getArtist() == songs[j].getArtist()) {
                adjMatrix[i][j] = adjMatrix[j][i] = 1;
            } else if (songs[i].getGenre() == songs[j].getGenre()) {
                adjMatrix[i][j] = adjMatrix[j][i] = 2;
            } else if (songs[i].getAlbum() == songs[j].getAlbum()) {
                adjMatrix[i][j] = adjMatrix[j][i] = 3;
            } else if (songs[i].getLanguage() == songs[j].getLanguage()) {
                adjMatrix[i][j] = adjMatrix[j][i] = 4;
            }
        }
    }

    return adjMatrix;
}

// Print the adjacency matrix
void printAdjacencyMatrix(const std::vector<std::vector<int>>& adjMatrix) {
    for (const auto& row : adjMatrix) {
        for (int weight : row) {
            std::cout << weight << " ";
        }
        std::cout << std::endl;
    }
}

//std::vector<Song> songs; // Storing all existing songs

vector<Song> SongRecommender(vector<vector<int>> adjMatrix, vector<int> sv){
    int n = adjMatrix.size();
    std::vector<bool> visited(n, false);
    std::queue<int> q;
    vector<Song> s;
    for(int i=0; i<sv.size(); i++){
        visited[sv[i]] = true;
        q.push(sv[i]);

        while (!q.empty() && s.size() < (i+1)*5) {
            int vertex = q.front();
            q.pop();

            for (int edgeWeight = 1; edgeWeight < 5 && s.size() < (i+1)*5; ++edgeWeight) {
                int enqueuedCount = 0;
                for (int i = 0; i < n; ++i) {
                    if (adjMatrix[vertex][i] == edgeWeight && !visited[i] && enqueuedCount < 2) {
                        visited[i] = true;
                        q.push(i);
                        s.push_back(songs[i]);
                        enqueuedCount++;
                    }
                }
            }
        }
    }
    return s;
}

int reccommand() {
    loadSongs(songs);

    vector<vector<int>> adjMatrix = createAdjacencyMatrix(songs);
    vector <int> v({1,1});
    recommandedSongs = SongRecommender(adjMatrix, v);
    std::cout << "Recommended Songs:" << std::endl;
    /*for (const auto& song : s) {
        std::cout << song.getName() << " by " << song.getArtist() << std::endl;
    }

    cout << "\n" << songs[33].getName() << adjMatrix[0][33];*/
    return 0;
}

void show(vector<Song> RSongs) {
    for(auto i : RSongs) {
        cout << i.getName() << endl;
    }
    cout << endl;
}



#endif // JAIREC_H_INCLUDED
