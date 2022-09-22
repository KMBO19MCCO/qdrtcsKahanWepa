//
// Created by eszdman on 18.09.22.
//

#ifndef QDRTCSKAHANWEPA_SOLVER_H
#define QDRTCSKAHANWEPA_SOLVER_H
#include <cmath>
#include <vector>
#include <cassert>
#include <iostream>
template<typename fp_t> void qdrtc(std::vector<fp_t> coefficients, std::vector<fp_t> &output);
template<typename fp_t> fp_t dscrmt(fp_t A,fp_t B,fp_t C);

#endif //QDRTCSKAHANWEPA_SOLVER_H
