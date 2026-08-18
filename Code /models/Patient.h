#ifndef PATIENT_H
#define PATIENT_H

#include <string>

/**
 * @file Patient.h
 * @brief Domain entity for ER Triage Patient.
 */
struct Patient {
    std::string name;
    int severity;
    int arrival_time;

    Patient() : name(""), severity(0), arrival_time(0) {}
    Patient(const std::string& n, int s, int a) : name(n), severity(s), arrival_time(a) {}

    // Operator< is required by MaxHeap
    // Max heap puts the "greatest" element at the top.
    bool operator<(const Patient& other) const {
        if (severity == other.severity) {
            // Lower arrival time should be prioritized, so we say it's "greater" for the max-heap
            return arrival_time > other.arrival_time; 
        }
        return severity < other.severity;
    }
};

#endif
