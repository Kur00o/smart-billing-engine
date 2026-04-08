#include "subscription.h"

// ============================================================
// SubscriptionPlan - Base Class Implementation
// ============================================================

SubscriptionPlan::SubscriptionPlan(const string& name, double price)
    : planName(name), basePrice(price), freeLimit(0), overageRate(0) {
}

string SubscriptionPlan::getPlanName() const {
    return planName;
}

double SubscriptionPlan::getBasePrice() const {
    return basePrice;
}

void SubscriptionPlan::display() const {
    cout << "\nPlan: " << planName << endl;
    cout << "Base Price: $" << basePrice << endl;
    displayPlanDetails();
}

// ============================================================
// FreePlan Implementation
// ============================================================

const double FreePlan::FREE_LIMIT = 1000.0;
const double FreePlan::OVERAGE_RATE = 0.01;

FreePlan::FreePlan() : SubscriptionPlan("Free Plan", 0) {
    freeLimit = FREE_LIMIT;
    overageRate = OVERAGE_RATE;
}

double FreePlan::calculateBill(double usageAmount) {
    if (usageAmount <= FREE_LIMIT) {
        return 0;
    }
    return (usageAmount - FREE_LIMIT) * OVERAGE_RATE;
}

void FreePlan::displayPlanDetails() {
    cout << "Free up to " << FREE_LIMIT << " units, then $" << OVERAGE_RATE << " per unit" << endl;
}

// ============================================================
// ProPlan Implementation
// ============================================================

const double ProPlan::INCLUDED_CALLS = 10000.0;
const double ProPlan::OVERAGE_RATE = 0.05;

ProPlan::ProPlan() : SubscriptionPlan("Pro Plan", 29.0) {
    overageRate = OVERAGE_RATE;
}

double ProPlan::calculateBill(double usageAmount) {
    double bill = basePrice;
    
    if (usageAmount > INCLUDED_CALLS) {
        double overage = usageAmount - INCLUDED_CALLS;
        bill += overage * OVERAGE_RATE;
    }
    
    return bill;
}

void ProPlan::displayPlanDetails() {
    cout << "$" << basePrice << " + $" << OVERAGE_RATE << " per call after " 
         << INCLUDED_CALLS << " calls" << endl;
}

// ============================================================
// EnterprisePlan Implementation
// ============================================================

EnterprisePlan::EnterprisePlan(double rate)
    : SubscriptionPlan("Enterprise Plan", 0), negotiatedRate(rate) {
}

double EnterprisePlan::calculateBill(double usageAmount) {
    // Enterprise plan: flat negotiated rate regardless of usage
    return negotiatedRate;
}

void EnterprisePlan::displayPlanDetails() {
    cout << "Enterprise Plan - Negotiated Rate: $" << negotiatedRate << endl;
}

void EnterprisePlan::setNegotiatedRate(double rate) {
    negotiatedRate = rate;
}

double EnterprisePlan::getNegotiatedRate() const {
    return negotiatedRate;
}