#include "addon.h"
#include <iomanip>

// ============================================================
// AddOn Class Implementation
// ============================================================

AddOn::AddOn(const string& name, double price)
    : addonName(name), monthlyPrice(price) {
}

string AddOn::getName() const {
    return addonName;
}

double AddOn::getPrice() const {
    return monthlyPrice;
}

void AddOn::setPrice(double price) {
    monthlyPrice = price;
}

void AddOn::display() const {
    cout << addonName << " - $" << fixed << setprecision(2) << monthlyPrice << "/month" << endl;
}

// ============================================================
// AddOnFactory Implementation
// ============================================================

AddOn AddOnFactory::createAnalyticsAddOn() {
    return AddOn("Analytics", 10.0);
}

AddOn AddOnFactory::createBackupAddOn() {
    return AddOn("Backup", 15.0);
}

AddOn AddOnFactory::createPrioritySupportAddOn() {
    return AddOn("Priority Support", 20.0);
}

AddOn AddOnFactory::createCustomAddOn(const string& name, double price) {
    return AddOn(name, price);
}

// ============================================================
// Helper Function
// ============================================================

double applyAllAddOns(const vector<AddOn>& addons) {
    double total = 0.0;
    for (const AddOn& addon : addons) {
        total += addon.getPrice();
    }
    return total;
}