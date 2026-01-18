#pragma once

#include <vector>
#include <cmath>
#include <stdexcept>

class YieldCurve {
    std::vector<double> times;
    std::vector<double> rates;

public:
    YieldCurve(const std::vector<double>& t,
               const std::vector<double>& r)
        : times(t), rates(r)
    {
        if (times.size() != rates.size() || times.empty())
            throw std::invalid_argument("Invalid yield curve");
    }

    double zeroRate(double T) const {
        if (T <= times.front())
            return rates.front();
        if (T >= times.back())
            return rates.back();

        for (size_t i = 1; i < times.size(); ++i) {
            if (T <= times[i]) {
                double w = (T - times[i-1]) /
                           (times[i] - times[i-1]);
                return rates[i-1] +
                       w * (rates[i] - rates[i-1]);
            }
        }
        return rates.back();
    }

    double discount(double T) const {
        return std::exp(-zeroRate(T) * T);
    }
};
