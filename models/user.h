#pragma once

#include <string>
#include <iostream>
using namespace std;

// User Model Class
class User {
private:
    int id;
    string name;
    string email;

public:
    User(int userId, const string& userName, const string& userEmail);
    
    // Getters
    int getId() const;
    string getName() const;
    string getEmail() const;
    
    // Setters
    void setName(const string& newName);
    void setEmail(const string& newEmail);
    
    // Display function
    void displayUser() const;
};
