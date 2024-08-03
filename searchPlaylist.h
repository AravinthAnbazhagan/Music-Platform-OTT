#ifndef SEARCHPLAYLIST_H_INCLUDED
#define SEARCHPLAYLIST_H_INCLUDED

#include "playlistPage.h"

#endif // SEARCHPLAYLIST_H_INCLUDED

class AVLPlaylistNode {
public:
    Playlist playlist;
    AVLPlaylistNode* left;
    AVLPlaylistNode* right;
    int height;

    AVLPlaylistNode(const Playlist& p)
        : playlist(p), left(nullptr), right(nullptr), height(1) {}
};

class AVLPlaylistTree {
private:
    AVLPlaylistNode* root;

    int height(AVLPlaylistNode* node) {
        return node ? node->height : 0;
    }

    int balanceFactor(AVLPlaylistNode* node) {
        return node ? height(node->left) - height(node->right) : 0;
    }

    void updateHeight(AVLPlaylistNode* node) {
        if (node) {
            node->height = 1 + max(height(node->left), height(node->right));
        }
    }

    AVLPlaylistNode* rotateRight(AVLPlaylistNode* y) {
        AVLPlaylistNode* x = y->left;
        AVLPlaylistNode* T2 = x->right;

        x->right = y;
        y->left = T2;

        updateHeight(y);
        updateHeight(x);

        return x;
    }

    AVLPlaylistNode* rotateLeft(AVLPlaylistNode* x) {
        AVLPlaylistNode* y = x->right;
        AVLPlaylistNode* T2 = y->left;

        y->left = x;
        x->right = T2;

        updateHeight(x);
        updateHeight(y);

        return y;
    }

    AVLPlaylistNode* balance(AVLPlaylistNode* node) {
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

    AVLPlaylistNode* insert(AVLPlaylistNode* node, const Playlist& playlist) {
        if (!node) {
            return new AVLPlaylistNode(playlist);
        }

        if (playlist.getName() < node->playlist.getName()) {
            node->left = insert(node->left, playlist);
        } else if (playlist.getName() > node->playlist.getName()) {
            node->right = insert(node->right, playlist);
        } else {
            return node; // Avoid duplicate playlists
        }

        return balance(node);
    }

    AVLPlaylistNode* search(AVLPlaylistNode* node, const string& name) const {
        if (!node || node->playlist.getName() == name) {
            return node;
        }

        if (name < node->playlist.getName()) {
            return search(node->left, name);
        } else {
            return search(node->right, name);
        }
    }

public:
    AVLPlaylistTree() : root(nullptr) {}

    void insert(const Playlist& playlist) {
        root = insert(root, playlist);
    }

    Playlist* search(const string& name) const {
        AVLPlaylistNode* result = search(root, name);
        return result ? &result->playlist : nullptr;
    }
};

Playlist* searchPlaylist(string& searchName) {
    AVLPlaylistTree playlistTree;
    for (const Playlist& p : userPlaylists) {
        playlistTree.insert(p);
    }

    // Search for a playlist by name
    /*string searchName;
    cout << "Enter playlist name: ";
    cin.ignore();
    getline(cin, searchName);*/
    Playlist* foundPlaylist = playlistTree.search(searchName);

    return foundPlaylist;
}


/********************************



// Example usage
int main() {
    AVLPlaylistTree avl;

    // Create some playlists
    Playlist p1("Rock Classics");
    Playlist p2("Pop Hits");
    Playlist p3("Jazz Essentials");

    // Insert playlists into the AVL tree
    avl.insert(p1);
    avl.insert(p2);
    avl.insert(p3);

    // Search for a playlist
    string searchName;
    cout << "Enter the name of the playlist to search: ";
    cin >> searchName;

    Playlist* foundPlaylist = avl.search(searchName);
    if (foundPlaylist) {
        cout << "Playlist found: " << foundPlaylist->getName() << endl;
    } else {
        cout << "Playlist not found." << endl;
    }

    return 0;
}

*****************************/
