#include "usage_tracker.h"
#include <iomanip>
#include <sstream>
#include <ctime>

using namespace std;

// Helper function to create YYYY-MM key
string UsageTracker::createDateKey(int month, int year) const {
    stringstream ss;
    ss << year << "-" << setfill('0') << setw(2) << month;
    return ss.str();
}

// Helper function to get or create usage entry
UsageMetrics& UsageTracker::getOrCreateUsage(int userId, int month, int year) {
    string dateKey = createDateKey(month, year);
    
    if (usageData[userId].find(dateKey) == usageData[userId].end()) {
        usageData[userId][dateKey] = UsageMetrics();
        usageData[userId][dateKey].month = month;
        usageData[userId][dateKey].year = year;
    }
    
    return usageData[userId][dateKey];
}

// Record API calls for a user in current month/year
void UsageTracker::recordApiCall(int userId, long calls) {
    // Get current month/year
    time_t now = time(0);
    struct tm* timeinfo = localtime(&now);
    int month = timeinfo->tm_mon + 1;  // tm_mon is 0-based
    int year = timeinfo->tm_year + 1900;
    
    UsageMetrics& metrics = getOrCreateUsage(userId, month, year);
    metrics.apiCalls += calls;
}

// Record storage usage for a user
void UsageTracker::recordStorage(int userId, double gb) {
    time_t now = time(0);
    struct tm* timeinfo = localtime(&now);
    int month = timeinfo->tm_mon + 1;
    int year = timeinfo->tm_year + 1900;
    
    UsageMetrics& metrics = getOrCreateUsage(userId, month, year);
    metrics.storageGB += gb;
}

// Record active users count
void UsageTracker::recordUsers(int userId, int count) {
    time_t now = time(0);
    struct tm* timeinfo = localtime(&now);
    int month = timeinfo->tm_mon + 1;
    int year = timeinfo->tm_year + 1900;
    
    UsageMetrics& metrics = getOrCreateUsage(userId, month, year);
    metrics.activeUsers = count;  // Set, not accumulate
}

// Retrieve usage metrics for a specific month/year
UsageMetrics UsageTracker::getUsage(int userId, int month, int year) const {
    string dateKey = createDateKey(month, year);
    
    auto userIt = usageData.find(userId);
    if (userIt != usageData.end()) {
        auto metricsIt = userIt->second.find(dateKey);
        if (metricsIt != userIt->second.end()) {
            return metricsIt->second;
        }
    }
    
    // Return empty metrics if not found
    UsageMetrics empty;
    empty.month = month;
    empty.year = year;
    return empty;
}

// Reset monthly usage for a user
void UsageTracker::resetMonthlyUsage(int userId) {
    if (usageData.find(userId) != usageData.end()) {
        usageData[userId].clear();
    }
}

// Display all usage for a specific user
void UsageTracker::displayUsage(int userId) const {
    auto userIt = usageData.find(userId);
    
    if (userIt == usageData.end()) {
        cout << "No usage data found for user " << userId << endl;
        return;
    }
    
    cout << "\n========== Usage Summary for User " << userId << " ==========" << endl;
    
    for (const auto& entry : userIt->second) {
        const string& dateKey = entry.first;
        const UsageMetrics& metrics = entry.second;
        
        cout << "\nDate: " << dateKey << endl;
        cout << "  API Calls: " << metrics.apiCalls << endl;
        cout << "  Storage: " << fixed << setprecision(2) << metrics.storageGB << " GB" << endl;
        cout << "  Active Users: " << metrics.activeUsers << endl;
    }
    
    cout << "========================================================\n" << endl;
}