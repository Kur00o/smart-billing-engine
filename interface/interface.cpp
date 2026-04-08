#include "interface.h"
#include <iostream>
#include <limits>

// ============================================================
// Interface Class Implementation
// ============================================================

Interface::Interface() : nextUserId(1), usageTracker(new UsageTracker()), 
                        invoiceGenerator(nullptr) {
}

Interface::~Interface() {
    delete usageTracker;
    delete invoiceGenerator;
    // Clean up subscription plans
    for (auto& entry : subscriptions) {
        delete entry.second;
    }
}

void Interface::displayMainMenu() {
    cout << "\n" << string(60, '=') << endl;
    cout << "SMART SUBSCRIPTION & USAGE-BASED BILLING ENGINE" << endl;
    cout << string(60, '=') << endl;
    cout << "\n[1] Manage Users" << endl;
    cout << "[2] Manage Subscriptions" << endl;
    cout << "[3] Track Usage" << endl;
    cout << "[4] Configure Billing" << endl;
    cout << "[5] Generate Invoice" << endl;
    cout << "[6] Display Users & Plans" << endl;
    cout << "[0] Exit" << endl;
    cout << "\nEnter your choice: ";
}

void Interface::run() {
    int choice = -1;
    
    while (true) {
        displayMainMenu();
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        switch (choice) {
            case 1:
                manageUsers();
                break;
            case 2:
                manageSubscriptions();
                break;
            case 3:
                trackUsage();
                break;
            case 4:
                configureBilling();
                break;
            case 5:
                generateInvoiceMenu();
                break;
            case 6:
                displayUsersAndPlans();
                break;
            case 0:
                cout << "\nExiting... Thank you!" << endl;
                return;
            default:
                cout << "\nInvalid choice. Please try again." << endl;
        }
    }
}

// ============================================================
// User Management
// ============================================================

void Interface::manageUsers() {
    cout << "\n--- Manage Users ---" << endl;
    cout << "[1] Add User" << endl;
    cout << "[2] Display All Users" << endl;
    cout << "[0] Back" << endl;
    cout << "Choice: ";
    
    int choice;
    cin >> choice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    switch (choice) {
        case 1:
            addUser();
            break;
        case 2:
            displayAllUsers();
            break;
        default:
            break;
    }
}

void Interface::addUser() {
    string name, email;
    
    cout << "\nEnter user name: ";
    getline(cin, name);
    
    cout << "Enter user email: ";
    getline(cin, email);
    
    users.emplace(nextUserId, User(nextUserId, name, email));
    cout << "\n✓ User added successfully! (ID: " << nextUserId << ")" << endl;
    nextUserId++;
}

void Interface::displayAllUsers() {
    if (users.empty()) {
        cout << "\nNo users found." << endl;
        return;
    }
    
    cout << "\n--- All Users ---" << endl;
    for (auto& entry : users) {
        entry.second.displayUser();
    }
}

// ============================================================
// Subscription Management
// ============================================================

void Interface::manageSubscriptions() {
    cout << "\n--- Manage Subscriptions ---"<< endl;
    cout << "[1] Assign Plan to User" << endl;
    cout << "[2] Display All Subscriptions" << endl;
    cout << "[0] Back" << endl;
    cout << "Choice: ";
    
    int choice;
    cin >> choice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    switch (choice) {
        case 1:
            assignPlan(getUserIdInput());
            break;
        case 2:
            displayAllSubscriptions();
            break;
        default:
            break;
    }
}

void Interface::assignPlan(int userId) {
    if (users.find(userId) == users.end()) {
        cout << "\nUser not found." << endl;
        return;
    }
    
    cout << "\nSelect plan:" << endl;
    cout << "[1] Free Plan" << endl;
    cout << "[2] Pro Plan" << endl;
    cout << "[3] Enterprise Plan" << endl;
    cout << "Choice: ";
    
    int choice;
    cin >> choice;
    
    if (choice == 1) {
        subscriptions[userId] = new FreePlan();
        cout << "\n✓ Free Plan assigned to user " << userId << endl;
    } else if (choice == 2) {
        subscriptions[userId] = new ProPlan();
        cout << "\n✓ Pro Plan assigned to user " << userId << endl;
    } else if (choice == 3) {
        cout << "Enter negotiated rate: $";
        double rate;
        cin >> rate;
        subscriptions[userId] = new EnterprisePlan(rate);
        cout << "\n✓ Enterprise Plan assigned to user " << userId << endl;
    }
}

void Interface::displayAllSubscriptions() {
    if (subscriptions.empty()) {
        cout << "\nNo subscriptions found." << endl;
        return;
    }
    
    cout << "\n--- All Subscriptions ---" << endl;
    for (auto& entry : subscriptions) {
        cout << "User ID: " << entry.first << " - Plan: " << entry.second->getPlanName() << endl;
    }
}

// ============================================================
// Usage Tracking
// ============================================================

void Interface::trackUsage() {
    cout << "\n--- Track Usage ---" << endl;
    cout << "[1] Record Usage" << endl;
    cout << "[2] Display Usage Data" << endl;
    cout << "[0] Back" << endl;
    cout << "Choice: ";
    
    int choice;
    cin >> choice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    switch (choice) {
        case 1:
            recordUsage(getUserIdInput());
            break;
        case 2:
            displayUsageData(getUserIdInput());
            break;
        default:
            break;
    }
}

void Interface::recordUsage(int userId) {
    cout << "\nEnter API calls: ";
    long apiCalls;
    cin >> apiCalls;
    
    cout << "Enter storage (GB): ";
    double storage;
    cin >> storage;
    
    cout << "Enter active users: ";
    int activeUsers;
    cin >> activeUsers;
    
    usageTracker->recordApiCall(userId, apiCalls);
    usageTracker->recordStorage(userId, storage);
    usageTracker->recordUsers(userId, activeUsers);
    
    cout << "\n✓ Usage recorded successfully!" << endl;
}

void Interface::displayUsageData(int userId) {
    usageTracker->displayUsage(userId);
}

// ============================================================
// Billing Configuration
// ============================================================

void Interface::configureBilling() {
    cout << "\n--- Configure Billing ---" << endl;
    cout << "[1] Set Discount Policy" << endl;
    cout << "[2] Set Tax Calculator" << endl;
    cout << "[3] Add Add-ons" << endl;
    cout << "[0] Back" << endl;
    cout << "Choice: ";
    
    int choice;
    cin >> choice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    switch (choice) {
        case 1:
            setDiscount();
            break;
        case 2:
            setTax();
            break;
        case 3:
            addAddOns();
            break;
        default:
            break;
    }
}

void Interface::setDiscount() {
    if (!invoiceGenerator) {
        cout << "\nError: Please generate an invoice first." << endl;
        return;
    }
    
    cout << "\nSelect discount type:" << endl;
    cout << "[1] No Discount" << endl;
    cout << "[2] Percentage Discount" << endl;
    cout << "[3] Seasonal Discount" << endl;
    cout << "Choice: ";
    
    int choice;
    cin >> choice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    if (choice == 1) {
        invoiceGenerator->setDiscountPolicy(new NoDiscount());
        cout << "\n✓ No discount applied." << endl;
    } else if (choice == 2) {
        cout << "Enter discount percentage (0-100): ";
        double percent;
        cin >> percent;
        invoiceGenerator->setDiscountPolicy(new PercentageDiscount(percent / 100.0));
        cout << "\n✓ Discount set to " << percent << "%." << endl;
    } else if (choice == 3) {
        cout << "Enter discount percentage: ";
        double percent;
        cin >> percent;
        cout << "Enter month (1-12): ";
        int month;
        cin >> month;
        invoiceGenerator->setDiscountPolicy(new SeasonalDiscount(percent / 100.0, month));
        cout << "\n✓ Seasonal discount set." << endl;
    }
}

void Interface::setTax() {
    if (!invoiceGenerator) {
        cout << "\nError: Please generate an invoice first." << endl;
        return;
    }
    
    cout << "\nSelect tax type:" << endl;
    cout << "[1] GST (18%)" << endl;
    cout << "[2] Custom VAT" << endl;
    cout << "Choice: ";
    
    int choice;
    cin >> choice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    if (choice == 1) {
        invoiceGenerator->setTaxCalculator(new GSTCalculator());
        cout << "\n✓ GST (18%) tax applied." << endl;
    } else if (choice == 2) {
        cout << "Enter VAT rate (0-100): ";
        double rate;
        cin >> rate;
        invoiceGenerator->setTaxCalculator(new VATCalculator(rate / 100.0));
        cout << "\n✓ VAT set to " << rate << "%." << endl;
    }
}

void Interface::addAddOns() {
    if (!invoiceGenerator) {
        cout << "\nError: Please generate an invoice first." << endl;
        return;
    }
    
    cout << "\nSelect add-ons:" << endl;
    cout << "[1] Analytics ($10/month)" << endl;
    cout << "[2] Backup ($15/month)" << endl;
    cout << "[3] Priority Support ($20/month)" << endl;
    cout << "[4] Custom Add-on" << endl;
    cout << "Choice (or 0 to finish): ";
    
    int choice;
    while (cin >> choice && choice != 0) {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        if (choice == 1) {
            invoiceGenerator->addAddOn(AddOnFactory::createAnalyticsAddOn());
            cout << "  ✓ Analytics added." << endl;
        } else if (choice == 2) {
            invoiceGenerator->addAddOn(AddOnFactory::createBackupAddOn());
            cout << "  ✓ Backup added." << endl;
        } else if (choice == 3) {
            invoiceGenerator->addAddOn(AddOnFactory::createPrioritySupportAddOn());
            cout << "  ✓ Priority Support added." << endl;
        } else if (choice == 4) {
            string name;
            double price;
            cout << "Enter add-on name: ";
            getline(cin, name);
            cout << "Enter price: $";
            cin >> price;
            invoiceGenerator->addAddOn(AddOnFactory::createCustomAddOn(name, price));
            cout << "  ✓ " << name << " added." << endl;
        }
        
        cout << "\nAdd another? (or 0 to finish): ";
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// ============================================================
// Invoice Generation
// ============================================================

void Interface::generateInvoiceMenu() {
    int userId = getUserIdInput();
    
    if (users.find(userId) == users.end()) {
        cout << "\nUser not found." << endl;
        return;
    }
    
    if (subscriptions.find(userId) == subscriptions.end()) {
        cout << "\nNo subscription assigned to this user." << endl;
        return;
    }
    
    // Create invoice generator if not exists
    if (!invoiceGenerator) {
        invoiceGenerator = new InvoiceGenerator(subscriptions[userId], usageTracker);
    }
    
    cout << "Enter month (1-12): ";
    int month;
    cin >> month;
    
    cout << "Enter year: ";
    int year;
    cin >> year;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    generateAndDisplayInvoice(userId, month, year);
}

void Interface::generateAndDisplayInvoice(int userId, int month, int year) {
    if (!invoiceGenerator || subscriptions.find(userId) == subscriptions.end()) {
        cout << "\nCannot generate invoice." << endl;
        return;
    }
    
    // Update the invoice generator's subscription plan for this user
    invoiceGenerator = new InvoiceGenerator(subscriptions[userId], usageTracker);
    
    Invoice* invoice = invoiceGenerator->generateInvoice(users.at(userId), month, year);
    
    if (invoice) {
        invoice->printInvoice();
        
        cout << "Save to file? (y/n): ";
        char response;
        cin >> response;
        if (response == 'y' || response == 'Y') {
            string filename = "invoice_" + to_string(userId) + "_" + to_string(month) + "_" + to_string(year) + ".txt";
            invoice->saveToFile(filename);
        }
        
        delete invoice;
    }
}

// ============================================================
// Display Options
// ============================================================

void Interface::displayUsersAndPlans() {
    cout << "\n--- Users & Plans Summary ---" << endl;
    
    if (users.empty()) {
        cout << "No users found." << endl;
        return;
    }
    
    cout << "\nUser ID | Name" << setw(20) << "Email" << setw(20) << "Plan" << endl;
    cout << string(70, '-') << endl;
    
    for (auto& entry : users) {
        int userId = entry.first;
        User& user = entry.second;
        string planName = subscriptions.find(userId) != subscriptions.end() ? 
                         subscriptions[userId]->getPlanName() : "Not Assigned";
        
        cout << userId << " | " << user.getName() << setw(20) << user.getEmail() 
             << setw(20) << planName << endl;
    }
}

// ============================================================
// Helper Methods
// ============================================================

int Interface::getUserIdInput() {
    cout << "\nEnter user ID: ";
    int userId;
    cin >> userId;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return userId;
}

SubscriptionPlan* Interface::getPlanInput() {
    cout << "\nSelect plan type:" << endl;
    cout << "[1] Free Plan" << endl;
    cout << "[2] Pro Plan" << endl;
    cout << "[3] Enterprise Plan" << endl;
    cout << "Choice: ";
    
    int choice;
    cin >> choice;
    
    switch (choice) {
        case 1:
            return new FreePlan();
        case 2:
            return new ProPlan();
        case 3:
            cout << "Enter negotiated rate: $";
            double rate;
            cin >> rate;
            return new EnterprisePlan(rate);
        default:
            return new FreePlan();
    }
}
