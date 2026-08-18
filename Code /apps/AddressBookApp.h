#ifndef ADDRESSBOOKAPP_H
#define ADDRESSBOOKAPP_H

#include "../core/AVLTree.h"
#include "../models/Contact.h"
#include <iostream>
#include <fstream>
#include <sstream>

class AddressBookApp {
    AVLTree<int, Contact> tree;
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
                int id;
                std::string name, phone, email;
                if (iss >> id >> name >> phone >> email) {
                    if (tree.insert(id, Contact(name, phone, email))) {
                        std::cout << "Contact added successfully.\n";
                    } else {
                        std::cout << "Error: Contact with ID " << id << " already exists\n";
                    }
                }
            } else if (choice == 2) {
                int id;
                if (iss >> id) {
                    const Contact* c = tree.search(id);
                    if (c) {
                        std::cout << "\nContact found:\nID: " << id << "\nName: " << c->name
                                  << "\nPhone: " << c->phone << "\nEmail: " << c->email << "\n\n";
                    } else {
                        std::cout << "Contact not found.\n";
                    }
                }
            } else if (choice == 3) {
                if (tree.isEmpty()) {
                    std::cout << "Address Book is empty.\n";
                } else {
                    std::cout << "Contacts in Address Book (sorted by ID):\n";
                    tree.inorder([](const int& id, const Contact& c) {
                        std::cout << "ID: " << id << ", Name: " << c.name
                                  << ", Phone: " << c.phone << ", Email: " << c.email << "\n";
                    });
                    std::cout << "\n";
                }
            } else if (choice == 4) {
                std::cout << "Current tree structure:\n";
                tree.displayTreeStructure();
            } else if (choice == 5) {
                std::cout << "Exiting the file...\n";
                break;
            } else {
                std::cout << "Invalid choice found in the file.\n";
            }
        }
    }
};
#endif
