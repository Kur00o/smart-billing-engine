#pragma once

#include <vector>
#include <iostream>
#include "pricing_rule.h"
#include "usage_tracker.h"
using namespace std;

// Forward declaration
class SubscriptionPlan;

// Pricing Engine - Computes total bill applying subscription plan's calculateBill then all pricing rules
class PricingEngine {
public:
    PricingEngine(SubscriptionPlan* plan, const UsageMetrics& metrics);
    
    // Calculate total bill: apply plan's calculateBill() then apply all pricing rules sequentially
    double computeTotal();
    
    // Manage pricing rules - demonstrates Open-Closed Principle
    void addRule(PricingRule* rule);
    void removeRule(int index);
    int getRuleCount() const;
    
    // Display computation breakdown
    void displayBreakdown() const;

private:
    SubscriptionPlan* subscriptionPlan;
    UsageMetrics usageMetrics;
    vector<PricingRule*> rules;
    
    // Storage for last computed bill
    mutable double lastComputedBill;
};
