//
//  Calculator.hpp
//  Team Project
//
//  Created by 张君陶 on 2021/12/8.
//

#ifndef Calculator_hpp
#define Calculator_hpp

#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <map>
#pragma once
#include "Bootstrap.hpp"

using namespace std;

typedef vector<double> Vector;
typedef vector<Vector> Matrix;

Vector operator+(Matrix &m,Vector &v);
Vector operator+(Vector &AAR, double num);
Vector AAR(Matrix &m);
Vector CAAR(const Vector &AAR);

Vector mean(const Matrix &m2);
Vector stdev(const Matrix &m2);

Matrix call_bootstrap(vector<Stock*> stocks,const StockPrice& benchmark, const int n);

#endif /* Calculator_hpp */
