#include <iostream>
#include <string>
#include <limits>
#include "apps/AddressBookApp.h"
#include "apps/BrowserHistoryApp.h"
#include "apps/PatientTriageApp.h"
#include "apps/ArrayFlipperApp.h"

using namespace std;

void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int main() {
    while (true) {
        cout << "\n=== CS214 Data Structures Suite ===\n";
        cout << "1. Address Book (AVL Tree)\n";
        cout << "2. Browser History Manager (Stack)\n";
        cout << "3. Patient Priority Queue (Max Heap)\n";
        cout << "4. Binary Array Flipper (Dynamic Array)\n";
        cout << "5. Exit\n";
        cout << "Choose an application (1-5): ";
        
        int choice;
        if (!(cin >> choice)) {
            clearInput();
            cout << "Invalid input. Please try again.\n";
            continue;
        }

        if (choice == 5) {
            cout << "Exiting suite...\n";
            break;
        }

        if (choice < 1 || choice > 4) {
            cout << "Invalid choice.\n";
            continue;
        }

        while (true) {
            string filename;
            cout << "Enter test file name (without .txt) or 'q' to go back: ";
            cin >> filename;
            
            if (filename == "q") break;
            
            filename += ".txt";
            
            switch (choice) {
                case 1: { AddressBookApp app; app.run(filename); break; }
                case 2: { BrowserHistoryApp app; app.run(filename); break; }
                case 3: { PatientTriageApp app; app.run(filename); break; }
                case 4: { ArrayFlipperApp app; app.run(filename); break; }
            }

            cout << "\nDo you want to test another file? (1) Yes / (2) No: ";
            int cont;
            if (!(cin >> cont) || cont == 2) {
                clearInput();
                break;
            }
        }
    }
    return 0;
}
