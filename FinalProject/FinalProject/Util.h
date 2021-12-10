//
//  Util.h
//  FinalProject
//
//  Created by Hanlu Ni on 12/10/21.
//
#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <map>
//#include <algorithm> //for sort function
include "Stock.h"

//enum SurprisingGroup { BEAT, MEET, MISS };
using namespace std;

//TranslateDate function only translate "dd-MMM-yy" or "d-MMM-yy" to "yyyy-mm-dd"
string TranslateDate(string raw);

//want to compair the surprisePercentage of two pair<string,Stock>
bool cmp(pair<string, Stock>& a, pair<string, Stock>& b) { return a.second.getSurprisePercentage() > b.second.getSurprisePercentage(); }


class StockGroup {
private:
	vector<Stock> beat;
	vector<Stock> meet;
	vector<Stock> miss;
public:
	void setStockGroup(map<string, Stock> mymap);
	vector<Stock> getBeat() { return beat; }
	vector<Stock> getMeet() { return meet; }
	vector<Stock> getMiss() { return miss; }
};
