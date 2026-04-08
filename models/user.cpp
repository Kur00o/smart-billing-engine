#include "user.h"

// Constructor
User::User(int userId, const string& userName, const string& userEmail)
    : id(userId), name(userName), email(userEmail) {
}

// Getters
int User::getId() const {
    return id;
}

string User::getName() const {
    return name;
}

string User::getEmail() const {
    return email;
}

// Setters
void User::setName(const string& newName) {
    name = newName;
}

void User::setEmail(const string& newEmail) {
    email = newEmail;
}

// Display function
void User::displayUser() const {
    cout << "\n========== User Information ==========" << endl;
    cout << "ID: " << id << endl;
    cout << "Name: " << name << endl;
    cout << "Email: " << email << endl;
    cout << "=====================================\n" << endl;
}