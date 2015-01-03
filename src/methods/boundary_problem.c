#include <math.h>
#include <stdio.h>
#include "../include/boundary_problem.h"

boundary_solution boundary_problem_solve(boundary_problem o) {
    size_t n = o.n;
    real h = (o.b - o.a) / n;

    vector x = new_vector(n+1);
    for (size_t i = 0; i <= n; ++i) {
        vidx(x,i) = ((n-i) * o.a + i * o.b) / n;
    }

    vector p = new_vector(n-1);
    vector q = new_vector(n-1);
    vector F = new_vector(n-1);

    for (size_t i = 0; i < n-1; ++i) {
        real next_x = vidx(x, i+1);
        vidx(p,i) = o.p(next_x);
        vidx(q,i) = o.q(next_x);
        vidx(F,i) = o.f(next_x);
    }

    vector A = new_vector(n-1);
    vector B = new_vector(n-1);
    vector C = new_vector(n-1);

    for (size_t i = 0; i < n-1; ++i) {
        real one_div_h2 = 1 / (h*h);
        real p_div_2h = vidx(p,i) / (2*h);
        vidx(A,i) = one_div_h2 - p_div_2h;
        vidx(B,i) = (-2) * one_div_h2 + vidx(q,i);
        vidx(C,i) = one_div_h2 + p_div_2h;
    }

    real alpha1 = (-o.c2) / (o.c1*h - o.c2);
    real beta1  = (o.c*h) / (o.c1*h - o.c2);

    vector alpha = new_vector(n);
    vector beta  = new_vector(n);

    vidx(alpha, 0) = alpha1;
    vidx(beta,  0) = beta1;

    for (size_t i = 0; i < n-1; ++i) {
        real denominator = vidx(A,i) * vidx(alpha,i) + vidx(B,i);
        vidx(alpha, i+1) = -vidx(C,i) / denominator;
        vidx(beta,  i+1) = (vidx(F,i) - vidx(A,i)*vidx(beta,i)) / denominator;
    }

    real yn = (o.d2 * vidx(beta,n-1) + o.d * h) / (o.d2 * (1 - vidx(alpha,n-1)) + o.d1 * h);

    vector y = new_vector(n+1);
    vidx(y, n) = yn;

    for (size_t i = n; i > 0; --i) {
        vidx(y, i-1) = vidx(alpha,i-1) * vidx(y,i) + vidx(beta,i-1);
    }

    delete_vector(p);
    delete_vector(q);
    delete_vector(A);
    delete_vector(B);
    delete_vector(C);
    delete_vector(F);
    delete_vector(alpha);
    delete_vector(beta);

    boundary_solution solution = { x, y };
    return solution;
}

void print_boundary_solution(boundary_solution s, const char *fname) {
    FILE *output = fopen(fname, "w");

    size_t n = s.x->dimension;

    for (size_t i = 0; i < n; ++i) {
        fprintf(output, "%11.8Lf %11.8Lf\n", vidx(s.x, i), vidx(s.y, i));
    }

    fclose(output);
}

real boundary_solution_error(boundary_solution s, one_arg_func exact) {
    size_t n = s.x->dimension;
    real max = 0;

    for (size_t i = n/4; i < n; ++i) {
        real delta = fabsl(vidx(s.y, i) - exact(vidx(s.x, i)));
        if (max < delta) { max = delta; }
    }

    return max;
}