#include <iostream>
#include <vector>
using namespace std;

#include "policies/discount_policy.cpp"
#include "policies/tax_calc.cpp"
#include "policies/addon.cpp"
#include "policies/billing_policies.cpp"

int main() {

    double baseAmount = 1000;

    cout << "Base Amount: " << baseAmount << endl;

    // Discount test
    PercentageDiscount discount(10);
    double discounted = discount.applyDiscount(baseAmount);
    cout << "After Discount: " << discounted << endl;

    // Tax test
    GSTCalculator tax;
    double taxAmount = tax.calculateTax(discounted);
    cout << "Tax: " << taxAmount << endl;

    // Add-ons test
    vector<AddOn> addons;
    addons.push_back(AddOnFactory::createAnalytics());
    addons.push_back(AddOnFactory::createBackup());

    double addonTotal = applyAllAddOns(addons);
    cout << "Add-On Total: " << addonTotal << endl;

    // Final
    double finalBill = discounted + taxAmount + addonTotal;
    cout << "Final Bill: " << finalBill << endl;

    return 0;
}