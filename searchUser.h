#ifndef SEARCHUSER_H_INCLUDED
#define SEARCHUSER_H_INCLUDED

template<typename T>
class AVLNode {
public:
    T data;
    shared_ptr<AVLNode<T>> left;
    shared_ptr<AVLNode<T>> right;
    int height;

    AVLNode(const T& value)
        : data(value), left(nullptr), right(nullptr), height(1) {}
};

template<typename T>
class AVLTree {
private:
    shared_ptr<AVLNode<T>> root;

    int height(shared_ptr<AVLNode<T>> node) {
        return node ? node->height : 0;
    }

    int getBalance(shared_ptr<AVLNode<T>> node) {
        return node ? height(node->left) - height(node->right) : 0;
    }

    shared_ptr<AVLNode<T>> rightRotate(shared_ptr<AVLNode<T>> y) {
        auto x = y->left;
        auto T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = max(height(y->left), height(y->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;

        return x;
    }

    shared_ptr<AVLNode<T>> leftRotate(shared_ptr<AVLNode<T>> x) {
        auto y = x->right;
        auto T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = max(height(x->left), height(x->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;

        return y;
    }

    shared_ptr<AVLNode<T>> insert(shared_ptr<AVLNode<T>> node, const T& value) {
        if (!node) return make_shared<AVLNode<T>>(value);

        if (value < node->data) {
            node->left = insert(node->left, value);
        } else if (node->data < value) {
            node->right = insert(node->right, value);
        } else {
            return node;
        }

        node->height = 1 + max(height(node->left), height(node->right));

        int balance = getBalance(node);

        if (balance > 1 && value < node->data)
            return rightRotate(node);

        if (balance < -1 && node->data < value)
            return leftRotate(node);

        if (balance > 1 && !(value < node->data))
            return rightRotate(node);

        if (balance < -1 && !(node->data < value))
            return leftRotate(node);

        return node;
    }

    shared_ptr<AVLNode<T>> search(shared_ptr<AVLNode<T>> node, const T& value) const {
        if (!node || node->data == value) return node;

        if (value < node->data)
            return search(node->left, value);

        return search(node->right, value);
    }

public:
    AVLTree() : root(nullptr) {}

    void insert(const T& value) {
        root = insert(root, value);
    }

    shared_ptr<AVLNode<T>> search(const T& value) const {
        return search(root, value);
    }

    T* searchByUsername(const string& username) const {
        User dummyUser(username, "", "", "", 0, {}, {}, {});
        auto result = search(root, dummyUser);
        return result ? &result->data : nullptr;
    }
};

#endif // SEARCHUSER_H_INCLUDED
