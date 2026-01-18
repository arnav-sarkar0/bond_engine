#pragma once

#include "Bond.hpp"
#include "YieldCurve.hpp"
#include "CreditCurve.hpp"
#include "Date.hpp"

class BondPricer {
public:
    static double price(
        const Bond& bond,
        const YieldCurve& yc,
        const CreditCurve& credit,
        double recoveryRate,
        const Date& valuationDate
    ) {
        double pv = 0.0;
        const auto& cfs = bond.getCashflows();

        for (const auto& cf : cfs) {
            if (cf.date() <= valuationDate)
                continue;

            double t = Date::yearFraction(valuationDate, cf.date());
            pv += cf.getAmount()
                * yc.discount(t)
                * credit.survivalProb(t);
        }

        for (size_t i = 0; i < cfs.size(); ++i) {
            if (cfs[i].date() <= valuationDate)
                continue;

            double t = Date::yearFraction(valuationDate, cfs[i].date());
            double tPrev = (i == 0) ? 0.0 :
                Date::yearFraction(valuationDate, cfs[i-1].date());

            double dp =
                credit.survivalProb(tPrev) -
                credit.survivalProb(t);

            pv += bond.getFace()
                * recoveryRate
                * yc.discount(t)
                * dp;
        }

        return pv;
    }
};
