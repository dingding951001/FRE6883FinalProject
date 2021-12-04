//
//  Stock.h
//  FinalProject
//
//  Created by Xingyuan Ding on 12/3/21.
//

#ifndef Stock_h
#define Stock_h

#include <string>
#include "Vector.h"
using namespace std;

enum SurprisingGroup{BEAT, MISS, MEET};

class Stock {
private:
    string ticker;
    Vector<string> dates;
    Vector<double> prices;
    SurprisingGroup surprisingGroup;
    int earningDateIndex;
    string earningDate;
    string periodEndDate;
    double estimate;
    double reported;
    double surprise;
    double surprisePercentage;
public:
    Stock(String ticker, Vector<string> dates, Vector<double> prices, string earningDate, string periodEndDate, double estimate, double reported, double surprise, double surprisePercentage);
    void setSurprisingGroup(SurprisingGroup surprisingGroup);
    Vector<double> calculateCumulativeDailyReturn() const;
    Vector<double> calculateDailyReturn(const int n) const;
    void displayInformation() const;
}

#endif /* Stock_h */
