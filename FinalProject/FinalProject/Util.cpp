//
//  Util.cpp
//  FinalProject
//
//  Created by Hanlu Ni on 12/10/21.
//
#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <algorithm> //for sort function
include "Stock.h"
#include "Util.h"

enum SurprisingGroup { BEAT, MEET，MISS };
using namespace std;
//TranslateDate function only translate "dd-MMM-yy" or "d-MMM-yy" to "yyyy-mm-dd"
string TranslateDate(string raw) {
    int strlength = raw.size();
    string day = raw.substr(0, strlength - 7);
    string monthandyear = raw.substr(strlength - 6, strlength);
    string month = monthandyear.substr(0, 3);
    string year = monthandyear.substr(4, monthandyear.size());
    string str;
    str.append("20");
    str.append(year);
    str.append("-");
    string mm;
    if (month == "Mar") {
        mm = "03";
    }
    else if (month == "Apr") {
        mm = "04";
    }
    else if (month == "May") {
        mm = "05";
    }
    else {
        mm = "06";
    }
    str.append(mm);
    str.append("-");
    if (day.size() == 2) {
        str.append(day);
    }
    else {
        str.append("0");
        str.append(day);
    }
    return str;
}

void setStockGroup(map<string, Stock> mymap) {
    vector<pair<string, Stock>> A;
    map<string, Stock>::iterator itr;
    for (itr = mymap.begin(); itr != mymap.end(); itr++) {
        A.push_back(make_pair(itr->first, itr->second));
    }

    sort(A.begin(), A.end(), cmp);

    int count = 0;
    int a = 300;
    int b = 600;
    for (int i = 0; i < A.size(); i++) {
        if (count <= a) {
            beat.push_back(A[i].second);
            //A[i].second.setSurprisingGroup(SurprisingGroup BEAT);this line hasnt been tested
        }
        else if (count <= b) {
            meet.push_back(A[i].second);
            //A[i].second.setSurprisingGroup(SurprisingGroup MEET);this line hasnt been tested
        }
        else {
            miss.push_back(A[i].second);
            //A[i].second.setSurprisingGroup(SurprisingGroup MISS);this line hasnt been tested
        }
        count++;
    }
}
