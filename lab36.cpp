// comsc 210 | lab33 | Christian Molina
#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include "IntBinaryTree.h"

using namespace std;

void LoadFromFile(const string &filename, StringBinaryTree &tree) {// Load strings from a file into the binary tree
    ifstream fin(filename);
    if (!fin) {
        cerr << "Could not open " << filename << " for reading.\n";
        return;
    }

    string line;
    size_t inserted = 0;
    while (getline(fin, line)) {
        // Trim trailing/leading spaces (basic)
        if (line.size() == 0) continue;
        // Optionally ignore lines that are only whitespace
        bool allspace = true;
        for (char c : line) if (!isspace(static_cast<unsigned char>(c))) { allspace = false; break; }
        if (allspace) continue;

        // Insert as-is (preserve case & characters)
        if (!tree.searchNode(line)) {
            tree.insertNode(line);
            inserted++;
        }
    }
    cout << "Loaded " << inserted << " codes from " << filename << ".\n";
    fin.close();
}

void waitEnter() {
    cout << "Press Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int main(){
    StringBinaryTree tree;
    const string filename = "codes.txt";
    cout << "Loading codes from " << filename << "...\n";
    LoadFromFile(filename, tree);


    while (true) {
        cout << "\nMenu:\n";
        cout << " 1) Display tree (in-order)\n";
        cout << " 2) Add code\n";
        cout << " 3) Delete code\n";
        cout << " 4) Search code\n";
        cout << " 5) Modify code (replace existing with new)\n";
        cout << " 6) Exit\n";
        cout << "Enter choice: ";
        int choice;
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid selection. Try again.\n";
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 

        if (choice == 1) {
            cout << "\n---- Tree (in-order) ----\n";
            tree.displayInOrder();
            cout << "---- End ----\n";
            // waitEnter(); // optional
        } else if (choice == 2) {
            cout << "Enter code to add: ";
            string code;
            getline(cin, code);
            if (code.empty()) { cout << "Empty input. Aborting.\n"; continue; }
            if (tree.searchNode(code)) {
                cout << "Code already exists in the tree.\n";
            } else {
                tree.insertNode(code);
                cout << "Inserted: " << code << '\n';
            }     
        }
        else if (choice == 3) {
            cout << "Enter code to delete: ";
            string code;
            getline(cin, code);
            if (code.empty()) { cout << "Empty input. Aborting.\n"; continue; }
            if (tree.searchNode(code)) {
                tree.remove(code);
                cout << "Deleted: " << code << '\n';
            } else {
                cout << "Code not found: " << code << '\n';
            }
        } else if (choice == 4) {
            cout << "Enter code to search: ";
            string code;
            getline(cin, code);
            if (code.empty()) { cout << "Empty input. Aborting.\n"; continue; }
            bool found = tree.searchNode(code);
            cout << (found ? "Found: " : "Not found: ") << code << '\n';
        } else if (choice == 5) {
            cout << "Enter code to modify (existing): ";
            string oldCode;
            getline(cin, oldCode);
            if (oldCode.empty()) { cout << "Empty input. Aborting.\n"; continue; }
            if (!tree.searchNode(oldCode)) {
                cout << "Code not found: " << oldCode << '\n';
                continue;
            }
            cout << "Enter new code to replace with: ";
            string newCode;
            getline(cin, newCode);
            if (newCode.empty()) { cout << "Empty input. Aborting.\n"; continue; }
            // If newCode already exists, reject to avoid duplicates.
            if (tree.searchNode(newCode)) {
                cout << "New code already exists in tree. Cannot modify to duplicate.\n";
                continue;
            }
            // Remove old and insert new
            tree.remove(oldCode);
            tree.insertNode(newCode);
            cout << "Replaced \"" << oldCode << "\" with \"" << newCode << "\".\n";
    
        } else if (choice == 6) {
            cout << "Exiting.\n";
            break;
        } else {
            cout << "Invalid choice. Try again.\n";
        }
    }
    return 0;
}