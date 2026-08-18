#ifndef CONTACT_H
#define CONTACT_H

#include <string>

/**
 * @file Contact.h
 * @brief Domain entity for an Address Book contact.
 */
struct Contact {
    std::string name;
    std::string phone;
    std::string email;

    Contact() : name(""), phone(""), email("") {}
    Contact(const std::string& n, const std::string& p, const std::string& e)
        : name(n), phone(p), email(e) {}
};

#endif
