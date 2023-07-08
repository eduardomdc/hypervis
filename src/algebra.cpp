#include "algebra.hpp"
#include "geometry.hpp"
#include <cmath>
#include <cstdlib>
#include <math.h>
#include <vector>
#include <iostream>

float dotp(pointnd a, pointnd b){
    float dot = 0;
    for (int i=0; i<a.vec.size(); i++){
        dot += a.vec[i]*b.vec[i];
    }
    return dot;
}

pointnd scale(pointnd vec, float val){
    for (int i=0; i<vec.vec.size(); i++){
        vec.vec[i] = vec.vec[i]*val;
    }
    return vec;
}

pointnd project(pointnd vec, pointnd projecter){
    pointnd projected;
    float dotprod = dotp(vec, projecter);
    projected = scale(projecter, dotprod);
    return projected;
}

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

pointnd emptyPoint(int dim){
    pointnd p;
    p.dim = dim;
    for (int i=0; i<dim; i++){
        p.vec.push_back(0);
    }
    return p;
}

matrix multiply(matrix a, matrix b);
pointnd apply(matrix t, pointnd vec);

object rotateObj(object obj, std::vector<pointnd> basis, float ang){
    int dim = obj.points[0].vec.size();
    pointnd rotatedx = basis[basis.size()-1];
    pointnd rotatedy = basis[basis.size()-2];
    // go through every point of object
    // change only components of rotated plane
    for (int i=0; i<obj.points.size(); i++){
        pointnd p = obj.points[i];
        pointnd px = project(p, rotatedx); //vector components on rotation plane
        pointnd py = project(p, rotatedy);
        p = p - px - py;
        pointnd temppx = px;
        px = scale(px, cos(ang)) - scale(py, sin(ang));
        py = scale(temppx, sin(ang)) + scale(py, cos(ang));
        p = p + px + py;
        obj.points[i] = p;
    }
    return obj;
}

pointnd randomPoint(int dim){
    pointnd random;
    random.dim = dim;
    for (int i=0; i<dim; i++){
        float r = 2*((float) (rand())/(float)(RAND_MAX)) - 1;
        random.vec.push_back(r);
    }

    return random;
}

std::vector<pointnd> orthogonalbasis(std::vector<pointnd> axy){
    std::vector<pointnd> basis;
    int initialVectors = axy.size();
    int dim = axy[0].vec.size();
    for (int i=0; i< initialVectors; i++){
        basis.push_back(axy[i]);
        renormalize(&basis[i]);
    }
    for (int step=initialVectors; step<dim; step++){
        pointnd another = randomPoint(dim);//just make a linearly independent vector
        for(int i=0; i<basis.size(); i++){
            another = another - project(another, basis[i]);
        }
        renormalize(&another);
        basis.push_back(another);
    }
    std::cout<<"basis:"<<std::endl;
    for(int i=0;i<basis.size(); i++){
        printPoint(basis[i]);
    }
    return basis;
}
