#include <iostream>
#include <string>
using namespace std;

class User {
private:
    int id;
    string name;
    string email;

public:
    User(int id, string name, string email) {
        this->id = id;
        this->name = name;
        this->email = email;
    }

    void display() {
        cout << "ID: " << id
             << ", Name: " << name
             << ", Email: " << email << endl;
    }
};