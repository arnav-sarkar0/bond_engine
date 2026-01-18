#pragma once

#include <vector>
#include <cmath>
#include <stdexcept>

class CreditCurve {
    std::vector<double> times;
    std::vector<double> hazards;

public:
    CreditCurve(const std::vector<double>& t,
                const std::vector<double>& h)
        : times(t), hazards(h)
    {
        if (times.size() != hazards.size() || times.empty())
            throw std::invalid_argument("Invalid credit curve");
    }

    double survivalProb(double T) const {
        if (T < 0.0)
            throw std::invalid_argument("Negative time");

        double H = 0.0;
        double prev = 0.0;

        for (size_t i = 0; i < times.size(); ++i) {
            if (T <= times[i]) {
                H += hazards[i] * (T - prev);
                return std::exp(-H);
            }
            H += hazards[i] * (times[i] - prev);
            prev = times[i];
        }

        H += hazards.back() * (T - prev);
        return std::exp(-H);
    }
};
