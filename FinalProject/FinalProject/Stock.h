//
//  Stock.h
//  FinalProject
//
//  Created by Xingyuan Ding on 12/3/21.
//

#ifndef Stock_h
#define Stock_h

#include <string>
#include <vector>
#include "Utils.h"
using namespace std;

enum SurprisingGroup{BEAT, MISS, MEET};

class Stock {
private:
    string ticker;
    vector<string> dates;
    vector<double> prices;
    SurprisingGroup surprisingGroup;
    int earningDateIndex;
    string earningDate;
    string periodEndDate;
    double estimate;
    double reported;
    double surprise;
    double surprisePercentage;
public:
    Stock(string ticker, vector<string> dates, vector<double> prices, string earningDate, string periodEndDate, double estimate, double reported, double surprise, double surprisePercentage): ticker(ticker), dates(dates), prices(prices), earningDate(earningDate), periodEndDate(periodEndDate), estimate(estimate), reported(reported), surprise(surprise), surprisePercentage(surprisePercentage) {
        earningDateIndex = 0;
        for (vector<string>::iterator iter = dates.begin(); iter != dates.end(); iter++) {
            if (iter->compare(convertDateFormat(earningDate)) == 0) {
                break;
            } else {
                earningDateIndex += 1;
            }
        }
    }
    void setSurprisingGroup(SurprisingGroup surprisingGroup) {
        this->surprisingGroup = surprisingGroup;
    }
    vector<double> calculateCumulativeDailyReturn() const;
    vector<double> calculateDailyReturn(const int n) const;
    void displayInformation() const;
};

struct StockPrice {
    vector<string> dates;
    vector<double> prices;
};

struct EarningInfo {
    string earningDate;
    string periodEndDate;
    double estimate;
    double reported;
    double surprise;
    double surprisePercentage;
};

#endif /* Stock_h */
