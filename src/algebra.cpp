#include "algebra.hpp"
#include "geometry.hpp"
#include "draw.hpp"
#include "hyper.hpp"
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
    pointnd rotatedx = basis[basis.size()-2];
    pointnd rotatedy = basis[basis.size()-1];
    // go through every point of object
    // change only components of rotated plane
    for (int i=0; i<obj.points.size(); i++){
        pointnd p = obj.points[i];
        //vector components on rotation plane
        pointnd px = project(p, rotatedx); 
        pointnd py = project(p, rotatedy);
        float dotpx = dotp(px, rotatedx);
        float dotpy = dotp(py, rotatedy);
        p = p - px - py;
        float temp = dotpx;
        dotpx = dotpx*cos(ang) - dotpy*sin(ang);
        dotpy = temp*sin(ang) + dotpy*cos(ang);
        p = p + scale(rotatedx, dotpx) + scale(rotatedy, dotpy);
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

pointnd canonical(int idx, int dim){
    pointnd axis;
    axis.dim = dim;
    for (int i=0; i<dim; i++){
        if (i==idx) axis.vec.push_back(1);
        else axis.vec.push_back(0);
    }
    return axis;
}

std::vector<pointnd> rotateBasis(std::vector<pointnd> basis, std::vector<int> idxplane, float angle){
    int dim = basis[0].vec.size();
    std::vector<pointnd> projects;
    /*
    for(int i=0; i<basis.size(); i++){
        basis[i].vec[idxplane[0]] = basis[i].vec[idxplane[0]]*cos(angle) - basis[i].vec[idxplane[1]]*sin(angle);
        basis[i].vec[idxplane[1]] = basis[i].vec[idxplane[0]]*sin(angle) + basis[i].vec[idxplane[1]]*cos(angle);
    }*/
    for (int i=0; i<basis.size(); i++){
        pointnd vector = basis[i];
        //vector components on rotation plane
        pointnd a_axis = basis[idxplane[0]];
        pointnd b_axis = basis[idxplane[1]];
        pointnd va = project(vector, a_axis);
        pointnd vb = project(vector, b_axis);
        vector = vector - va - vb; // remove ones off axis
        float dotva = dotp(va, a_axis);
        float dotvb = dotp(vb, b_axis);
        float temp = dotva;
        dotva = dotva*cos(angle) - dotvb*sin(angle);
        dotvb = temp*sin(angle) + dotvb*cos(angle);
        vector = vector + scale(a_axis, dotva) + scale(b_axis, dotvb);
        basis[i] = vector;
    }
    return basis;
}

std::vector<pointnd> defaultbasis(int dimension){
    std::vector<pointnd> basis;
    for (int i=0; i<dimension; i++){
        pointnd bpoint;
        for (int j=0; j<dimension; j++){
            bpoint.vec.push_back(float(i==j));
        } 
        basis.push_back(bpoint);
    }
    return basis;
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
    return basis;
}

std::vector<pointnd> reorthogonalize(std::vector<pointnd> basis){
    for (int step=0; step<basis.size(); step++){
        for(int i=0; i<step; i++){
            basis[step] = basis[step] - project(basis[step], basis[i]);
        }
        renormalize(&basis[step]);
    }
    return basis;
}

object objBasisTransform(object obj, std::vector<pointnd> basis){
    for (int i=0; i<obj.points.size(); i++){
        pointnd tempp = obj.points[i];
        for(int j=0; j<basis.size(); j++){
            obj.points[i].vec[j] = dotp(tempp, basis[j]);
        }
    }
    return obj;
}
