// Specification file for the IntBinaryTree class
#ifndef INTBINARYTREE_H
#define INTBINARYTREE_H

#include <iostream>
#include <string>

class StringBinaryTree { // Forward declaration
   private:
      struct TreeNode {
         std::string value;
         TreeNode *left;
         TreeNode *right;
      };

      TreeNode *root;

      void insert(TreeNode *&nodePtr, TreeNode *&newNode) {
        if (!nodePtr) {
            nodePtr = newNode;
        } else if (newNode->value < nodePtr->value) {
            insert(nodePtr->left, newNode);
        } else if (newNode->value > nodePtr->value) {
            insert(nodePtr->right, newNode);
        } else {
            // Duplicate - do not insert. Caller created newNode, clean up.
            delete newNode;
            newNode = nullptr;
        }
    }
    
    void deleteNode(const std::string &val, TreeNode *&nodePtr) {
        if (!nodePtr) return; // not found
        if (val < nodePtr->value)
            deleteNode(val, nodePtr->left);
        else if (val > nodePtr->value)
            deleteNode(val, nodePtr->right);
        else
            makeDeletion(nodePtr);
    }

    void makeDeletion(TreeNode *&nodePtr) {
        TreeNode *tempNodePtr;

        if (!nodePtr) {
            std::cout << "Cannot delete empty node.\n";
        } else if (!nodePtr->right) {
            tempNodePtr = nodePtr;
            nodePtr = nodePtr->left;
            delete tempNodePtr;
        } else if (!nodePtr->left) {
            tempNodePtr = nodePtr;
            nodePtr = nodePtr->right;
            delete tempNodePtr;
        } else {
            // Two children: find smallest in right subtree
            tempNodePtr = nodePtr->right;
            while (tempNodePtr->left)
                tempNodePtr = tempNodePtr->left;
            // attach left subtree
            tempNodePtr->left = nodePtr->left;
            // move root right up
            tempNodePtr = nodePtr;
            nodePtr = nodePtr->right;
            delete tempNodePtr;
        }
    }
    
    bool search(TreeNode *nodePtr, const std::string &val) const {
        while (nodePtr) {
            if (nodePtr->value == val)
                return true;
            else if (val < nodePtr->value)
                nodePtr = nodePtr->left;
            else
                nodePtr = nodePtr->right;
        }
        return false;
    }

    void destroySubTree(TreeNode *nodePtr) {
        if (nodePtr) {
            if (nodePtr->left)
                destroySubTree(nodePtr->left);
            if (nodePtr->right)
                destroySubTree(nodePtr->right);
            delete nodePtr;
        }
    }

    void displayPreOrder(TreeNode *nodePtr) const {
        if (nodePtr) {
            std::cout << nodePtr->value << '\n';
            displayPreOrder(nodePtr->left);
            displayPreOrder(nodePtr->right);
        }
    }

    void displayPostOrder(TreeNode *nodePtr) const {
        if (nodePtr) {
            displayPostOrder(nodePtr->left);
            displayPostOrder(nodePtr->right);
            std::cout << nodePtr->value << '\n';
        }
    }

    void displayInOrder(TreeNode *nodePtr) const {
        if (nodePtr) {
            displayInOrder(nodePtr->left);
            std::cout << nodePtr->value << '\n';
            displayInOrder(nodePtr->right);
        }
    }


    public:
    StringBinaryTree() : root(nullptr) {}
      ~StringBinaryTree() { destroySubTree(root); }
      void insertNode(const std::string &val) {
        TreeNode *newNode = new TreeNode;
        newNode->value = val;
        newNode->left = newNode->right = nullptr;
        insert(root, newNode);
      }

      bool searchNode(const std::string &val) const {
        return search(root, val);
      }
      
      void remove(const std::string &val) {
        deleteNode(val, root);
      }

      void displayInOrder() const { displayInOrder(root); }
      void displayPreOrder() const { displayPreOrder(root); }
      void displayPostOrder() const { displayPostOrder(root); }
      
};

#endif // INTBINARYTREE_H
