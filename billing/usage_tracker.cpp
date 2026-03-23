#include <iostream>
#include <map>
#include <string>
using namespace std;

// UsageRecord holds all three usage dimensions for a given month
struct UsageRecord {
    int apiCalls;
    double storageGB;
    int activeUsers;

    UsageRecord() : apiCalls(0), storageGB(0.0), activeUsers(0) {}
    UsageRecord(int calls, double storage, int users)
        : apiCalls(calls), storageGB(storage), activeUsers(users) {}
};

// UsageTracker — Encapsulation demo
// usageData is private; outside code can only interact through methods
class UsageTracker {
private:
    // key = "YYYY-MM" (e.g. "2025-03"), value = usage for that month
    map<string, UsageRecord> usageData;
    string userId;

public:
    UsageTracker(const string& uid) : userId(uid) {}

    // Record usage for a specific month
    void recordUsage(const string& month, int apiCalls, double storageGB, int activeUsers) {
        // If an entry already exists, add on top of it (usage accumulates)
        usageData[month].apiCalls     += apiCalls;
        usageData[month].storageGB    += storageGB;
        usageData[month].activeUsers   = activeUsers; // active users = snapshot, not cumulative
    }

    // Primary pipeline entry point: getUsage()
    UsageRecord getUsage(const string& month) const {
        auto it = usageData.find(month);
        if (it != usageData.end()) {
            return it->second;
        }
        // Return zeroed record if no data exists for that month
        return UsageRecord();
    }

    // Utility: print usage summary for a month
    void printUsage(const string& month) const {
        UsageRecord rec = getUsage(month);
        cout << "========== Usage Report ==========\n";
        cout << "User ID     : " << userId << "\n";
        cout << "Month       : " << month << "\n";
        cout << "API Calls   : " << rec.apiCalls << "\n";
        cout << "Storage     : " << rec.storageGB << " GB\n";
        cout << "Active Users: " << rec.activeUsers << "\n";
        cout << "==================================\n";
    }

    // Utility: check if any data recorded for that month
    bool hasData(const string& month) const {
        return usageData.find(month) != usageData.end();
    }

    string getUserId() const { return userId; }
};