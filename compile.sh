#!/bin/bash
# Smart Billing Engine - Compilation & Execution Script
# This script compiles and runs the billing engine on Linux/Mac
# For Windows: Use PowerShell commands below

# ============================================================
# WINDOWS POWERSHELL COMMANDS
# ============================================================

# Step 1: Navigate to project directory
# cd "c:\Users\hp\Desktop\Aaryan\college\oops\smart-billing-engine"

# Step 2: Compile (one line)
# g++ -std=c++17 -o billing_engine.exe main.cpp models/user.cpp models/subscription.cpp billing/billing_strategy.cpp billing/pricing_rule.cpp billing/usage_tracker.cpp billing/pricing_engine.cpp policies/discount_policy.cpp policies/tax_calc.cpp policies/addon.cpp invoice/invoice.cpp invoice/invoice_generator.cpp interface/interface.cpp

# Step 3: Execute
# .\billing_engine.exe

# ============================================================
# LINUX/MAC BASH SCRIPT
# ============================================================

# Navigate to project directory
cd "$(dirname "$0")"

echo "╔════════════════════════════════════════════════════════════╗"
echo "║   SMART BILLING ENGINE - Compilation Script               ║"
echo "╚════════════════════════════════════════════════════════════╝"

# Check if g++ is installed
if ! command -v g++ &> /dev/null; then
    echo "Error: g++ not found. Please install GCC with C++17 support."
    exit 1
fi

echo -e "\n[1/3] Compiling source files..."

# Compile all source files into a single executable
g++ -std=c++17 -o billing_engine \
    main.cpp \
    models/user.cpp \
    models/subscription.cpp \
    billing/billing_strategy.cpp \
    billing/pricing_rule.cpp \
    billing/usage_tracker.cpp \
    billing/pricing_engine.cpp \
    policies/discount_policy.cpp \
    policies/tax_calc.cpp \
    policies/addon.cpp \
    invoice/invoice.cpp \
    invoice/invoice_generator.cpp \
    interface/interface.cpp

if [ $? -eq 0 ]; then
    echo -e "✓ Compilation successful!"
    echo -e "\n[2/3] Executable created: billing_engine"
    
    # Make executable (Linux/Mac)
    chmod +x billing_engine
    
    echo -e "\n[3/3] Starting application..."
    echo -e "════════════════════════════════════════════════════════════\n"
    
    # Run the application
    ./billing_engine
else
    echo -e "✗ Compilation failed!"
    echo "Please check the error messages above."
    exit 1
fi
