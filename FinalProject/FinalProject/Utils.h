//
//  Utils.h
//  FinalProject
//
//  Created by Xingyuan Ding on 12/6/21.
//

#ifndef Utils_h
#define Utils_h

#include <fstream>
#include <vector>
using namespace std;

struct MemoryStruct {
    char *memory;
    size_t size;
};

int write_data(void* ptr, int size, int nmemb, FILE* stream);
void *myrealloc(void *ptr, size_t size);
int write_data2(void *ptr, size_t size, size_t nmemb, void *data);
vector<double> calculate_daily_returns(const vector<double>& prices, int index, int n);
string convertDateFormat(string earningDate);

#endif /* Utils_h */
