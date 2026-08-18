#ifndef AVLTREE_H
#define AVLTREE_H

#include <iostream>
#include <string>
#include <functional>

/**
 * @file AVLTree.h
 * @brief Generic AVL Tree data structure
 * 
 * Reusable template-based AVL Tree implementation. Replaces the hardcoded
 * AddressBook AVL tree found in AddressBookAVL.cpp.
 */

template <typename Key, typename Value>
class AVLTree {
public:
    struct Node {
        Key key;
        Value value;
        Node* left;
        Node* right;
        Node(const Key& k, const Value& v) : key(k), value(v), left(nullptr), right(nullptr) {}
    };

private:
    Node* root;

    int getHeight(Node* node) const {
        if (node == nullptr) return 0;
        int left = getHeight(node->left);
        int right = getHeight(node->right);
        return (left > right ? left + 1 : right + 1);
    }

    int getBalanceFactor(Node* node) const {
        if (node == nullptr) return 0;
        return getHeight(node->left) - getHeight(node->right);
    }

    Node* rotateLeft(Node* node) {
        if (node == nullptr) return nullptr;
        Node* child = node->right;
        Node* temp = child->left;
        child->left = node;
        node->right = temp;
        return child;
    }

    Node* rotateRight(Node* node) {
        if (node == nullptr) return nullptr;
        Node* child = node->left;
        Node* temp = child->right;
        child->right = node;
        node->left = temp;
        return child;
    }

    Node* insert(Node* node, const Key& key, const Value& value, bool& inserted) {
        if (node == nullptr) {
            inserted = true;
            return new Node(key, value);
        }
        
        if (key < node->key) {
            node->left = insert(node->left, key, value, inserted);
        } else if (node->key < key) {
            node->right = insert(node->right, key, value, inserted);
        } else {
            inserted = false; // Duplicate key
            return node;
        }

        int factor = getBalanceFactor(node);

        // Right-Right
        if (factor < -1 && node->right && (node->right->key < key))
            return rotateLeft(node);
        // Left-Left
        if (factor > 1 && node->left && (key < node->left->key))
            return rotateRight(node);
        // Left-Right
        if (factor > 1 && node->left && (node->left->key < key)) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        // Right-Left
        if (factor < -1 && node->right && (key < node->right->key)) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
        return node;
    }

    Node* search(Node* node, const Key& key) const {
        if (node == nullptr) return nullptr;
        if (node->key == key) return node;
        if (key < node->key) return search(node->left, key);
        return search(node->right, key);
    }

    void deleteAllNodes(Node* node) {
        if (node == nullptr) return;
        deleteAllNodes(node->left);
        deleteAllNodes(node->right);
        delete node;
    }

    void inorderTraversal(Node* node, const std::function<void(const Key&, const Value&)>& callback) const {
        if (node != nullptr) {
            inorderTraversal(node->left, callback);
            callback(node->key, node->value);
            inorderTraversal(node->right, callback);
        }
    }

    void printLevel(Node* node, int level) const {
        if (node == nullptr) return;
        if (level == 1)
            std::cout << node->key << "   ";
        else if (level > 1) {
            std::cout << " ";
            printLevel(node->left, level - 1);
            printLevel(node->right, level - 1);
        }
    }

    void printBranches(Node* node, int level) const {
        if (node == nullptr) return;
        if (level == 1) {
            if (node->left && node->right) std::cout << "/  \\ "; 
            else if (node->left)  std::cout << "/    "; 
            else if (node->right) std::cout << "   \\ "; 
            else  std::cout << "     "; 
        } else if (level > 1) {
            std::cout << " ";
            printBranches(node->left, level - 1);
            printBranches(node->right, level - 1);
        }
    }

public:
    AVLTree() : root(nullptr) {}

    bool insert(const Key& key, const Value& value) {
        bool inserted = false;
        root = insert(root, key, value, inserted);
        return inserted;
    }

    const Value* search(const Key& key) const {
        Node* result = search(root, key);
        if (result) return &(result->value);
        return nullptr;
    }

    void inorder(const std::function<void(const Key&, const Value&)>& callback) const {
        inorderTraversal(root, callback);
    }
    
    bool isEmpty() const {
        return root == nullptr;
    }

    void displayTreeStructure() const {
        if(root == nullptr) {
            std::cout << "The tree is empty.\n";
            return;
        }
        int height = getHeight(root);
        for (int i = 1; i <= height; i++) {
            std::cout << std::string(((height - i + 1) * 4) + 1, ' ');
            printLevel(root, i);
            std::cout << "\n";
            if (i < height) {
                std::cout << std::string(((height - i + 1) * 4), ' ');
                printBranches(root, i);
                std::cout << "\n";
            }
        }
    }

    ~AVLTree() {
        deleteAllNodes(root);
    }
};

#endif // AVLTREE_H
