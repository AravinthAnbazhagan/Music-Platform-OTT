#ifndef SEARCHPODCAST_H_INCLUDED
#define SEARCHPODCAST_H_INCLUDED


/*
// Node class for AVL tree
template<typename T>
class Node {
public:
    T data;
    Node *left;
    Node *right;
    int height;

    Node(T data) : data(data), left(nullptr), right(nullptr), height(1) {}
};



// AVL tree class
template<typename T>
class AVLTree {
private:
    Node<T> *root;

    int height(Node<T> *N) {
        if (N == nullptr)
            return 0;
        return N->height;
    }

    int max(int a, int b) {
        return (a > b) ? a : b;
    }

    Node<T> *rightRotate(Node<T> *y) {
        Node<T> *x = y->left;
        Node<T> *T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = max(height(y->left), height(y->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;

        return x;
    }

    Node<T> *leftRotate(Node<T> *x) {
        Node<T> *y = x->right;
        Node<T> *T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = max(height(x->left), height(x->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;

        return y;
    }

    int getBalance(Node<T> *N) {
        if (N == nullptr)
            return 0;
        return height(N->left) - height(N->right);
    }

    Node<T> *insert(Node<T> *node, T key) {
        if (node == nullptr)
            return (new Node<T>(key));

        if (key.getName() < node->data.getName())
            node->left = insert(node->left, key);
        else if (key.getName() > node->data.getName())
            node->right = insert(node->right, key);
        else
            return node;

        node->height = 1 + max(height(node->left), height(node->right));

        int balance = getBalance(node);

        if (balance > 1 && key.getName() < node->data.getName())
            return rightRotate(node);

        if (balance < -1 && key.getName() > node->data.getName())
            return leftRotate(node);

        if (balance > 1 && key.getName() > node->left->data.getName()) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        if (balance < -1 && key.getName() < node->right->data.getName()) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    Node<T> *minValueNode(Node<T> *node) {
        Node<T> *current = node;
        while (current->left != nullptr)
            current = current->left;
        return current;
    }

    Node<T> *deleteNode(Node<T> *root, string key) {
        if (root == nullptr)
            return root;

        if (key < root->data.getName())
            root->left = deleteNode(root->left, key);
        else if (key > root->data.getName())
            root->right = deleteNode(root->right, key);
        else {
            if ((root->left == nullptr) || (root->right == nullptr)) {
                Node<T> *temp = root->left ? root->left : root->right;

                if (temp == nullptr) {
                    temp = root;
                    root = nullptr;
                } else
                    *root = *temp;

                delete temp;
            } else {
                Node<T> *temp = minValueNode(root->right);
                root->data = temp->data;
                root->right = deleteNode(root->right, temp->data.getName());
            }
        }

        if (root == nullptr)
            return root;

        root->height = 1 + max(height(root->left), height(root->right));

        int balance = getBalance(root);

        if (balance > 1 && getBalance(root->left) >= 0)
            return rightRotate(root);

        if (balance > 1 && getBalance(root->left) < 0) {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }

        if (balance < -1 && getBalance(root->right) <= 0)
            return leftRotate(root);

        if (balance < -1 && getBalance(root->right) > 0) {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }

        return root;
    }

    void preOrder(Node<T> *root) {
        if (root != nullptr) {
            root->data.display();
            preOrder(root->left);
            preOrder(root->right);
        }
    }

    Node<T> *search(Node<T> *root, string key) {
        if (root == nullptr || root->data.getName() == key)
            return root;

        if (root->data.getName() < key)
            return search(root->right, key);

        return search(root->left, key);
    }

public:
    AVLTree() : root(nullptr) {}

    void insert(T key) {
        root = insert(root, key);
    }

    void deleteNode(string key) {
        root = deleteNode(root, key);
    }

    void preOrder() {
        preOrder(root);
    }

    T *search(string key) {
        Node<T> *result = search(root, key);
        if (result != nullptr) {
            return &(result->data);
        } else {
            return nullptr;
        }
    }
};

// Global AVL tree to store podcasts
AVLTree<Podcast> podcastTree;

void buildPodcastTree() {
    podcastTree = AVLTree<Podcast>();
    for (const auto &podcast : podcasts) {
        podcastTree.insert(podcast);
    }
}
*/
/*
void searchPodcast() {
    string name;
    cout << "Enter the name of the podcast to search: ";
    cin.ignore();
    getline(cin, name);

    Podcast *result = podcastTree.search(name);

    if (result) {
        result->display();
    } else {
        cout << "Podcast not found." << endl;
    }
}*/


#endif // SEARCHPODCAST_H_INCLUDED
