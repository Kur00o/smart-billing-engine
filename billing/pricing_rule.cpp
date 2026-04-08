#include "pricing_rule.h"
#include <iostream>

using namespace std;

// ==================== ProratedRule ====================
ProratedRule::ProratedRule(int daysUsed, int daysInMonth)
    : daysUsed(daysUsed), daysInMonth(daysInMonth) {
}

double ProratedRule::apply(double baseAmount) {
    // Prorate based on days used vs total days in month
    if (daysInMonth <= 0) {
        return baseAmount;
    }
    
    double prorationFactor = (double)daysUsed / daysInMonth;
    return baseAmount * prorationFactor;
}

string ProratedRule::ruleName() const {
    return "Prorated Rule (" + to_string(daysUsed) + "/" + to_string(daysInMonth) + " days)";
}

// ==================== VolumeDiscountRule ====================
double VolumeDiscountRule::apply(double baseAmount) {
    // Apply 10% discount if amount > $500
    if (baseAmount > 500.0) {
        return baseAmount * 0.9;  // 10% off
    }
    return baseAmount;
}

string VolumeDiscountRule::ruleName() const {
    return "Volume Discount Rule (10% off if > $500)";
}
