//
//  Utils.cpp
//  FinalProject
//
//  Created by Xingyuan Ding on 12/6/21.
//

#include "Utils.h"
using namespace std;

int write_data(void* ptr, int size, int nmemb, FILE* stream)
{
    size_t written;
    written = fwrite(ptr, size, nmemb, stream);
    return written;
}

void *myrealloc(void *ptr, size_t size)
{
    if (ptr)
        return realloc(ptr, size);
    else
        return malloc(size);
}

int write_data2(void *ptr, size_t size, size_t nmemb, void *data)
{
    size_t realsize = size * nmemb;
    struct MemoryStruct *mem = (struct MemoryStruct *)data;
    mem->memory = (char *)myrealloc(mem->memory, mem->size + realsize + 1);
    if (mem->memory) {
        memcpy(&(mem->memory[mem->size]), ptr, realsize);
        mem->size += realsize;
        mem->memory[mem->size] = 0;
    }
    return realsize;
}

vector<double> calculate_daily_returns(const vector<double>& prices, int index, int n) {
    vector<double> dailyReturns;
    for (int i = index - n + 1; i <= index + n; i++) {
        dailyReturns.push_back(prices[i]/prices[i-1]-1);
    }
    return dailyReturns;
}

string convertDateFormat(string earningDate) {
    return "2021-04-21";
}
