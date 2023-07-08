#ifndef ALGEBRA
#define ALGEBRA

#include "geometry.hpp"
#include <vector>

typedef struct matrix {
    std::vector<std::vector<float>> m;
    int width;
    int height;
} matrix;

void renormalize(pointnd* vec);
matrix multiply(matrix a, matrix b);
pointnd apply(matrix t, pointnd vec);
matrix makeRotMatrix(pointnd axis, float ang);

#endif
