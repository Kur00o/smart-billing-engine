#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <algorithm>
using namespace std;

// ── Reuse UsageRecord from usage_tracker (in real build, a shared header
//    would do this; here we just redefine it since no .h files) ──────────
struct UsageRecord {
    int apiCalls;
    double storageGB;
    int activeUsers;

    UsageRecord() : apiCalls(0), storageGB(0.0), activeUsers(0) {}
    UsageRecord(int calls, double storage, int users)
        : apiCalls(calls), storageGB(storage), activeUsers(users) {}
};

// ══════════════════════════════════════════════════════════════════════════
//  ABSTRACTION — BillingStrategy
//  Pure virtual interface. Any billing style must implement calculateBill().
//  The rest of the system only ever talks to BillingStrategy*, so swapping
//  strategies at runtime is trivial (Strategy design pattern).
// ══════════════════════════════════════════════════════════════════════════
class BillingStrategy {
public:
    virtual double calculateBill(const UsageRecord& usage) const = 0;
    virtual string strategyName() const = 0;
    virtual ~BillingStrategy() {}
};

// ── Concrete Strategy 1: Flat Rate ────────────────────────────────────────
// Charges a fixed amount regardless of how much the user actually consumed.
// Suitable for EnterprisePlan (negotiated flat rate).
class FlatRateStrategy : public BillingStrategy {
private:
    double flatAmount;

public:
    FlatRateStrategy(double amount) : flatAmount(amount) {}

    double calculateBill(const UsageRecord& /*usage*/) const override {
        // Usage doesn't affect the price at all — that's the point of flat rate
        return flatAmount;
    }

    string strategyName() const override {
        return "Flat Rate";
    }
};

// ── Concrete Strategy 2: Per-Unit ─────────────────────────────────────────
// Charges per API call + per GB of storage used.
// Suitable for ProPlan overage calculation.
class PerUnitStrategy : public BillingStrategy {
private:
    double ratePerApiCall;    // cost per single API call
    double ratePerGB;         // cost per GB of storage
    double baseCharge;        // fixed base (e.g. $29 for ProPlan)

public:
    PerUnitStrategy(double base, double perCall, double perGB)
        : baseCharge(base), ratePerApiCall(perCall), ratePerGB(perGB) {}

    double calculateBill(const UsageRecord& usage) const override {
        double bill = baseCharge;
        bill += usage.apiCalls   * ratePerApiCall;
        bill += usage.storageGB  * ratePerGB;
        return bill;
    }

    string strategyName() const override {
        return "Per-Unit";
    }
};

// ── Concrete Strategy 3: Tiered ───────────────────────────────────────────
// API calls are grouped into tiers; each tier has its own per-call rate.
// The first N calls are cheapest, the next M cost more, and so on.
// Classic SaaS usage-based pricing.
class TieredStrategy : public BillingStrategy {
private:
    // Each tier: { upper limit of this tier, rate per call within this tier }
    struct Tier {
        int  limitCalls;   // calls up to this number fall in this tier
        double ratePerCall;
    };

    vector<Tier> tiers;
    double ratePerGB;
    double baseCharge;

public:
    TieredStrategy(double base, double perGB) : baseCharge(base), ratePerGB(perGB) {
        // Example tiers (matches FreePlan overage model):
        // 0 – 1000 calls  → free ($0.00)
        // 1001 – 5000     → $0.002 per call
        // 5001+           → $0.005 per call
        tiers.push_back({1000,  0.000});
        tiers.push_back({5000,  0.002});
        tiers.push_back({INT_MAX, 0.005});
    }

    double calculateBill(const UsageRecord& usage) const override {
        double bill = baseCharge;
        int remaining = usage.apiCalls;
        int previousLimit = 0;

        for (const Tier& tier : tiers) {
            if (remaining <= 0) break;

            int callsInThisTier = min(remaining, tier.limitCalls - previousLimit);
            bill += callsInThisTier * tier.ratePerCall;
            remaining    -= callsInThisTier;
            previousLimit = tier.limitCalls;
        }

        bill += usage.storageGB * ratePerGB;
        return bill;
    }

    string strategyName() const override {
        return "Tiered";
    }
};

// ══════════════════════════════════════════════════════════════════════════
//  OPEN-CLOSED PRINCIPLE — PricingRule (abstract base)
//  Adding a new rule (e.g. surge pricing, holiday rate) means creating a
//  new subclass — you never touch PricingEngine or existing rules.
// ══════════════════════════════════════════════════════════════════════════
class PricingRule {
public:
    // Takes a bill computed so far and usage context, returns adjusted bill
    virtual double apply(double currentBill, const UsageRecord& usage) const = 0;
    virtual string ruleName() const = 0;
    virtual ~PricingRule() {}
};

// ── Concrete Rule 1: Overage Surcharge ────────────────────────────────────
// If API calls exceed a free quota, add a flat surcharge on top.
class OverageSurchargeRule : public PricingRule {
private:
    int    freeCallLimit;
    double surchargePerExtraCall;

public:
    OverageSurchargeRule(int limit, double surcharge)
        : freeCallLimit(limit), surchargePerExtraCall(surcharge) {}

    double apply(double currentBill, const UsageRecord& usage) const override {
        if (usage.apiCalls > freeCallLimit) {
            int extraCalls = usage.apiCalls - freeCallLimit;
            double surcharge = extraCalls * surchargePerExtraCall;
            cout << "[Rule] Overage surcharge applied: +" << surcharge << "\n";
            return currentBill + surcharge;
        }
        return currentBill;
    }

    string ruleName() const override {
        return "Overage Surcharge";
    }
};

// ── Concrete Rule 2: ProratedRule ─────────────────────────────────────────
// If user joined mid-month, bill only for the days they were active.
// Open-Closed: this is a brand new rule added without touching other code.
class ProratedRule : public PricingRule {
private:
    int daysActive;    // how many days the user was on the plan
    int daysInMonth;   // total days in the billing month

public:
    ProratedRule(int active, int total) : daysActive(active), daysInMonth(total) {}

    double apply(double currentBill, const UsageRecord& /*usage*/) const override {
        if (daysActive < daysInMonth && daysInMonth > 0) {
            double ratio = static_cast<double>(daysActive) / daysInMonth;
            double adjusted = currentBill * ratio;
            cout << "[Rule] Prorated (" << daysActive << "/" << daysInMonth
                 << " days): " << currentBill << " → " << adjusted << "\n";
            return adjusted;
        }
        return currentBill;
    }

    string ruleName() const override {
        return "Prorated";
    }
};

// ── Concrete Rule 3: High-Usage Bonus Discount ────────────────────────────
// If user consumed more than a threshold, reward them with a small discount.
// Shows how OCP lets us keep stacking rules without changing existing ones.
class HighUsageDiscountRule : public PricingRule {
private:
    int    callThreshold;
    double discountPercent;  // e.g. 0.05 = 5%

public:
    HighUsageDiscountRule(int threshold, double discount)
        : callThreshold(threshold), discountPercent(discount) {}

    double apply(double currentBill, const UsageRecord& usage) const override {
        if (usage.apiCalls >= callThreshold) {
            double discount = currentBill * discountPercent;
            cout << "[Rule] High-usage discount (" << discountPercent * 100
                 << "%): -" << discount << "\n";
            return currentBill - discount;
        }
        return currentBill;
    }

    string ruleName() const override {
        return "High-Usage Bonus Discount";
    }
};

// ══════════════════════════════════════════════════════════════════════════
//  PricingEngine — composes a strategy + a chain of rules
//  This is what the billing pipeline actually calls.
// ══════════════════════════════════════════════════════════════════════════
class PricingEngine {
private:
    BillingStrategy*        strategy;   // which billing model to use
    vector<PricingRule*>    rules;      // ordered list of rules to apply after

public:
    PricingEngine(BillingStrategy* strat) : strategy(strat) {}

    // Attach a rule — order matters; rules run top to bottom
    void addRule(PricingRule* rule) {
        rules.push_back(rule);
    }

    // Full pipeline step: calculateBill() → applyPricingRules()
    double applyPricingRules(const UsageRecord& usage) const {
        // Step 1: base bill from selected strategy
        double bill = strategy->calculateBill(usage);
        cout << "\n[" << strategy->strategyName() << "] Base bill: $" << bill << "\n";

        // Step 2: run every pricing rule in sequence
        for (const PricingRule* rule : rules) {
            bill = rule->apply(bill, usage);
        }

        return bill;
    }

    string getStrategyName() const {
        return strategy->strategyName();
    }

    // Destructor cleans up raw pointers
    ~PricingEngine() {
        delete strategy;
        for (PricingRule* r : rules) delete r;
    }
};

// ══════════════════════════════════════════════════════════════════════════
//  Quick local test — remove this main() when linking with main.cpp
// ══════════════════════════════════════════════════════════════════════════
/*
int main() {
    // Simulate a ProPlan user: $29 base, $0.001/call, $0.50/GB
    UsageRecord usage(7200, 15.5, 4);   // 7200 calls, 15.5 GB, 4 users

    PricingEngine engine(new PerUnitStrategy(29.0, 0.001, 0.50));
    engine.addRule(new OverageSurchargeRule(5000, 0.002));
    engine.addRule(new HighUsageDiscountRule(7000, 0.05));

    double finalBill = engine.applyPricingRules(usage);
    cout << "\nFinal Bill: $" << finalBill << "\n";

    return 0;
}
*/