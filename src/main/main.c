#include <math.h>
#include <stdio.h>
#include "../include/boundary_problem.h"

real p_test1(real x) {
    return (-2) * x;
}

real q_test1(real x) {
    return -2;
}

real f_test1(real x) {
    return (-4) * x;
}

real exact_test1(real x) {
    return x + expl(x*x);
}

real p_test2(real x) {
    return (-3) * x;
}

real q_test2(real x) {
    return 2;
}

real f_test2(real x) {
    return 1.5;
}


const size_t BUF_SIZE = 80;

int main(void) {
    boundary_problem tests[] = {
        // p       q        f        a    b  c1 c2  c    d1   d2 d      n
        { p_test1, q_test1, f_test1, 0,   1, 1, -1, 0,   1,   0, 1+M_E, 10   },
        { p_test1, q_test1, f_test1, 0,   1, 1, -1, 0,   1,   0, 1+M_E, 100  },
        { p_test1, q_test1, f_test1, 0,   1, 1, -1, 0,   1,   0, 1+M_E, 1000 },
        { p_test2, q_test2, f_test2, 0.7, 1, 0, 1,  1.3, 0.5, 1, 2,     100  }
    };

    char fname[BUF_SIZE];

    for (size_t i = 0; i < 4; ++i) {
        boundary_solution solution = boundary_problem_solve(tests[i]);

        snprintf(fname, BUF_SIZE, "boundary-%zu.dat", i+1);
        print_boundary_solution(solution, fname);

        if (i < 3) {
            printf("Test %zu, error: %11.8Lf\n", i+1,
                   boundary_solution_error(solution, exact_test1));
        }
    }

    return 0;
}