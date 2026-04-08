#pragma once

#include <string>
#include <iostream>
using namespace std;

// ==================== Tax Calculator Interface ====================
class TaxCalculator {
public:
    virtual double calculateTax(double amount) = 0;
    virtual string taxName() const = 0;
    virtual ~TaxCalculator() = default;
};

// ==================== GST Calculator ====================
// Fixed percentage GST (Goods and Services Tax)
class GSTCalculator : public TaxCalculator {
private:
    static const double GST_RATE;  // Fixed at 18%

public:
    double calculateTax(double amount) override;
    string taxName() const override;
};

// ==================== VAT Calculator ====================
// Custom Value Added Tax
class VATCalculator : public TaxCalculator {
private:
    double vatRate;  // Custom VAT rate

public:
    VATCalculator(double rate = 0.15);  // Default 15%
    
    double calculateTax(double amount) override;
    string taxName() const override;
    
    void setVATRate(double rate);
    double getVATRate() const;
};
