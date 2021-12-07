#include "Initializer.h"

#include <iostream>
using namespace std;

int main(void)
{
    Initializer initializer;
    map<string, Stock> stockData = initializer.getStockData();
    for (map<string, Stock>::iterator iter = stockData.begin(); iter != stockData.end(); iter++) {
        iter->second.displayInformation();
    }
    StockPrice benchmark = initializer.getBenchMark();
    for (int i = 0 ; i < benchmark.prices.size() ; i++) {
        cout << benchmark.dates[i] << " " << benchmark.prices[i] << endl;
    }
    return 0;
}
