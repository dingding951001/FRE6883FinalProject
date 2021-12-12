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

using namespace std;

typedef vector<double> Vector;
typedef vector<Vector> Matrix;

Vector operator+(Matrix &m,Vector &v);
Vector AAR(Matrix &m);
Vector CAAR(const Vector &AAR_v);

Vector mean(const Matrix &m2);
Vector stdev(const Matrix &m2);

Matrix call_bootstrap();

#endif /* Calculator_hpp */
