#include "pricing_engine.h"
#include "../models/subscription.cpp"
#include <iostream>
#include <iomanip>

using namespace std;

// ==================== PricingEngine Implementation ====================

// Constructor
PricingEngine::PricingEngine(SubscriptionPlan* plan, const UsageMetrics& metrics)
    : subscriptionPlan(plan), usageMetrics(metrics), lastComputedBill(0.0) {
}

// Compute total bill: apply subscription plan's calculateBill() then apply pricing rules sequentially
double PricingEngine::computeTotal() {
    if (subscriptionPlan == nullptr) {
        cerr << "Error: SubscriptionPlan is null" << endl;
        return 0.0;
    }

    // Step 1: Calculate base bill using the subscription plan's method
    double baseAmount = subscriptionPlan->calculateBill(usageMetrics.apiCalls);
    
    cout << "\n========== Billing Calculation Breakdown ==========" << endl;
    cout << "Plan: " << subscriptionPlan->getPlanName() << endl;
    cout << "API Calls: " << usageMetrics.apiCalls << endl;
    cout << "Storage: " << fixed << setprecision(2) << usageMetrics.storageGB << " GB" << endl;
    cout << "Active Users: " << usageMetrics.activeUsers << endl;
    cout << "\nBase Bill (from plan): $" << fixed << setprecision(2) << baseAmount << endl;

    // Step 2: Apply each pricing rule sequentially (Open-Closed Principle)
    // Adding new PricingRule subclasses requires NO changes to this code
    double finalAmount = baseAmount;
    cout << "\n--- Applying Pricing Rules ---" << endl;
    
    if (rules.empty()) {
        cout << "No pricing rules applied." << endl;
    } else {
        for (PricingRule* rule : rules) {
            double beforeRule = finalAmount;
            finalAmount = rule->apply(finalAmount);
            cout << rule->ruleName() << ": $" << fixed << setprecision(2) 
                 << beforeRule << " → $" << finalAmount << endl;
        }
    }

    lastComputedBill = finalAmount;
    cout << "\nFinal Bill: $" << fixed << setprecision(2) << finalAmount << endl;
    cout << "==================================================\n" << endl;
    
    return finalAmount;
}

// Add a pricing rule - demonstrates extensibility
void PricingEngine::addRule(PricingRule* rule) {
    if (rule != nullptr) {
        rules.push_back(rule);
    }
}

// Remove a pricing rule by index
void PricingEngine::removeRule(int index) {
    if (index >= 0 && index < (int)rules.size()) {
        PricingRule* rule = rules[index];
        rules.erase(rules.begin() + index);
        delete rule;
    }
}

// Get the count of active rules
int PricingEngine::getRuleCount() const {
    return rules.size();
}

// Display breakdown of the calculation
void PricingEngine::displayBreakdown() const {
    cout << "\n========== Billing Breakdown Summary ==========" << endl;
    cout << "Plan: " << subscriptionPlan->getPlanName() << endl;
    cout << "Number of Pricing Rules: " << rules.size() << endl;
    
    if (!rules.empty()) {
        cout << "\nActive Rules:" << endl;
        for (int i = 0; i < (int)rules.size(); i++) {
            cout << "  [" << (i + 1) << "] " << rules[i]->ruleName() << endl;
        }
    }
    
    cout << "\nFinal Amount: $" << fixed << setprecision(2) << lastComputedBill << endl;
    cout << "============================================\n" << endl;
}


// ══════════════════════════════════════════════════════════════════════════
//  Quick local test — remove this main() when linking with main.cpp
// ══════════════════════════════════════════════════════════════════════════
/*
int main() {
    // Simulate a ProPlan user: $29 base, $0.001/call, $0.50/GB
    UsageRecord usage(7200, 15.5, 4);   // 7200 calls, 15.5 GB, 4 users

    PricingEngine engine(new PerUnitStrategy(29.0, 0.001, 0.50));
    engine.addRule(new OverageSurchargeRule(5000, 0.002));
    engine.addRule(new HighUsageDiscountRule(7000, 0.05));

    double finalBill = engine.applyPricingRules(usage);
    cout << "\nFinal Bill: $" << finalBill << "\n";

    return 0;
}
*/