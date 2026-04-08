#include "billing_strategy.h"
#include <iostream>

using namespace std;

// ==================== FlatRateStrategy ====================
double FlatRateStrategy::calculate(double usage, double rate) {
    // Flat rate ignores usage, charges fixed rate
    return rate;
}

string FlatRateStrategy::strategyName() const {
    return "Flat Rate Strategy";
}

// ==================== PerUnitStrategy ====================
double PerUnitStrategy::calculate(double usage, double rate) {
    // Simple per-unit charging: usage * rate
    return usage * rate;
}

string PerUnitStrategy::strategyName() const {
    return "Per Unit Strategy";
}

// ==================== TieredStrategy ====================
// Tier 1: 0-1000 at rate
// Tier 2: 1001-5000 at rate*0.8 (20% discount)
// Tier 3: 5001+ at rate*0.6 (40% discount)
double TieredStrategy::calculate(double usage, double rate) {
    double total = 0.0;

    if (usage <= 0) {
        return 0.0;
    }

    // Tier 1: First 1000 units at full rate
    if (usage <= 1000) {
        total = usage * rate;
    }
    // Tier 2: Units 1001-5000 at 80% rate
    else if (usage <= 5000) {
        total = (1000 * rate) + ((usage - 1000) * rate * 0.8);
    }
    // Tier 3: Units 5001+ at 60% rate
    else {
        total = (1000 * rate) + (4000 * rate * 0.8) + ((usage - 5000) * rate * 0.6);
    }

    return total;
}

string TieredStrategy::strategyName() const {
    return "Tiered Strategy (0-1000@100%, 1001-5000@80%, 5001+@60%)";
}
