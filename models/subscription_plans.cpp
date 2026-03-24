#include <iostream>
#include "subscription.cpp"
using namespace std;

//FREE PLAN 
class FreePlan : public SubscriptionPlan {
public:
    FreePlan() : SubscriptionPlan("Free Plan", 0) {}

    double calculateBill(double usageAmount) {
        if (usageAmount <= 1000)
            return 0;

        return (usageAmount - 1000) * 0.01;
    }

    void displayPlanDetails() {
        cout << "Free Plan: Free up to 1000 units, then $0.01 per unit" << endl;
    }
};

// PRO PLAN 
class ProPlan : public SubscriptionPlan {
public:
    ProPlan() : SubscriptionPlan("Pro Plan", 29) {}

    double calculateBill(double usageAmount) {
        double extra = 0;

        if (usageAmount > 10000)
            extra = (usageAmount - 10000) * 0.05;

        return basePrice + extra;
    }

    void displayPlanDetails() {
        cout << "Pro Plan: $29 + $0.05 per call after 10,000" << endl;
    }
};

// ENTERPRISE PLAN 
class EnterprisePlan : public SubscriptionPlan {
private:
    double negotiatedRate;

public:
    EnterprisePlan(double rate)
        : SubscriptionPlan("Enterprise Plan", 0) {
        negotiatedRate = rate;
    }

    double calculateBill(double usageAmount) {
        return negotiatedRate;
    }

    void displayPlanDetails() {
        cout << "Enterprise Plan: Flat rate = $" << negotiatedRate << endl;
    }
};