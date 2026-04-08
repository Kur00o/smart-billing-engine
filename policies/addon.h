#pragma once

#include <string>
#include <vector>
#include <memory>
#include <iostream>
using namespace std;

// ==================== Add-On Class ====================
// Represents additional features/services that can be added to a subscription
class AddOn {
private:
    string addonName;
    double monthlyPrice;

public:
    AddOn(const string& name, double price);
    
    // Getters
    string getName() const;
    double getPrice() const;
    
    // Setters
    void setPrice(double price);
    
    // Display function
    void display() const;
};

// ==================== Add-On Factory ====================
// Factory class for creating predefined add-ons
class AddOnFactory {
public:
    // Static factory methods for predefined add-ons
    static AddOn createAnalyticsAddOn();      // $10/month
    static AddOn createBackupAddOn();         // $15/month
    static AddOn createPrioritySupportAddOn(); // $20/month
    
    // Generic factory method
    static AddOn createCustomAddOn(const string& name, double price);
};

// ==================== Helper Functions ====================
// Calculate total cost of all add-ons
double applyAllAddOns(const vector<AddOn>& addons);
