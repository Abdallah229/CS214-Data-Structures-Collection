#ifndef BROWSERHISTORYAPP_H
#define BROWSERHISTORYAPP_H

#include "../core/Stack.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

class BrowserHistoryApp {
    Stack<std::string> backStack;
    Stack<std::string> forwardStack;
    std::string currentUrl;

    void printStack(const Stack<std::string>& stack) {
        Stack<std::string> temp = stack; // uses overloaded operator=
        std::cout << "[";
        while (!temp.isEmpty()) {
            std::cout << "\" " << temp.pop() << "\",";
        }
        std::cout << "]\n";
    }

public:
    void run(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Error: Could not open the file " << filename << ".\n";
            return;
        }

        std::string line;
        while (std::getline(file, line)) {
            if (line.empty()) continue;
            std::istringstream iss(line);
            int choice;
            if (!(iss >> choice)) continue;

            if (choice == 1) {
                std::string url;
                if (iss >> url) {
                    currentUrl = url;
                    backStack.push(currentUrl);
                    forwardStack.clear();
                    std::cout << "Visited: " << url << "\n\n";
                }
            } else if (choice == 2) {
                if (backStack.isEmpty()) {
                    std::cout << "No previous URL to go back \n\n";
                } else if (currentUrl.empty()) {
                    std::cout << "No current URL\n";
                } else {
                    std::string previousUrl = backStack.pop();
                    forwardStack.push(previousUrl);
                    currentUrl = backStack.pop();
                    backStack.push(currentUrl);
                    std::cout << "Went back to: " << currentUrl << "\n\n";
                }
            } else if (choice == 3) {
                if (forwardStack.isEmpty()) {
                    std::cout << "No forward URL to go forward\n\n";
                } else if (currentUrl.empty()) {
                    std::cout << "No current URL\n";
                } else {
                    std::string nextUrl = forwardStack.pop();
                    backStack.push(nextUrl);
                    currentUrl = nextUrl;
                    std::cout << "Went forward to: " << currentUrl << "\n\n";
                }
            } else if (choice == 4) {
                std::cout << "Back Stack: "; printStack(backStack);
                std::cout << "Forward Stack: "; printStack(forwardStack);
                std::cout << "Current URL: " << currentUrl << "\n\n";
            } else {
                std::cout << "Invalid choice found in the file \n\n";
            }
        }
    }
};
#endif
