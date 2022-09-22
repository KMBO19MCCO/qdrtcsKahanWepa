//
// Created by eszdman on 18.09.22.
//
#include <iostream>
#include <vector>
#include "excerpt.h"
#include "solver.h"
using namespace std;
typedef float fp_t;
int main(){
    unsigned p = 2;
    vector<fp_t> roots(p);
    vector<fp_t> output(p);
    vector<fp_t> coefficients(p + 1);
    auto result = generate_polynomial<fp_t>(p, 0, 2, 0, 10.0L/5, -5, 5.0L, roots, coefficients);
    cout<<"test"<<endl;
    float dev;
    output[0] = roots[0]+static_cast<fp_t>(0.001L);
    output[1] = roots[1]-static_cast<fp_t>(0.005L);
    //coefficients[0] = 3;
    //coefficients[1] = 6;
    //coefficients[2] = 1;
    qdrtc(coefficients,output);
    int res = compare_roots<fp_t>(p,p,output,roots,dev);
    cout<<"res:"<<res<<" dev:"<<dev<<" roots:"<<roots[0]<<","<<roots[1]<<" output:"<<output[0]<<","<<output[1]<<endl;
}