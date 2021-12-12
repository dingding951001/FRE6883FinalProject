//
//  Bootstrap.cpp
//  6883FinalProject
//
//  Created by 张环欣 on 2021-12-10.
//


#include "Bootstrap.hpp"
#include <iostream>
#include <vector>
#include <random>
#include <map>



vector<vector<double>> bootstrapping(vector<Stock*> stocks,const StockPrice& benchmark, const int n)
{
    int bootstrap_num = 80;
    int len = stocks.size();
    
    vector<vector<double>> bootstrapping_result;
    
    std::default_random_engine random(time(NULL));
    std::uniform_int_distribution<double> index_dist(0, len - 1);
    
    //declaring vector of pairs of stock data
    
    for (int i = 0; i < bootstrap_num; i++)
    {
        bootstrapping_result.push_back(stocks[index_dist(random)]->calculateAbnormalDailyRetrun(benchmark,n));
    }
  
    
    return bootstrapping_result;
}
