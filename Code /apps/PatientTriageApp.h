#ifndef PATIENTTRIAGEAPP_H
#define PATIENTTRIAGEAPP_H

#include "../core/MaxHeap.h"
#include "../models/Patient.h"
#include <iostream>
#include <fstream>
#include <sstream>

class PatientTriageApp {
public:
    void run(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Error: Could not open the file " << filename << ".\n";
            return;
        }

        MaxHeap<Patient> heap;
        std::string name;
        int severity = 0;
        int arrivalTime = 0;
        
        std::string line;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            if (!(iss >> name >> severity)) continue;
            if (name.length() < 3 || severity < 0 || severity > 100) continue;

            heap.insert(Patient(name, severity, ++arrivalTime));
            std::cout << "Inserting : " << name << "\nHeap [";
            
            const Patient* arr = heap.getArray();
            int sz = heap.getSize();
            for (int i = 0; i < sz; i++) {
                std::cout << "'" << arr[i].name << "'";
                if (i != sz - 1) std::cout << ", ";
            }
            std::cout << "]\n\n";
        }

        std::cout << "\n\n";
        while (!heap.isEmpty()) {
            Patient p = heap.extract_max();
            std::cout << "Treating : " << p.name << "\n";
        }
        std::cout << "\n\nAll patients has been treated successfully \n";
    }
};
#endif
