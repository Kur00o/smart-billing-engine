#pragma once

#include <string>
#include <cmath>
using namespace std;

// Abstract Billing Strategy Interface
class BillingStrategy {
public:
    virtual double calculate(double usage, double rate) = 0;
    virtual string strategyName() const = 0;
    virtual ~BillingStrategy() = default;
};

// Concrete Strategy 1: Flat Rate
class FlatRateStrategy : public BillingStrategy {
public:
    double calculate(double usage, double rate) override;
    string strategyName() const override;
};

// Concrete Strategy 2: Per Unit
class PerUnitStrategy : public BillingStrategy {
public:
    double calculate(double usage, double rate) override; // usage * rate
    string strategyName() const override;
};

// Concrete Strategy 3: Tiered Pricing
// Tier 1: 0-1000 at rate
// Tier 2: 1001-5000 at rate*0.8
// Tier 3: 5001+ at rate*0.6
class TieredStrategy : public BillingStrategy {
public:
    double calculate(double usage, double rate) override;
    string strategyName() const override;
};
