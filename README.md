# Bond Engine

**Bond Engine** is a C++ library for pricing fixed-income bonds. The engine supports cashflow generation, yield curve discounting, survival probability adjustments, and recovery modeling.

---

## Features

- **Bond Pricing**
  - Cashflow generation (coupons & principal)
  - Discounted present value calculation
  - Survival-adjusted for default probabilities
  - Recovery modeling

- **Credit Curves**
  - Piecewise-constant hazard rate models
  - Survival probability computation
  - Default probability computation

- **Yield Curves**
  - Linear interpolation of zero rates
  - Discount factor calculation

---

## Getting Started

### Prerequisites

- C++17 compatible compiler

### Build and Run

1. Place all header files (`Date.hpp`, `CashFlow.hpp`, `Bond.hpp`, `YieldCurve.hpp`, `CreditCurve.hpp`, `BondPricer.hpp`) in the same folder.
2. Create a `main.cpp` to test the pricer (example below).
3. Compile:

```bash
c++ -std=c++17 -O2 main.cpp -o bond_engine
