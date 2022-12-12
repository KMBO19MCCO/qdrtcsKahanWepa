#pragma clang diagnostic push
#pragma ide diagnostic ignored "openmp-use-default-none"
//
// Created by eszdman on 18.09.22.
//
#include <iostream>
#include <vector>
#include <fstream>
#include <omp.h>
#include "excerpt.h"
#include "solver.h"
#define MAX_DISTANCE 10e-5
using namespace std;
typedef float fp_t;
struct bestRes {
   fp_t A,B,C;
   fp_t dev;
   fp_t relDev;
   fp_t root0,root1;
   fp_t out0,out1;
};
int main(){
    unsigned p = 2;
    ofstream *outputFile;
    int procs = omp_get_num_procs();
    auto *bestDev = new fp_t[procs]{0};
    outputFile = new ofstream[procs];
    auto *resFinal = new bestRes[procs]{0};

    #pragma omp parallel
    {
        int thread_num = omp_get_thread_num();
        outputFile[thread_num] = ofstream();
        outputFile[thread_num].open("output"+to_string(thread_num)+".txt");
        outputFile[thread_num]<<"Starting"<<endl;
    }
    #pragma omp parallel for
    for(int i = 0; i<1000*1000*1000; i++){
        vector<fp_t> roots(p);
        vector<fp_t> output(p);
        vector<fp_t> coefficients(p + 1);
        int thread_num = omp_get_thread_num();
        generate_polynomial<fp_t>(p, 0, 2, 0, MAX_DISTANCE, 0, 1, roots, coefficients);
        fp_t dev;
        fp_t relDev;
        qdrtc(coefficients,output);
        int err = compare_roots<fp_t>(p,p,output,roots,dev,relDev);
        if (err >= PR_NUMBERS_OF_ROOTS_EQUAL) {
            if (dev > bestDev[thread_num]) {
                bestDev[thread_num] = dev;
                outputFile[thread_num] << setprecision(numeric_limits<fp_t>::digits10 + 1) << "dev:"
                                       << bestDev[thread_num] << " relDev:" << relDev << " ABC:" << coefficients[2] << " "
                                       << coefficients[1] << " " << coefficients[0] << " roots:" << roots[0] << " "
                                       << roots[1] << " out:" << output[0] << " " << output[1] << endl;
                resFinal[thread_num].A = coefficients[2];
                resFinal[thread_num].B = coefficients[1];
                resFinal[thread_num].C = coefficients[0];
                resFinal[thread_num].dev = dev;
                resFinal[thread_num].relDev = relDev;
                resFinal[thread_num].root0 = roots[0];
                resFinal[thread_num].root1 = roots[1];
                resFinal[thread_num].out0 = output[0];
                resFinal[thread_num].out1 = output[1];
            }
        }

    }
    bestDev = new fp_t[procs]{0};
    bestRes bestOfBest{};
    ofstream bestFile = ofstream();
    bestFile.open("output.txt");
    for(int i =0; i<omp_get_num_procs();i++)
    {
        int thread_num = i;
        cout<<"i:"<<i<<endl;
        fp_t dev = resFinal[thread_num].dev;
        if(dev > bestDev[thread_num]){
            bestOfBest = resFinal[thread_num];
            bestDev[thread_num] = dev;
        }
        outputFile[thread_num].close();
    }
    bestFile<<setprecision(numeric_limits<fp_t>::digits10 + 1)<<"dev:"<<bestOfBest.dev << " relDev:" << bestOfBest.relDev <<" ABC:"<<bestOfBest.A<<" "
           <<bestOfBest.B<<" "<<bestOfBest.C<<" roots:"<<bestOfBest.root0<<" "<<bestOfBest.root1<<" out:"<<bestOfBest.out0<<" "<<bestOfBest.out1<<endl;
    bestFile.close();

}
#pragma clang diagnostic pop