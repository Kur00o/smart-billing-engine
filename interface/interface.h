#pragma once

#include <string>
#include <map>
#include <vector>
#include <memory>
#include "../models/user.h"
#include "../models/subscription.h"
#include "../billing/usage_tracker.h"
#include "../policies/discount_policy.h"
#include "../policies/tax_calculator.h"
#include "../policies/addon.h"
#include "../invoice/invoice_generator.h"
using namespace std;

// ==================== Interface Class ====================
// CLI-based menu system for managing the billing engine
class Interface {
private:
    map<int, User> users;                    // Store users by ID
    map<int, SubscriptionPlan*> subscriptions; // Store plans by user ID
    UsageTracker* usageTracker;
    InvoiceGenerator* invoiceGenerator;
    
    int nextUserId;
    
public:
    Interface();
    ~Interface();
    
    // Menu functions
    void displayMainMenu();
    void run();
    
    // User management
    void manageUsers();
    void addUser();
    void displayAllUsers();
    
    // Subscription management
    void manageSubscriptions();
    void assignPlan(int userId);
    void displayAllSubscriptions();
    
    // Usage tracking
    void trackUsage();
    void recordUsage(int userId);
    void displayUsageData(int userId);
    
    // Billing configuration
    void configureBilling();
    void setDiscount();
    void setTax();
    void addAddOns();
    
    // Invoice generation
    void generateInvoiceMenu();
    void generateAndDisplayInvoice(int userId, int month, int year);
    
    // Display options
    void displayUsersAndPlans();
    
private:
    // Helper methods
    int getUserIdInput();
    SubscriptionPlan* getPlanInput();
};
