#ifndef BOUNDARY_PROBLEM_H
#define BOUNDARY_PROBLEM_H

#include "common.h"
#include "vectors.h"

typedef struct boundary_problem {
    one_arg_func p, q, f;
    real a, b;
    real c1, c2, c;
    real d1, d2, d;
    int n;
} boundary_problem;

typedef struct boundary_solution {
    vector x, y;
} boundary_solution;

boundary_solution boundary_problem_solve(boundary_problem p);

void print_boundary_solution(boundary_solution solution, const char *fname);
real boundary_solution_error(boundary_solution solution, one_arg_func exact);

#endif