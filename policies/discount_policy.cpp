#include <iostream>
#include <string>
using namespace std;

// Base Class
class DiscountPolicy {
public:
    virtual double applyDiscount(double amount) = 0;
    virtual string discountName() = 0;
};

// No Discount
class NoDiscount : public DiscountPolicy {
public:
    double applyDiscount(double amount) override {
        return amount;
    }

    string discountName() override {
        return "No Discount";
    }
};

// Percentage Discount
class PercentageDiscount : public DiscountPolicy {
private:
    double percent;

public:
    PercentageDiscount(double p) {
        percent = p;
    }

    double applyDiscount(double amount) override {
        return amount * (1.0 - percent / 100.0);
    }

    string discountName() override {
        return to_string(percent) + "% Discount";
    }
};

// Seasonal Discount
class SeasonalDiscount : public DiscountPolicy {
private:
    int activeMonth;

public:
    SeasonalDiscount(int month) {
        activeMonth = month;
    }

    double applyDiscount(double amount) override {
        int currentMonth = 12; // Example (December)
        if (currentMonth == activeMonth)
            return amount * 0.8; // 20% off
        return amount;
    }

    string discountName() override {
        return "Seasonal Discount";
    }
};