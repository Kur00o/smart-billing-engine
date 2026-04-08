#include "tax_calculator.h"
#include <sstream>
#include <iomanip>

// ============================================================
// GSTCalculator Implementation
// ============================================================

const double GSTCalculator::GST_RATE = 0.18;  // Fixed at 18%

double GSTCalculator::calculateTax(double amount) {
    return amount * GST_RATE;
}

string GSTCalculator::taxName() const {
    stringstream ss;
    ss << "GST (" << fixed << setprecision(0) << (GST_RATE * 100) << "%)";
    return ss.str();
}

// ============================================================
// VATCalculator Implementation
// ============================================================

VATCalculator::VATCalculator(double rate) : vatRate(rate) {
}

double VATCalculator::calculateTax(double amount) {
    return amount * vatRate;
}

string VATCalculator::taxName() const {
    stringstream ss;
    ss << "VAT (" << fixed << setprecision(1) << (vatRate * 100) << "%)";
    return ss.str();
}

void VATCalculator::setVATRate(double rate) {
    vatRate = rate;
}

double VATCalculator::getVATRate() const {
    return vatRate;
}