#pragma once

#include "../models/subscription.h"
#include "../models/user.h"
#include "../billing/usage_tracker.h"
#include "../policies/discount_policy.h"
#include "../policies/tax_calculator.h"
#include "../policies/addon.h"
#include "invoice.h"
#include <vector>
#include <memory>
#include <iostream>
using namespace std;

// ==================== Invoice Generator Class ====================
// Generates invoices by combining subscription plan, usage, discounts, tax, and add-ons
class InvoiceGenerator {
private:
    SubscriptionPlan* subscriptionPlan;
    UsageTracker* usageTracker;
    DiscountPolicy* discountPolicy;
    TaxCalculator* taxCalculator;
    vector<AddOn> addons;

public:
    InvoiceGenerator(SubscriptionPlan* plan, UsageTracker* tracker);
    
    // Configuration methods
    void setDiscountPolicy(DiscountPolicy* policy);
    void setTaxCalculator(TaxCalculator* calculator);
    void addAddOn(const AddOn& addon);
    void clearAddOns();
    
    // Main generation method
    // Generates invoice for a user in a specific month/year
    Invoice* generateInvoice(const User& user, int month, int year);
    
    // Destructor
    ~InvoiceGenerator();
};
