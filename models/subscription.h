#pragma once

#include <string>
#include <vector>
#include <iostream>
using namespace std;

// Abstract Base Class for Subscription Plans
class SubscriptionPlan {
protected:
    string planName;
    double basePrice;
    double freeLimit;  // Free usage limit (for FreePlan)
    double overageRate; // Rate for overages

public:
    SubscriptionPlan(const string& name, double price);
    virtual ~SubscriptionPlan() = default;
    
    // Pure virtual function - must be implemented by derived classes
    virtual double calculateBill(double usageAmount) = 0;
    
    // Regular virtual functions
    virtual void displayPlanDetails() = 0;
    
    // Getters
    string getPlanName() const;
    double getBasePrice() const;
    
    // Display function
    virtual void display() const;
};

// ==================== FreePlan ====================
class FreePlan : public SubscriptionPlan {
private:
    static const double FREE_LIMIT;      // 1000 units free
    static const double OVERAGE_RATE;    // $0.01 per unit

public:
    FreePlan();
    
    double calculateBill(double usageAmount) override;
    void displayPlanDetails() override;
};

// ==================== ProPlan ====================
class ProPlan : public SubscriptionPlan {
private:
    static const double INCLUDED_CALLS;  // 10000 calls included
    static const double OVERAGE_RATE;    // $0.05 per call

public:
    ProPlan();
    
    double calculateBill(double usageAmount) override;
    void displayPlanDetails() override;
};

// ==================== EnterprisePlan ====================
class EnterprisePlan : public SubscriptionPlan {
private:
    double negotiatedRate;

public:
    EnterprisePlan(double rate = 1000.0);
    
    double calculateBill(double usageAmount) override;
    void displayPlanDetails() override;
    
    void setNegotiatedRate(double rate);
    double getNegotiatedRate() const;
};
