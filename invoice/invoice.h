#pragma once

#include <string>
#include <vector>
#include <iostream>
using namespace std;

// ==================== LineItem Structure ====================
struct LineItem {
    string description;
    double amount;
    
    LineItem(const string& desc, double amt) : description(desc), amount(amt) {}
};

// ==================== Invoice Class ====================
class Invoice {
private:
    int userId;
    int month;
    int year;
    vector<LineItem> lineItems;
    double discountAmount;
    double taxAmount;

public:
    Invoice(int id, int m, int y);
    
    // Line item management
    void addLineItem(const string& description, double amount);
    
    // Discount and tax setters
    void setDiscount(double discount);
    void setTax(double tax);
    
    // Calculation methods
    double getSubtotal() const;
    double getTotal() const;
    
    // Getters
    int getUserId() const;
    int getMonth() const;
    int getYear() const;
    double getDiscountAmount() const;
    double getTaxAmount() const;
    vector<LineItem> getLineItems() const;
    
    // Display and file operations
    void printInvoice() const;
    void saveToFile(const string& filename) const;
};
