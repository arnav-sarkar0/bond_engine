#pragma once

#include "Date.hpp"

enum class CashFlowType {
    Coupon,
    Principal
};

class Cashflow {
    Date paymentDate;
    double amount;
    CashFlowType type;

public:
    Cashflow(const Date& d, double a, CashFlowType t)
        : paymentDate(d), amount(a), type(t) {}

    const Date& date() const { return paymentDate; }
    double getAmount() const { return amount; }
    CashFlowType getType() const { return type; }
};
