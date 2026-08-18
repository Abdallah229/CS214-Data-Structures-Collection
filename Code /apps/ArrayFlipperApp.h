#ifndef ARRAYFLIPPERAPP_H
#define ARRAYFLIPPERAPP_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

class ArrayFlipperApp {
public:
    void run(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Error: Could not open the file " << filename << ".\n";
            return;
        }

        std::string line;
        if (!std::getline(file, line)) return;

        // Swapped dynamic array with std::vector for robust modern C++
        std::vector<int> arr;
        std::istringstream iss(line);
        int x;
        while (iss >> x) {
            arr.push_back(x);
        }

        int k;
        if (!(file >> k)) return;

        int cntOfSub = 0;
        bool done = true;
        
        for (size_t i = 0; i < arr.size(); ++i) {
            if (arr[i] == 0) {
                for (int j = 0; j < k; ++j) {
                    if (i + j >= arr.size()) {
                        done = false;
                        break;
                    }
                    arr[i + j] = !arr[i + j];
                }
                if (!done) break;
                cntOfSub++;
            }
        }

        if (!done) {
            std::cout << "-1\n";
        } else {
            std::cout << cntOfSub << "\n";
        }
    }
};
#endif
