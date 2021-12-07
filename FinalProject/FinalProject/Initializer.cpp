//
//  Initializer.cpp
//  FinalProject
//
//  Created by Xingyuan Ding on 12/6/21.
//
#include <fstream>
#include <iostream>
#include <iomanip>
#include <map>
#include <sstream>
#include <stdexcept>
#include <string>
#include "curl/curl.h"
#include "Initializer.h"
#include "Stock.h"
#include "Utils.h"

using namespace std;

const char* cIWB1000SymbolFile = "Russell_1000_component_stocks - Copy.csv";
const char* earningAnnouncementFile = "EarningsAnnouncements (duplicate removed).csv";
const char* resultsFile = "Results.txt";

void Initializer::populateSymbolVector(vector<string>& symbols)
{
    ifstream fin;
    fin.open(cIWB1000SymbolFile, ios::in);
    string line, name, symbol;
    while (!fin.eof())
    {
        getline(fin, line);
        stringstream sin(line);
        getline(sin, symbol, ',');
        getline(sin, name);
        symbols.push_back(symbol);
    }
}

void Initializer::loadStockPrice(map<string, StockPrice>& stockPrices)
{
    string line;
    bool shouldInitialize = true;
    string ticker;
    vector<string> dates;
    vector<double> prices;
    ifstream f(resultsFile);
    if (f.is_open())
    {
        while (getline(f,line))
        {
            if (shouldInitialize) {
                ticker = line;
                dates = vector<string>();
                prices = vector<double>();
                shouldInitialize = false;
                continue;
            }
            if (line.compare("Date,Open,High,Low,Close,Adjusted_close,Volume") == 0)
                continue;
            vector<string> seglist;
            stringstream ss(line);
            string segment;
            while (getline(ss, segment, ','))
            {
               seglist.push_back(segment);
            }
            if (seglist.size() == 1) {
                shouldInitialize = true;
                stockPrices.insert({ticker, {dates, prices}});
            } else {
                dates.push_back(seglist[0]);
                prices.push_back(stod(seglist[5]));
            }
        }
        f.close();
    }
}

void Initializer::loadEarningInfo(map<string, EarningInfo>& earningInfos) {
    string line;
    ifstream f(earningAnnouncementFile);
    bool isFirstLine = true;
    if (f.is_open())
    {
        while (getline(f,line))
        {
            if (isFirstLine) {
                isFirstLine = false;
                continue;
            }
            vector<string> seglist;
            stringstream ss(line);
            string segment;
            while (getline(ss, segment, ','))
            {
               seglist.push_back(segment);
            }
            earningInfos.insert({seglist[0], {seglist[1],seglist[2],stod(seglist[3]),stod(seglist[4]),stod(seglist[5]),stod(seglist[6])}});
        }
    }
}

void Initializer::downloadStocksFromOnline()
{
    vector<string> symbolList;
    populateSymbolVector(symbolList);
    // file pointer to create file that store the data
    FILE* fp;
    const char resultfilename[FILENAME_MAX] = "Results.txt";
    // declaration of an object CURL
    CURL* handle;
    CURLcode result;
    // set up the program environment that libcurl needs
    curl_global_init(CURL_GLOBAL_ALL);
    // curl_easy_init() returns a CURL easy handle
    handle = curl_easy_init();
    // if everything's all right with the easy handle...
    if (handle)
    {
        string url_common = "https://eodhistoricaldata.com/api/eod/";
        string start_date = "2021-01-01";
        string end_date = "2021-11-30";
        // You must replace this API token with yours
        string api_token = "61aeb5a8def104.22282854";
        vector<string>::iterator itr = symbolList.begin();
        for (; itr != symbolList.end(); itr++)
        {
            struct MemoryStruct data;
            data.memory = NULL;
            data.size = 0;
            string symbol = *itr;
            string url_request = url_common + symbol + ".US?" + "from=" + start_date + "&to=" + end_date + "&api_token=" + api_token + "&period=d";
            curl_easy_setopt(handle, CURLOPT_URL,url_request.c_str());
            //adding a user agent
            curl_easy_setopt(handle, CURLOPT_USERAGENT,"Mozilla/5.0(Windows NT 10.0; Win64; x64; rv:74.0) Gecko/20100101Firefox/74.0");
            curl_easy_setopt(handle, CURLOPT_SSL_VERIFYPEER, 0);
            curl_easy_setopt(handle, CURLOPT_SSL_VERIFYHOST, 0);
            fp = fopen(resultfilename, "ab");
            fprintf(fp, "%s\n", symbol.c_str());
            curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, write_data);
            curl_easy_setopt(handle, CURLOPT_WRITEDATA, fp);
            result = curl_easy_perform(handle);
            fprintf(fp, "%c", '\n');
            fclose(fp);
            // check for errors
            if (result != CURLE_OK) {
                fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(result));
                throw runtime_error("curl_easy_perform() failed");
            }
            curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, write_data2);
            curl_easy_setopt(handle, CURLOPT_WRITEDATA, (void*)&data);
            // perform, then store the expected code in result
            result = curl_easy_perform(handle);
            if (result != CURLE_OK)
            {
                // if errors have occured, tell us what is wrong with result
                fprintf(stderr, "curl_easy_perform() failed: %s\n",
                curl_easy_strerror(result));
                throw runtime_error("curl_easy_perform() failed");
            }
            stringstream sData;
            sData.str(data.memory);
            string sValue, sDate;
            double dValue = 0;
            string line;
            cout << symbol << endl;
            while (getline(sData, line)) {
                size_t found = line.find('-');
                if (found != std::string::npos)
                {
                    cout << line << endl;
                    sDate = line.substr(0, line.find_first_of(','));
                    line.erase(line.find_last_of(','));
                    sValue = line.substr(line.find_last_of(',') + 1);
                    dValue = strtod(sValue.c_str(), NULL);
                    cout << sDate << " " << std::fixed << ::setprecision(2) << dValue << endl;
                }
            }
            free(data.memory);
            data.size = 0;
        }
    } else {
        fprintf(stderr, "Curl init failed!\n");
        throw runtime_error("Curl init failed!");
    }
    // cleanup since you've used curl_easy_init
    curl_easy_cleanup(handle);
    // release resources acquired by curl_global_init()
    curl_global_cleanup();
}

StockPrice Initializer::getStockPriceFromApi(string symbol) {
    CURL* handle;
    CURLcode result;
    curl_global_init(CURL_GLOBAL_ALL);
    handle = curl_easy_init();
    vector<string> dates;
    vector<double> prices;
    if (handle)
    {
        string url_common = "https://eodhistoricaldata.com/api/eod/";
        string start_date = "2021-01-01";
        string end_date = "2021-11-30";
        string api_token = "61aeb5a8def104.22282854";
        
        struct MemoryStruct data;
        data.memory = NULL;
        data.size = 0;
        string url_request = url_common + symbol + ".US?" + "from=" + start_date + "&to=" + end_date + "&api_token=" + api_token + "&period=d";
        curl_easy_setopt(handle, CURLOPT_URL,url_request.c_str());
        curl_easy_setopt(handle, CURLOPT_USERAGENT,"Mozilla/5.0(Windows NT 10.0; Win64; x64; rv:74.0) Gecko/20100101Firefox/74.0");
        curl_easy_setopt(handle, CURLOPT_SSL_VERIFYPEER, 0);
        curl_easy_setopt(handle, CURLOPT_SSL_VERIFYHOST, 0);
        curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, write_data2);
        curl_easy_setopt(handle, CURLOPT_WRITEDATA, (void*)&data);
        result = curl_easy_perform(handle);
        if (result != CURLE_OK)
        {
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
            curl_easy_strerror(result));
            throw runtime_error("curl_easy_perform() failed");
        }
        stringstream sData;
        sData.str(data.memory);
        string sValue, sDate;
        double dValue = 0;
        string line;
        while (getline(sData, line)) {
            size_t found = line.find('-');
            if (found != std::string::npos)
            {
                sDate = line.substr(0, line.find_first_of(','));
                line.erase(line.find_last_of(','));
                sValue = line.substr(line.find_last_of(',') + 1);
                dValue = strtod(sValue.c_str(), NULL);
                dates.push_back(sDate);
                prices.push_back(dValue);
            }
        }
        free(data.memory);
        data.size = 0;
    } else {
        fprintf(stderr, "Curl init failed!\n");
        throw runtime_error("Curl init failed!");
    }
    curl_easy_cleanup(handle);
    curl_global_cleanup();
    return {dates, prices};
}

Initializer::Initializer() {
    ifstream f(resultsFile);
    if (!f.good()) {
        downloadStocksFromOnline();
    }
    map<string, StockPrice> stockPrices;
    loadStockPrice(stockPrices);
    map<string, EarningInfo> earningInfos;
    loadEarningInfo(earningInfos);
    for (map<string, StockPrice>::iterator stockPriceIter = stockPrices.begin(); stockPriceIter != stockPrices.end(); stockPriceIter++) {
        string ticker = stockPriceIter->first;
        map<string, EarningInfo>::iterator earningInfoIter = earningInfos.find(ticker);
        if (earningInfoIter != earningInfos.end()) {
            StockPrice stockPrice = stockPriceIter->second;
            EarningInfo earningInfo = earningInfoIter->second;
            Stock stock(ticker, stockPrice.dates, stockPrice.prices, earningInfo.earningDate, earningInfo.periodEndDate, earningInfo.estimate, earningInfo.reported, earningInfo.surprise, earningInfo.surprisePercentage);
            stockData.insert({ticker, stock});
        }
    }
    benchmark = getStockPriceFromApi("IWB");
}
