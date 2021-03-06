//
//  Stock.cpp
//  FinalProject
//
//  Created by Xingyuan Ding on 12/6/21.
//
#include <iostream>
#include <iomanip>
#include "Stock.h"
#include "Utils.h"
using namespace std;

vector<double> Stock::calculateCumulativeDailyReturn() const {
    vector<double> cumulativeReturns;
    for (int i = 0; i < prices.size(); i++) {
        cumulativeReturns.push_back(prices[i]/prices[0]-1);
    }
    return cumulativeReturns;
}

vector<double> Stock::calculateDailyReturn(const int n) const {
    return calculate_daily_returns(prices, earningDateIndex, n);
}

vector<double> operator-(const vector<double>& x, const vector<double>& y) {
    vector<double> z(x.size());
    for (int i = 0; i < x.size(); i++) {
        z[i] = x[i] - y[i];
    }
    return z;
}

vector<double> Stock::calculateAbnormalDailyRetrun(const StockPrice& benchmark, const int n) const {
    return calculate_daily_returns(prices, earningDateIndex, n) - calculate_daily_returns(benchmark.prices, earningDateIndex, n);
}

void Stock::displayInformation() const {
    // subject to change based on output format
    cout << ticker << " " << earningDate << " " << earningDateIndex << endl;
}
