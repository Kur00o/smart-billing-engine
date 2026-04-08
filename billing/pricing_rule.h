#pragma once

#include <string>
using namespace std;

// Abstract Pricing Rule Interface - Open/Closed Design
class PricingRule {
public:
    virtual double apply(double baseAmount) = 0;
    virtual string ruleName() const = 0;
    virtual ~PricingRule() = default;
};

// Concrete Rule 1: Prorated Pricing
class ProratedRule : public PricingRule {
public:
    ProratedRule(int daysUsed, int daysInMonth);
    double apply(double baseAmount) override;
    string ruleName() const override;

private:
    int daysUsed;
    int daysInMonth;
};

// Concrete Rule 2: Volume Discount Rule
// 10% off if amount > $500
class VolumeDiscountRule : public PricingRule {
public:
    double apply(double baseAmount) override;
    string ruleName() const override;
};
