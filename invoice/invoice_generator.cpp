#include "invoice_generator.h"
#include <iomanip>

// ============================================================
// InvoiceGenerator Class Implementation
// ============================================================

InvoiceGenerator::InvoiceGenerator(SubscriptionPlan* plan, UsageTracker* tracker)
    : subscriptionPlan(plan), usageTracker(tracker), discountPolicy(nullptr), 
      taxCalculator(nullptr) {
    // Set default policies if not provided
    if (!discountPolicy) {
        discountPolicy = new NoDiscount();
    }
    if (!taxCalculator) {
        taxCalculator = new GSTCalculator();
    }
}

void InvoiceGenerator::setDiscountPolicy(DiscountPolicy* policy) {
    if (policy) {
        delete discountPolicy;
        discountPolicy = policy;
    }
}

void InvoiceGenerator::setTaxCalculator(TaxCalculator* calculator) {
    if (calculator) {
        delete taxCalculator;
        taxCalculator = calculator;
    }
}

void InvoiceGenerator::addAddOn(const AddOn& addon) {
    addons.push_back(addon);
}

void InvoiceGenerator::clearAddOns() {
    addons.clear();
}

Invoice* InvoiceGenerator::generateInvoice(const User& user, int month, int year) {
    if (!subscriptionPlan || !usageTracker) {
        cerr << "Error: SubscriptionPlan or UsageTracker not set" << endl;
        return nullptr;
    }

    Invoice* invoice = new Invoice(user.getId(), month, year);

    // Step 1: Get usage metrics
    UsageMetrics metrics = usageTracker->getUsage(user.getId(), month, year);

    // Step 2: Calculate base bill using subscription plan
    double baseBill = subscriptionPlan->calculateBill(metrics.apiCalls);
    
    // Step 3: Add base line item
    cout << "\n========== Generating Invoice ==========" << endl;
    cout << "User: " << user.getName() << " (ID: " << user.getId() << ")" << endl;
    cout << "Plan: " << subscriptionPlan->getPlanName() << endl;
    cout << "Month: " << month << "/" << year << endl;
    cout << "\nBase Bill: $" << fixed << setprecision(2) << baseBill << endl;
    
    invoice->addLineItem("Subscription (" + subscriptionPlan->getPlanName() + ")", baseBill);

    // Step 4: Add add-ons as line items
    double addonTotal = 0.0;
    if (!addons.empty()) {
        cout << "Add-ons:" << endl;
        for (const AddOn& addon : addons) {
            cout << "  - " << addon.getName() << ": $" << fixed << setprecision(2) << addon.getPrice() << endl;
            invoice->addLineItem(addon.getName(), addon.getPrice());
            addonTotal += addon.getPrice();
        }
    }

    // Step 5: Calculate subtotal and apply discount
    double subtotal = baseBill + addonTotal;
    double discountAmount = discountPolicy->applyDiscount(subtotal) - subtotal;
    double discountedAmount = subtotal - discountAmount;
    
    cout << "Subtotal: $" << fixed << setprecision(2) << subtotal << endl;
    if (discountAmount > 0) {
        cout << "Discount (" << discountPolicy->discountName() << "): -$" 
             << fixed << setprecision(2) << discountAmount << endl;
    }
    
    invoice->setDiscount(fabs(discountAmount));

    // Step 6: Apply tax
    double taxAmount = taxCalculator->calculateTax(discountedAmount);
    cout << "Tax (" << taxCalculator->taxName() << "): +$" << fixed << setprecision(2) << taxAmount << endl;
    
    invoice->setTax(taxAmount);

    // Step 7: Return final invoice
    double finalBill = discountedAmount + taxAmount;
    cout << "Final Bill: $" << fixed << setprecision(2) << finalBill << endl;
    cout << "====================================\n" << endl;

    return invoice;
}

InvoiceGenerator::~InvoiceGenerator() {
    delete discountPolicy;
    delete taxCalculator;
}
