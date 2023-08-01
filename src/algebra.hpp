#ifndef ALGEBRA
#define ALGEBRA

#include "geometry.hpp"
#include <vector>

typedef struct matrix {
    std::vector<std::vector<float>> m;
    int width;
    int height;
} matrix;

pointnd randomPoint(int dim);
pointnd emptyPoint(int dim);
pointnd canonical(int idx, int dim);
float dotp(pointnd a, pointnd b);
pointnd scale(pointnd vec, float val);
pointnd project(pointnd vec, pointnd projecter);
void renormalize(pointnd* vec);
matrix multiply(matrix a, matrix b);
pointnd apply(matrix t, pointnd vec);
object rotateObj(object obj, std::vector<pointnd> axy, float ang);
object objBasisTransform(object obj, std::vector<pointnd> basis);
std::vector<pointnd> defaultbasis(int dimension);
std::vector<pointnd> orthogonalbasis(std::vector<pointnd> axy);
std::vector<pointnd> reorthogonalize(std::vector<pointnd> basis);
std::vector<pointnd> rotateBasis(std::vector<pointnd> basis, std::vector<int> idxplane, float angle);
#endif
