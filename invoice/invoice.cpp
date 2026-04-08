#include "invoice.h"
#include <fstream>
#include <iomanip>
#include <sstream>

// ============================================================
// Invoice Class Implementation
// ============================================================

Invoice::Invoice(int id, int m, int y)
    : userId(id), month(m), year(y), discountAmount(0), taxAmount(0) {
}

void Invoice::addLineItem(const string& description, double amount) {
    lineItems.push_back(LineItem(description, amount));
}

void Invoice::setDiscount(double discount) {
    discountAmount = discount;
}

void Invoice::setTax(double tax) {
    taxAmount = tax;
}

double Invoice::getSubtotal() const {
    double subtotal = 0.0;
    for (const LineItem& item : lineItems) {
        subtotal += item.amount;
    }
    return subtotal;
}

double Invoice::getTotal() const {
    // Total = subtotal - discount + tax
    double subtotal = getSubtotal();
    return subtotal - discountAmount + taxAmount;
}

int Invoice::getUserId() const {
    return userId;
}

int Invoice::getMonth() const {
    return month;
}

int Invoice::getYear() const {
    return year;
}

double Invoice::getDiscountAmount() const {
    return discountAmount;
}

double Invoice::getTaxAmount() const {
    return taxAmount;
}

vector<LineItem> Invoice::getLineItems() const {
    return lineItems;
}

void Invoice::printInvoice() const {
    cout << "\n" << string(60, '=') << endl;
    cout << "INVOICE" << endl;
    cout << string(60, '=') << endl;
    cout << "\nUser ID: " << userId << endl;
    cout << "Month: " << month << "/" << year << endl;
    cout << "\n" << string(60, '-') << endl;
    cout << "Line Items:" << endl;
    cout << string(60, '-') << endl;
    
    for (const LineItem& item : lineItems) {
        cout << left << setw(40) << item.description 
             << right << setw(15) << "$" << fixed << setprecision(2) << item.amount << endl;
    }
    
    cout << "\n" << string(60, '-') << endl;
    double subtotal = getSubtotal();
    cout << left << setw(40) << "Subtotal:" 
         << right << setw(15) << "$" << fixed << setprecision(2) << subtotal << endl;
    
    if (discountAmount > 0) {
        cout << left << setw(40) << "Discount:" 
             << right << setw(15) << "-$" << fixed << setprecision(2) << discountAmount << endl;
    }
    
    if (taxAmount > 0) {
        cout << left << setw(40) << "Tax:" 
             << right << setw(15) << "+$" << fixed << setprecision(2) << taxAmount << endl;
    }
    
    cout << "\n" << string(60, '=') << endl;
    cout << left << setw(40) << "TOTAL:" 
         << right << setw(15) << "$" << fixed << setprecision(2) << getTotal() << endl;
    cout << string(60, '=') << "\n" << endl;
}

void Invoice::saveToFile(const string& filename) const {
    ofstream outfile(filename, ios::app);
    
    if (!outfile.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        return;
    }
    
    outfile << "\n" << string(60, '=') << endl;
    outfile << "INVOICE" << endl;
    outfile << string(60, '=') << endl;
    outfile << "\nUser ID: " << userId << endl;
    outfile << "Month: " << month << "/" << year << endl;
    outfile << "\n" << string(60, '-') << endl;
    outfile << "Line Items:" << endl;
    outfile << string(60, '-') << endl;
    
    for (const LineItem& item : lineItems) {
        outfile << left << setw(40) << item.description 
                << right << setw(15) << "$" << fixed << setprecision(2) << item.amount << endl;
    }
    
    outfile << "\n" << string(60, '-') << endl;
    double subtotal = getSubtotal();
    outfile << left << setw(40) << "Subtotal:" 
            << right << setw(15) << "$" << fixed << setprecision(2) << subtotal << endl;
    
    if (discountAmount > 0) {
        outfile << left << setw(40) << "Discount:" 
                << right << setw(15) << "-$" << fixed << setprecision(2) << discountAmount << endl;
    }
    
    if (taxAmount > 0) {
        outfile << left << setw(40) << "Tax:" 
                << right << setw(15) << "+$" << fixed << setprecision(2) << taxAmount << endl;
    }
    
    outfile << "\n" << string(60, '=') << endl;
    outfile << left << setw(40) << "TOTAL:" 
            << right << setw(15) << "$" << fixed << setprecision(2) << getTotal() << endl;
    outfile << string(60, '=') << endl;
    
    outfile.close();
    cout << "Invoice saved to " << filename << endl;
}
