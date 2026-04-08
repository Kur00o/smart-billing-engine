#pragma once

#include <map>
#include <string>
#include <iostream>
#include <ctime>
using namespace std;

// Usage Metrics Struct
struct UsageMetrics {
    long apiCalls;
    double storageGB;
    int activeUsers;
    int month;
    int year;

    UsageMetrics() 
        : apiCalls(0), storageGB(0.0), activeUsers(0), month(0), year(0) {}
};

// Usage Tracker Class
class UsageTracker {
public:
    void recordApiCall(int userId, long calls);
    void recordStorage(int userId, double gb);
    void recordUsers(int userId, int count);

    UsageMetrics getUsage(int userId, int month, int year) const;
    void resetMonthlyUsage(int userId);
    void displayUsage(int userId) const;

private:
    // Map structure: userId -> ("YYYY-MM" -> UsageMetrics)
    map<int, map<string, UsageMetrics>> usageData;

    // Helper function to create date key
    string createDateKey(int month, int year) const;
    
    // Helper function to get or create usage entry
    UsageMetrics& getOrCreateUsage(int userId, int month, int year);
};
