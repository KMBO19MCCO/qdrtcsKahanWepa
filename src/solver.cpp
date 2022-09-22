//
// Created by eszdman on 18.09.22.
//
#include "solver.h"
template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

template<typename fp_t> fp_t dscrmt(fp_t A,fp_t B,fp_t C){
    fp_t p = B*B;
    fp_t q = A*C;
    //Use the hardware's FMA
    fp_t dp = std::fma(B,B,-p);
    fp_t dq = std::fma(A,C,-q);
    fp_t d = (p-q) + (dp - dq);
    return d;
}

template<typename fp_t> void qdrtc(std::vector<fp_t> coefficients, std::vector<fp_t> &roots){
    fp_t A,B,C;
    //Coefficients should be in BCA order
    A = coefficients[2];
    B = coefficients[1]/static_cast<fp_t>(-2);
    C = coefficients[0];
    fp_t d = dscrmt(A,B,C);
    std::cout<<"d:"<<d<<" d2:"<<B*B - A*C<<std::endl;
    assert(d > 0);
    fp_t S = B;
    S = std::sqrt(d)*(sgn(S) + (S==0)) + S;
    std::cout<<"S:"<<S<<std::endl;
    fp_t Z1 = S/(A);
    fp_t Z2 = (C)/S;

    roots[0] = Z1;
    roots[1] = Z2;
}

template void qdrtc<float>(std::vector<float> coefficients, std::vector<float> &output);
template float dscrmt(float A,float B,float C);

template void qdrtc<double>(std::vector<double> coefficients, std::vector<double> &output);
template double dscrmt<double>(double A,double B,double C);

template void qdrtc<long double>(std::vector<long double> coefficients, std::vector<long double> &output);

template long double dscrmt(long double A,long double B,long double C);