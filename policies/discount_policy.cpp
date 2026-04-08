#include "discount_policy.h"
#include <sstream>
#include <iomanip>

// ============================================================
// NoDiscount Implementation
// ============================================================

double NoDiscount::applyDiscount(double amount) {
    return amount;
}

string NoDiscount::discountName() const {
    return "No Discount";
}

// ============================================================
// PercentageDiscount Implementation
// ============================================================

PercentageDiscount::PercentageDiscount(double percentage)
    : discountPercentage(percentage) {
}

double PercentageDiscount::applyDiscount(double amount) {
    double discountedAmount = amount - (amount * discountPercentage);
    return discountedAmount;
}

string PercentageDiscount::discountName() const {
    stringstream ss;
    ss << fixed << setprecision(1) << (discountPercentage * 100) << "% Discount";
    return ss.str();
}

void PercentageDiscount::setDiscountPercentage(double percentage) {
    discountPercentage = percentage;
}

double PercentageDiscount::getDiscountPercentage() const {
    return discountPercentage;
}

// ============================================================
// SeasonalDiscount Implementation
// ============================================================

SeasonalDiscount::SeasonalDiscount(double percentage, int month)
    : discountPercentage(percentage), seasonMonth(month) {
}

double SeasonalDiscount::applyDiscount(double amount) {
    // In a real implementation, you would check the current month
    // For now, we'll apply the discount if the season month is set
    if (seasonMonth >= 1 && seasonMonth <= 12) {
        return amount - (amount * discountPercentage);
    }
    return amount;
}

string SeasonalDiscount::discountName() const {
    stringstream ss;
    ss << fixed << setprecision(1) << (discountPercentage * 100) 
       << "% Seasonal Discount (Month " << seasonMonth << ")";
    return ss.str();
}

void SeasonalDiscount::setSeasonMonth(int month) {
    seasonMonth = month;
}

int SeasonalDiscount::getSeasonMonth() const {
    return seasonMonth;
}
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