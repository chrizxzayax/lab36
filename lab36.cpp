// comsc 210 | lab33 | Christian Molina
#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include "IntBinaryTree.h"

using namespace std;

void LoadFromFile(const string &filename, StringBinaryTree &tree) {
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