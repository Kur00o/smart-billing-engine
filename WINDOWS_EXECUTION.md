# WINDOWS EXECUTION GUIDE - Step-by-Step

## Quick Start (Copy-Paste Ready)

### Step 1: Open PowerShell and Navigate to Project
```powershell
cd "c:\Users\hp\Desktop\Aaryan\college\oops\smart-billing-engine"
```

### Step 2: Compile the Project (One Command)
```powershell
g++ -std=c++17 -o billing_engine.exe main.cpp models/user.cpp models/subscription.cpp billing/billing_strategy.cpp billing/pricing_rule.cpp billing/usage_tracker.cpp billing/pricing_engine.cpp policies/discount_policy.cpp policies/tax_calc.cpp policies/addon.cpp invoice/invoice.cpp invoice/invoice_generator.cpp interface/interface.cpp
```

### Step 3: Run the Application
```powershell
.\billing_engine.exe
```

---

## Alternative: Step-by-Step Compilation

If you prefer compiling modules individually:

```powershell
# Navigate to project directory
cd "c:\Users\hp\Desktop\Aaryan\college\oops\smart-billing-engine"

# Compile models
g++ -std=c++17 -c models/user.cpp -o models/user.o
g++ -std=c++17 -c models/subscription.cpp -o models/subscription.o

# Compile billing modules
g++ -std=c++17 -c billing/billing_strategy.cpp -o billing/billing_strategy.o
g++ -std=c++17 -c billing/pricing_rule.cpp -o billing/pricing_rule.o
g++ -std=c++17 -c billing/usage_tracker.cpp -o billing/usage_tracker.o
g++ -std=c++17 -c billing/pricing_engine.cpp -o billing/pricing_engine.o

# Compile policies
g++ -std=c++17 -c policies/discount_policy.cpp -o policies/discount_policy.o
g++ -std=c++17 -c policies/tax_calc.cpp -o policies/tax_calc.o
g++ -std=c++17 -c policies/addon.cpp -o policies/addon.o

# Compile invoice modules
g++ -std=c++17 -c invoice/invoice.cpp -o invoice/invoice.o
g++ -std=c++17 -c invoice/invoice_generator.cpp -o invoice/invoice_generator.o

# Compile interface
g++ -std=c++17 -c interface/interface.cpp -o interface/interface.o

# Compile main
g++ -std=c++17 -c main.cpp -o main.o

# Link all object files
g++ -std=c++17 -o billing_engine.exe main.o models/user.o models/subscription.o billing/billing_strategy.o billing/pricing_rule.o billing/usage_tracker.o billing/pricing_engine.o policies/discount_policy.o policies/tax_calc.o policies/addon.o invoice/invoice.o invoice/invoice_generator.o interface/interface.o

# Run
.\billing_engine.exe
```

---

## Sample Session (What to Do After Running)

```
APPLICATION STARTS:
╔════════════════════════════════════════════════════════════╗
║   SMART SUBSCRIPTION & USAGE-BASED BILLING ENGINE          ║
║   Demonstration of OOP Principles in C++                   ║
╚════════════════════════════════════════════════════════════╝

============================================================
SMART SUBSCRIPTION & USAGE-BASED BILLING ENGINE
============================================================

[1] Manage Users
[2] Manage Subscriptions
[3] Track Usage
[4] Configure Billing
[5] Generate Invoice
[6] Display Users & Plans
[0] Exit

Enter your choice: 1          ← TYPE: 1 and press ENTER

--- Manage Users ---
[1] Add User
[2] Display All Users
[0] Back
Choice: 1                      ← TYPE: 1 and press ENTER

Enter user name: John Doe      ← TYPE: John Doe and press ENTER
Enter user email: john@example.com

✓ User added successfully! (ID: 1)

--- Manage Users ---
[1] Add User
[2] Display All Users
[0] Back
Choice: 0                      ← TYPE: 0 to go back

[1] Manage Users
[2] Manage Subscriptions
[3] Track Usage
[4] Configure Billing
[5] Generate Invoice
[6] Display Users & Plans
[0] Exit

Enter your choice: 2          ← TYPE: 2 and press ENTER

--- Manage Subscriptions ---
[1] Assign Plan to User
[2] Display All Subscriptions
[0] Back
Choice: 1                      ← TYPE: 1 and press ENTER

Enter user ID: 1              ← TYPE: 1 and press ENTER

Select plan:
[1] Free Plan
[2] Pro Plan
[3] Enterprise Plan
Choice: 2                      ← TYPE: 2 (Pro Plan)

✓ Pro Plan assigned to user 1

...and so on
```

---

## Common Issues & Solutions

### Issue 1: "g++ is not recognized"
**Solution**: 
- Download MinGW (GCC for Windows) from: https://www.mingw-w64.org/
- Add `C:\Program Files\mingw-w64\x86_64-8.1.0-posix-seh-rt_v6-rev0\mingw64\bin` to PATH
- Restart PowerShell

### Issue 2: "cannot find file"
**Solution**:
- Ensure you're in the correct directory: `cd c:\Users\hp\Desktop\Aaryan\college\oops\smart-billing-engine`
- List files to verify: `ls`

### Issue 3: Compilation takes very long
**Solution**:
- This is normal for first compilation
- Subsequent compilations will be faster
- Use `g++ -O3` to optimize for speed (after debugging)

### Issue 4: "Access denied" error
**Solution**:
- Close any open editors (VS Code, Visual Studio)
- Run PowerShell as Administrator
- Try compilation again

---

## Verification Checklist

After building, verify all files were compiled:

```powershell
# Check if executable exists
Test-Path .\billing_engine.exe

# Expected output: True

# Check file size (should be ~200-500 KB)
(Get-Item .\billing_engine.exe).Length
```

---

## Running with Different Options

### Run with Debug Output (Add flags to g++)
```powershell
g++ -std=c++17 -g -o billing_engine.exe main.cpp ... [all files]
```

### Run with Optimization (Faster execution)
```powershell
g++ -std=c++17 -O3 -o billing_engine.exe main.cpp ... [all files]
```

### Run with Warnings (Help identify potential issues)
```powershell
g++ -std=c++17 -Wall -Wextra -o billing_engine.exe main.cpp ... [all files]
```

---

## Testing After Execution

### Test Scenario 1: Basic Free Plan
```
1. Press [1] → Add User: "Test User" (test@example.com)
2. Press [2] → Assign Free Plan to user 1
3. Press [3] → Record: 500 calls, 10 GB, 2 users
4. Press [5] → Generate invoice for 4/2026
   
Expected: Bill should be $0.00 (within free limit)
```

### Test Scenario 2: Pro Plan with Overage
```
1. Press [1] → Add User: "Pro User" (pro@example.com)
2. Press [2] → Assign Pro Plan to user 2
3. Press [3] → Record: 15000 calls, 30 GB, 5 users
4. Press [5] → Generate invoice for 4/2026
   
Expected: $29 + (15000-10000)*$0.05 = $279
```

---

## File Locations

All source files are in:
```
c:\Users\hp\Desktop\Aaryan\college\oops\smart-billing-engine\
```

Structure:
```
├── main.cpp
├── models/
│   ├── user.h / user.cpp
│   └── subscription.h / subscription.cpp
├── billing/
│   ├── billing_strategy.h / .cpp
│   ├── pricing_rule.h / .cpp
│   ├── usage_tracker.h / .cpp
│   └── pricing_engine.h / .cpp
├── policies/
│   ├── discount_policy.h / .cpp
│   ├── tax_calculator.h / tax_calc.cpp
│   └── addon.h / .cpp
├── invoice/
│   ├── invoice.h / .cpp
│   └── invoice_generator.h / .cpp
└── interface/
    └── interface.h / .cpp
```

---

## Saving Invoices

After generating an invoice, the app asks if you want to save to file:
```
Save to file? (y/n): y
```

This creates files like:
- `invoice_1_4_2026.txt` (User 1, April 2026)
- `invoice_2_4_2026.txt` (User 2, April 2026)

Files are saved in the current working directory.

---

## PowerShell Usage Tips

```powershell
# Clear screen
Clear-Host

# List all files
Get-ChildItem -Recurse

# Check if file exists
Test-Path "./billing_engine.exe"

# Get file size
(Get-Item "./billing_engine.exe").Length

# Create directory
New-Item -ItemType Directory -Name "build"

# Remove compiled files (cleanup)
Remove-Item *.o, *.exe
```

---

**Last Updated**: April 8, 2026  
**Status**: Ready for Execution
