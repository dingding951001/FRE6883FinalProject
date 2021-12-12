//
//  Calculator.cpp
//  Team Project
//
//  Created by 张君陶 on 2021/12/8.
//

#include "Calculator.hpp"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>

using namespace std;

//Vector AAR(const &matrix);

Vector operator+(Matrix &m, Vector &v){
    for (int i = 0;i<m[0].size();i++){
        double res = 0.0;
        for (int j = 0;i<m.size();j++){
            res += m[j][i];}
        v[i] = res/m.size();} //m.size()是80
    return v;
}

Vector AAR(Matrix &m){
    Vector v(m[0].size());//也就是size 2N
    return m+v;
}


Vector CAAR(Vector &AAR){
    double init = 0.0;
    Vector v(AAR.size()); //2N
    for (int i=0;i<AAR.size();i++) {
        init += AAR[i];
        v[i] = init;
    }
    return v;
};
//---------------------------------
Vector mean(const Matrix &m2){
    Vector res(m2[0].size()); //应该是2N
    for (int i=0;i<m2[0].size();i++) { //2N
        double r=0.0;
        for (int j = 0;j<m2.size();j++){ //j<80
            r+= m2[j][i];
        }
        res[i] = r/40; //average of 40次的bootstrap
    }
    return res;
}

Vector stdev(const Matrix &m2){
    Vector avg = mean(m2);
    Vector res(m2[0].size());
    for (int i=0;i<m2[0].size();i++) {
        double r=0.0;
        for (int j = 0;j<m2.size();j++){
            r+= pow(m2[j][i]-avg[i],2);
        }
        res[i] = sqrt(r/(40-1));
    }
    return res;
}
//-----------------------------
Matrix call_bootstrap() {
    Matrix output_AAR(40);
    Matrix output_CAAR(40);
    Matrix output(4);
    for (int i=0;i<40;i++) {
        Matrix m = getBootsrap(); //function that gives me a matrix with size 80*2N
        output_AAR[i]=AAR(m); //这是个vector
        output_CAAR[i]=CAAR(output_AAR[i]);
    }
    output[0] = mean(output_AAR);
    output[1] = stdev(output_AAR);
    output[2] = mean(output_CAAR);
    output[3] = stdev(output_CAAR);
    return output;
};
