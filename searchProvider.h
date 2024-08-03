#ifndef SEARCHPROVIDER_H_INCLUDED
#define SEARCHPROVIDER_H_INCLUDED

#include <bits/stdc++.h>

using namespace std;

struct AVLProviderNode {
    Provider data;
    AVLProviderNode* left;
    AVLProviderNode* right;
    int height;

    AVLProviderNode(const Provider& p)
        : data(p), left(nullptr), right(nullptr), height(1) {}
};

class AVLProviderTree {
private:
    AVLProviderNode* root;

    int height(AVLProviderNode* node) {
        return node ? node->height : 0;
    }

    int getBalance(AVLProviderNode* node) {
        return node ? height(node->left) - height(node->right) : 0;
    }

    AVLProviderNode* rightRotate(AVLProviderNode* y) {
        AVLProviderNode* x = y->left;
        AVLProviderNode* T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = max(height(y->left), height(y->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;

        return x;
    }

    AVLProviderNode* leftRotate(AVLProviderNode* x) {
        AVLProviderNode* y = x->right;
        AVLProviderNode* T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = max(height(x->left), height(x->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;

        return y;
    }

    AVLProviderNode* insert(AVLProviderNode* node, const Provider& data) {
        if (!node) return new AVLProviderNode(data);

        if (data.getUsername() < node->data.getUsername())
            node->left = insert(node->left, data);
        else if (data.getUsername() > node->data.getUsername())
            node->right = insert(node->right, data);
        else
            return node;

        node->height = 1 + max(height(node->left), height(node->right));

        int balance = getBalance(node);

        if (balance > 1 && data.getUsername() < node->left->data.getUsername())
            return rightRotate(node);

        if (balance < -1 && data.getUsername() > node->right->data.getUsername())
            return leftRotate(node);

        if (balance > 1 && data.getUsername() > node->left->data.getUsername()) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        if (balance < -1 && data.getUsername() < node->right->data.getUsername()) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    AVLProviderNode* find(AVLProviderNode* node, const string& username) const {
        if (!node) return nullptr;

        if (username == node->data.getUsername())
            return node;

        if (username < node->data.getUsername())
            return find(node->left, username);

        return find(node->right, username);
    }

public:
    AVLProviderTree() : root(nullptr) {}

    void insert(const Provider& data) {
        root = insert(root, data);
    }

    Provider* find(const string& username) const {
        AVLProviderNode* node = find(root, username);
        return node ? &node->data : nullptr;
    }
};

#endif // SEARCHPROVIDER_H_INCLUDED
