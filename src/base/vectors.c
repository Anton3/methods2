#include <math.h>
#include "../include/vectors.h"

vector new_vector(size_t n) {
    vector result = malloc(sizeof(struct vector_m));
    result->storage = malloc(n * sizeof(real));
    result->dimension = n;
    return result;
}

void delete_vector(vector vec) {
    free(vec->storage);
    free(vec);
}