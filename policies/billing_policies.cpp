#include <vector>
#include <iostream>
using namespace std;

// Forward declaration
class AddOn;

// Function to calculate total add-on cost
double applyAllAddOns(vector<AddOn>& addons) {
    double total = 0;

    for (auto &a : addons) {
        total += a.getPrice();
    }

    return total;
}