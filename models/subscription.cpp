#include <iostream>
#include <string>
using namespace std;

// Base Abstract Class
class SubscriptionPlan {
protected:
    string planName;
    double basePrice;

public:
    SubscriptionPlan(string name, double price) {
        planName = name;
        basePrice = price;
    }

    virtual double calculateBill(double usageAmount) = 0;

    string getPlanName() {
        return planName;
    }

    virtual void displayPlanDetails() = 0;
};