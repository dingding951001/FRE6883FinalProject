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
#endif /* Calculator_hpp */
using namespace std;

typedef vector<double> Vector;
typedef vector<Vector> Matrix;

//input matrix, column是时间，row是80个stock

double mean(const Vector &v){
    double summ = 0.0;
    for_each(v.begin(), v.end(), [&] (int n) {
        summ += n;});
    return summ/v.size();
}

double stdev(const Vector &v) {
    double avg = mean(v);
    double init = 0.0;
    for (int i = 0;i<v.size();i++) {
        init += pow(v[i]-avg, 2);
    }
    return sqrt(init / v.size());
}

Vector AAR_v(const Matrix &m) {
    Vector v(m.size());
    for (int i = 0;i<m.size();i++){
        v[i] = mean(m[i]);
    }
    return v;
};

double AAR_mean(Vector &AAR_v) {
    return mean(AAR_v);
}

Vector AAR_STD_v(Matrix &m){
    Vector v(m.size());
    for (int i = 0;i<m.size();i++){
        v[i] = stdev(m[i]);
    }
    return v;
};

double AAR_STD(Vector &AAR_STD_V) {
    return mean(AAR_STD_V);
}
//-------------------------------------
//CAAR_v 是vector，[AAR1, AAR1+AAR2, AAR1+AAR2+AAR3, ...]以此类推
Vector CAAR_v(const Vector &AAR_v){
    double init = 0.0;
    Vector v(AAR_v.size());
    for (int i=0;i<AAR_v.size();i++) {
        init += AAR_v[i];
        v[i] = init;
    }
    return v;
};

double CAAR_mean(Vector &CAAR_v) {
    return mean(CAAR_v);
}

double CAAR_STD_v(Vector &CAAR_v){
    return stdev(CAAR_v);
};
