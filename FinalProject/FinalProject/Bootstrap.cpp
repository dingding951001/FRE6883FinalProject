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



bool myfunction(pair<Stock*, double> a, pair<Stock*, double> b)
{
    return a.second < b.second;
}


map<string, vector<Stock*>> bootstrapping(vector<Stock*> stocks, int seed)
{
    int bootstrap_num = 80;
    int len = stocks.size();
    
    map<string, vector<Stock*>> bootstrapping_result;
    
    default_random_engine random(time(NULL) + seed);
    std::uniform_real_distribution<double> dist(0.0, 1.0);
    
    //declaring vector of pairs of stock data
    vector< pair<Stock*,double> > vect;
    for (int i = 0; i < len; i++)
    {
        vect.push_back(pair<Stock*,double>(stocks[i], dist(random)));
    }

    sort(vect.begin(), vect.end(), myfunction);
    
    // Miss
    vector<Stock*> miss;
    for (auto iter : vect)
    {
        if ((iter.first->getSurprisingGroup() == MISS))
        {
            miss.push_back(iter.first);
            if (miss.size() == bootstrap_num) break;
        }
    }
    
    // Meet
    vector<Stock*> meet;
    for (auto iter : vect)
    {
        if ((iter.first->getSurprisingGroup() == MEET) )
        {
            meet.push_back(iter.first);
            if (meet.size() == bootstrap_num) break;
        }
    }


    // Beat
    vector<Stock*> beat;
    for (auto iter : vect)
    {
        if ((iter.first->getSurprisingGroup() == BEAT) )
        {
            beat.push_back(iter.first);
            if (beat.size() == bootstrap_num) break;
        }
    }

    bootstrapping_result["MISS"] = miss;
    bootstrapping_result["MEET"] = meet;
    bootstrapping_result["BEAT"] = beat;

    return bootstrapping_result;
}
