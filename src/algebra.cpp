#include "algebra.hpp"
#include <math.h>

void renormalize(pointnd* vec){
    float norm = 0;
    for(int i=0; i<vec->vec.size(); i++){
        norm += vec->vec[i]*vec->vec[i];
    }
    norm = sqrt(norm);
    for (int i=0; i<vec->vec.size(); i++){
        vec->vec[i] = vec->vec[i]/norm;
    }
}

matrix multiply(matrix a, matrix b);
pointnd apply(matrix t, pointnd vec);
matrix makeRotMatrix(pointnd axis, float ang);
