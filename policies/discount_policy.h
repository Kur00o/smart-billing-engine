#pragma once

#include <string>
#include <iostream>
#include <vector>
using namespace std;

// ==================== Discount Policy Interface ====================
class DiscountPolicy {
public:
    virtual double applyDiscount(double amount) = 0;
    virtual string discountName() const = 0;
    virtual ~DiscountPolicy() = default;
};

// ==================== NoDiscount ====================
// No discount applied
class NoDiscount : public DiscountPolicy {
public:
    double applyDiscount(double amount) override;
    string discountName() const override;
};

// ==================== PercentageDiscount ====================
// Fixed percentage discount (e.g., 10%)
class PercentageDiscount : public DiscountPolicy {
private:
    double discountPercentage;  // e.g., 0.10 for 10%

public:
    PercentageDiscount(double percentage);
    
    double applyDiscount(double amount) override;
    string discountName() const override;
    
    void setDiscountPercentage(double percentage);
    double getDiscountPercentage() const;
};

// ==================== SeasonalDiscount ====================
// Seasonal discount (e.g., 20% off during certain months)
class SeasonalDiscount : public DiscountPolicy {
private:
    double discountPercentage;
    int seasonMonth;  // Month when discount applies

public:
    SeasonalDiscount(double percentage, int month);
    
    double applyDiscount(double amount) override;
    string discountName() const override;
    
    void setSeasonMonth(int month);
    int getSeasonMonth() const;
};
