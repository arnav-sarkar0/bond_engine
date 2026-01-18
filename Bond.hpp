#pragma once

#include <vector>
#include <stdexcept>
#include "Date.hpp"
#include "Cashflow.hpp"

class Bond {
    double face;
    double couponRate;
    int frequency;
    Date issueDate;
    Date maturityDate;

    std::vector<Cashflow> cashflows;

    void generateCashflows() {
        cashflows.clear();

        int months = 12 / frequency;
        double coupon = face * couponRate / frequency;

        // Principal at maturity
        cashflows.emplace_back(
            maturityDate,
            face,
            CashFlowType::Principal
        );

        Date payDate = maturityDate;

        while (true) {
            payDate = payDate.addMonths(-months);
            if (payDate <= issueDate)
                break;

            cashflows.emplace_back(
                payDate,
                coupon,
                CashFlowType::Coupon
            );
        }
    }

public:
    Bond(double f,
         double c,
         int freq,
         const Date& issue,
         const Date& maturity)
        : face(f),
          couponRate(c),
          frequency(freq),
          issueDate(issue),
          maturityDate(maturity)
    {
        if (frequency <= 0 || 12 % frequency != 0)
            throw std::invalid_argument("Invalid frequency");

        generateCashflows();
    }

    const std::vector<Cashflow>& getCashflows() const {
        return cashflows;
    }

    double getFace() const { return face; }
    const Date& getMaturity() const { return maturityDate; }
};
