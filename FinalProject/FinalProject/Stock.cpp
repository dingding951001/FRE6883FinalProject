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

void Stock::displayInformation() const {
    // subject to change based on output format
    cout << ticker << " " << earningDate << " " << earningDateIndex << endl;
}
