#ifndef SEARCHSONG_H_INCLUDED
#define SEARCHSONG_H_INCLUDED

#include <bits/stdc++.h>
#include "songPage.h"

using namespace std;


class AVLsongNode {
public:
    tuple<string, string, string, string, string> key;
    Song data;
    AVLsongNode* left;
    AVLsongNode* right;
    int height;

    AVLsongNode(tuple<string, string, string, string, string> k, Song d)
        : key(k), data(d), left(nullptr), right(nullptr), height(1) {}
};

class AVLsongTree {
public:
    AVLsongTree() : root(nullptr) {}

    void insert(const Song& song) {
        auto key = make_tuple(song.getName(), song.getArtist(), song.getLanguage(), song.getGenre(), song.getAlbum());
        root = insert(root, key, song);
    }

    vector<Song> search(const string& attribute, const string& value) {
        vector<Song> results;
        search(root, attribute, value, results);
        return results;
    }

private:
    AVLsongNode* root;

    int height(AVLsongNode* node) {
        return node ? node->height : 0;
    }

    int balanceFactor(AVLsongNode* node) {
        return node ? height(node->left) - height(node->right) : 0;
    }

    void updateHeight(AVLsongNode* node) {
        if (node) {
            node->height = 1 + max(height(node->left), height(node->right));
        }
    }

    AVLsongNode* rotateRight(AVLsongNode* y) {
        AVLsongNode* x = y->left;
        AVLsongNode* T2 = x->right;
        x->right = y;
        y->left = T2;
        updateHeight(y);
        updateHeight(x);
        return x;
    }

    AVLsongNode* rotateLeft(AVLsongNode* x) {
        AVLsongNode* y = x->right;
        AVLsongNode* T2 = y->left;
        y->left = x;
        x->right = T2;
        updateHeight(x);
        updateHeight(y);
        return y;
    }

    AVLsongNode* balance(AVLsongNode* node) {
        if (!node) return nullptr;

        updateHeight(node);
        int bf = balanceFactor(node);

        if (bf > 1) {
            if (balanceFactor(node->left) < 0) {
                node->left = rotateLeft(node->left);
            }
            return rotateRight(node);
        }
        if (bf < -1) {
            if (balanceFactor(node->right) > 0) {
                node->right = rotateRight(node->right);
            }
            return rotateLeft(node);
        }
        return node;
    }

    AVLsongNode* insert(AVLsongNode* node, tuple<string, string, string, string, string> key, const Song& data) {
        if (!node) {
            return new AVLsongNode(key, data);
        }
        if (key < node->key) {
            node->left = insert(node->left, key, data);
        } else {
            node->right = insert(node->right, key, data);
        }
        return balance(node);
    }

    void search(AVLsongNode* node, const string& attribute, const string& value, vector<Song>& results) {
        if (!node) return;
        if ((attribute == "name" && get<0>(node->key) == value) ||
            (attribute == "artist" && get<1>(node->key) == value) ||
            (attribute == "language" && get<2>(node->key) == value) ||
            (attribute == "genre" && get<3>(node->key) == value) ||
            (attribute == "album" && get<4>(node->key) == value)) {
            results.push_back(node->data);
        }
        search(node->left, attribute, value, results);
        search(node->right, attribute, value, results);
    }
};

vector<Song> searchSong() {
    AVLsongTree AVL;

    vector<Song> songs;
    // Assuming you have a loadSongs function to load songs into the vector
    loadSongs(songs);

    for (const auto& song : songs) {
        AVL.insert(song);
    }

    int choice;
    string value;
    string attribute;

    cout << "Search by: " << endl;
    cout << "1. Name" << endl;
    cout << "2. Artist" << endl;
    cout << "3. Language" << endl;
    cout << "4. Genre" << endl;
    cout << "5. Album" << endl;
    cout << "Enter your choice: ";
    cin >> choice;
    cin.ignore(); // Ignore newline character after the choice input

    switch (choice) {
        case 1:
            attribute = "name";
            cout << "Enter Name: ";
            break;
        case 2:
            attribute = "artist";
            cout << "Enter Artist: ";
            break;
        case 3:
            attribute = "language";
            cout << "Enter Language: ";
            break;
        case 4:
            attribute = "genre";
            cout << "Enter Genre: ";
            break;
        case 5:
            attribute = "album";
            cout << "Enter Album: ";
            break;
        default:
            cout << "Invalid choice" << endl;
            return {};
    }

    getline(cin, value);

    // Searching for songs
    vector<Song> results = AVL.search(attribute, value);
    if (!results.empty()) {
        for (const Song& song : results) {
            cout << "Song found: " << song.getName() << " by " << song.getArtist() << ", Duration: " << song.getDuration()
                 << ", Language: " << song.getLanguage() << ", Genre: " << song.getGenre() << ", Album: " << song.getAlbum() << endl;
        }
    } else {
        cout << "No songs found" << endl;
    }
    return results;
}

#endif // SEARCHSONG_H_INCLUDED

