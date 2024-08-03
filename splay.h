#ifndef SPLAY_H_INCLUDED
#define SPLAY_H_INCLUDED

#include <iostream>
 #include <string>
 using namespace std;
 class Song {
 public:
    int noOfTimesPlayed;
    string title;
    string artist;
    string album;
    int releaseYear;
    string genre;
    int durationInSeconds;
    Song(int played, const string& t, const string& a, const string& al, int year, const string& g, int duration)
        :
 noOfTimesPlayed(played), title(t), artist(a), album(al), releaseYear(year), genre(g),
durationInSeconds(duration) {}
    // Comparison operators to sort by number of times played
    bool operator<(const Song& other) const {
        return noOfTimesPlayed < other.noOfTimesPlayed;
    }
    bool operator>(const Song& other) const {
        return noOfTimesPlayed > other.noOfTimesPlayed;
    }
    bool operator==(const Song& other) const {
        return noOfTimesPlayed == other.noOfTimesPlayed;
    }
 };
 template<typename T>
 struct Node {
 T key;
    Node<T>* left;
    Node<T>* right;
    Node<T>* parent;
 1
};
    Node(const T& item) : key(item), left(nullptr), right(nullptr), parent(nullptr) {}
 template<typename T>
 class SplayTree {
 private:
    Node<T>* root;
    void splay(Node<T>* x) {
        while (x->parent != nullptr) {
            Node<T>* parent = x->parent;
            Node<T>* grandparent = parent->parent;
            if (grandparent == nullptr) {
                if (x == parent->left)
                    rotateRight(parent);
                else
                    rotateLeft(parent);
            }
 else {
                if (parent == grandparent->left) {
                    if (x == parent->left) {
                        rotateRight(grandparent);
                        rotateRight(parent);
                    }
 else {
                        rotateLeft(parent);
                        rotateRight(grandparent);
                    }
                }
                }
            }
 else {
                    if (x == parent->right) {
                        rotateLeft(grandparent);
                        rotateLeft(parent);
                    }
 else {
                        rotateRight(parent);
                        rotateLeft(grandparent);
                    }
        }
        root = x;
    }
    void rotateRight(Node<T>* x) {
        Node<T>* y = x->left;
        x->left = y->right;
        if (y->right != nullptr)
            y->right->parent = x;
        y->parent = x->parent;
        if (x->parent == nullptr)
            root = y;
        else if (x == x->parent->right)
            x->parent->right = y;
        else
            x->parent->left = y;
        y->right = x;
        x->parent = y;
    }
    void rotateLeft(Node<T>* x) {
        Node<T>* y = x->right;
        x->right = y->left;
        if (y->left != nullptr)
            y->left->parent = x;
        y->parent = x->parent;
        if (x->parent == nullptr)
            root = y;
        else if (x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;
        y->left = x;
        x->parent = y;
    }
    Node<T>* insertUtil(Node<T>* root, const T& key) {
        if (root == nullptr)
            return new Node<T>(key);
        if (key < root->key) {
            root->left = insertUtil(root->left, key);
            root->left->parent = root;
        }
 else if (key > root->key) {
            root->right = insertUtil(root->right, key);
            root->right->parent = root;
        }
        return root;
    }
    void inorderUtil(Node<T>* root) {
        if (root != nullptr) {
            inorderUtil(root->left);
            cout << root->key.noOfTimesPlayed << " - " << root->key.title << endl;
            inorderUtil(root->right);
        }
    }
    void preorderUtil(Node<T>* root) {
        if (root != nullptr) {
 3
2022506060
            cout << root->key.noOfTimesPlayed << " - " << root->key.title << endl;
            preorderUtil(root->left);
            preorderUtil(root->right);
        }
    }
    void postorderUtil(Node<T>* root) {
        if (root != nullptr) {
            postorderUtil(root->left);
            postorderUtil(root->right);
            cout << root->key.noOfTimesPlayed << " - " << root->key.title << endl;
        }
    }
    Node<T>* minValueNode(Node<T>* node) {
        Node<T>* current = node;
        while (current && current->left != nullptr)
            current = current->left;
        return current;
    }
    Node<T>* deleteNodeUtil(Node<T>* root, const T& key) {
        if (root == nullptr)
            return root;
        if (key < root->key)
            root->left = deleteNodeUtil(root->left, key);
        else if (key > root->key)
            root->right = deleteNodeUtil(root->right, key);
        else {
            if (root->left == nullptr) {
                Node<T>* temp = root->right;
                delete root;
                return temp;
            }
 else if (root->right == nullptr) {
                Node<T>* temp = root->left;
                delete root;
                return temp;
            }
            Node<T>* temp = minValueNode(root->right);
            root->key = temp->key;
            root->right = deleteNodeUtil(root->right, temp->key);
        }
        return root;
    }
 public:
    SplayTree() : root(nullptr) {}
    void insert(const T& key) {
        root = insertUtil(root, key);
        splay(root);
    }
    void inorder() {
        inorderUtil(root);
    }
    void preorder() {
        preorderUtil(root);
    }
    void postorder() {
        postorderUtil(root);
    }
    Node<T>* search(const T& key) {
        Node<T>* current = root;
        while (current != nullptr) {
            if (key < current->key)
                current = current->left;
            else if (key > current->key)
                current = current->right;
            else {
                splay(current);
                return current;
            }
        }
        return nullptr;
    }
    void deleteNode(const T& key) {
        root = deleteNodeUtil(root, key);
    }
 };
 int main() {
    SplayTree<Song> splayTree;
    Song song1(10, "Title1", "Artist1", "Album1", 2000, "Genre1", 180);
    Song song2(5, "Title2", "Artist2", "Album2", 2005, "Genre2", 200);
    Song song3(15, "Title3", "Artist3", "Album3", 2010, "Genre3", 220);
    Song song4(8, "Title4", "Artist4", "Album4", 2015, "Genre4", 240);
    Song song5(12, "Title5", "Artist5", "Album5", 2020, "Genre5", 260);
 5
2022506060
    Song song6(20, "Title6", "Artist6", "Album6", 2025, "Genre6", 280);
    Song song7(3, "Title7", "Artist7", "Album7", 2030, "Genre7", 300);
    // Insert songs into the Splay Tree
    splayTree.insert(song1);
    splayTree.insert(song2);
    splayTree.insert(song3);
    splayTree.insert(song4);
    splayTree.insert(song5);
    splayTree.insert(song6);
    splayTree.insert(song7);
    int choice;
    do {
        cout << "\nSplay Tree Operations:" << endl;
        cout << "1. Delete a song" << endl;
        cout << "2. Search for a song" << endl;
        cout << "3. In-order traversal" << endl;
        cout << "4. Pre-order traversal" << endl;
        cout << "5. Post-order traversal" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1: {
                int
 played;
                cout << "Enter number of times played of the song to delete: ";
                cin >> played;
                Song temp(played, "", "", "", 0, "", 0);
                Node<Song>* toDelete = splayTree.search(temp);
                if (toDelete) {
                    splayTree.deleteNode(toDelete->key);
                    cout
 << "Song deleted successfully!" << endl;
                }
 else {
                    cout
 << "Song not found!" << endl;
                }
                break;
            }
            case 2: {
                int
 played;
                cout << "Enter number of times played of the song to search: ";
                cin >> played;
                Song temp(played, "", "", "", 0, "", 0);
                Node<Song>* found = splayTree.search(temp);
                if (found)
                    cout
 << "Song found: " << found->key.title << endl;
                else
                    cout
                break;
            }
            case 3: {
 << "Song not found!" << endl;
                cout << "In-order traversal:" << endl;
                splayTree.inorder();
                break;
            }
            case 4: {
                cout << "Pre-order traversal:" << endl;
                splayTree.preorder();
                break;
            }
            case 5: {
                cout << "Post-order traversal:" << endl;
                splayTree.postorder();
                break;
            }
            case 6:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 6);
    return 0;
 }


#endif // SPLAY_H_INCLUDED
