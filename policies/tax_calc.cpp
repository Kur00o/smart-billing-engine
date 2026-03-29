#include <iostream>
#include <string>
using namespace std;

// Base Class
class TaxCalculator {
public:
    virtual double calculateTax(double amount) = 0;
    virtual string taxName() = 0;
};

// GST (India)
class GSTCalculator : public TaxCalculator {
public:
    double calculateTax(double amount) override {
        return amount * 0.18;
    }

    string taxName() override {
        return "GST (18%)";
    }
};

// VAT
class VATCalculator : public TaxCalculator {
private:
    double rate;

public:
    VATCalculator(double r) {
        rate = r;
    }

    double calculateTax(double amount) override {
        return amount * rate;
    }

    string taxName() override {
        return "VAT";
    }
};