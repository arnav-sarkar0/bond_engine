#include <iostream>
#include <vector>

#include "Date.hpp"
#include "Bond.hpp"
#include "YieldCurve.hpp"
#include "CreditCurve.hpp"
#include "Pricer.hpp"

int main() {
    try {
        // ----------------------------
        // Valuation date
        // ----------------------------
        Date valuationDate(2026, 1, 1);

        // ----------------------------
        // Bond definition
        // ----------------------------
        double face = 100.0;
        double couponRate = 0.05;   // 5%
        int frequency = 2;          // semi-annual

        Date issueDate(2021, 1, 1);
        Date maturityDate(2031, 1, 1);

        Bond bond(
            face,
            couponRate,
            frequency,
            issueDate,
            maturityDate
        );

        // ----------------------------
        // Yield curve (flat 4%)
        // ----------------------------
        std::vector<double> ycTimes = {0.5, 1.0, 2.0, 3.0, 5.0, 10.0};
        std::vector<double> ycRates = {0.04, 0.04, 0.04, 0.04, 0.04, 0.04};

        YieldCurve yieldCurve(ycTimes, ycRates);

        // ----------------------------
        // Credit curve (piecewise hazard)
        // ----------------------------
        std::vector<double> creditTimes = {1.0, 3.0, 5.0, 10.0};
        std::vector<double> hazards     = {0.02, 0.025, 0.03, 0.035};

        CreditCurve creditCurve(creditTimes, hazards);

        // ----------------------------
        // Pricing
        // ----------------------------
        double recoveryRate = 0.40;

        double price = BondPricer::price(
            bond,
            yieldCurve,
            creditCurve,
            recoveryRate,
            valuationDate
        );

        std::cout << "Bond price: " << price << std::endl;
    }
    catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
    }

    return 0;
}
