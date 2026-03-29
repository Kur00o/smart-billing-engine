#include <iostream>
#include <string>
using namespace std;

class AddOn {
private:
    string name;
    double price;

public:
    AddOn(string n, double p) {
        name = n;
        price = p;
    }

    string getName() {
        return name;
    }

    double getPrice() {
        return price;
    }

    void display() {
        cout << name << " - $" << price << endl;
    }
};

// Factory
class AddOnFactory {
public:
    static AddOn createAnalytics() {
        return AddOn("Analytics", 19);
    }

    static AddOn createBackup() {
        return AddOn("Backup", 9);
    }

    static AddOn createPrioritySupport() {
        return AddOn("Priority Support", 29);
    }
};