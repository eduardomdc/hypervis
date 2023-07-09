#include "geometry.hpp"
#include "algebra.hpp"
#include <math.h>
#include <iostream>
#include <vector>


pointnd operator+(pointnd a, pointnd b){
    if (a.vec.size() != b.vec.size()){
        std::cout<<"invalid vector addition"<<std::endl;
        return a;
    }
    for (int i=0; i<a.vec.size(); i++){
        a.vec[i] += b.vec[i];
    }
    return a;
}

pointnd operator-(pointnd a, pointnd b){
    if (a.vec.size() != b.vec.size()){
        std::cout<<"invalid vector addition"<<std::endl;
        return a;
    }
    for (int i=0; i<a.vec.size(); i++){
        a.vec[i] -= b.vec[i];
    }
    return a;
}

void printPoint(pointnd p){
    std::cout<<"[";
    for(int i=0; i<p.vec.size(); i++){
        std::cout<<p.vec[i]<<", ";
    }
    std::cout<<"]"<<std::endl;
}

object cubeface(object cube, float size, int dim, int side){
    if (dim > 0){
        std::cout<<"cubeface(dim:"<<dim-1<<");"<<std::endl;
        cube = cubeface(cube, size, dim-1, 0);
        cube = cubeface(cube, size, dim-1, 1);
    } else {
        int len = cube.points.size(); //points so far
        int d = cube.dimension;
        pointnd point;
        point.dim = d;
        for(int i=0; i < d; i++){
            point.vec.push_back(size*(((len>>i)&1)-0.5));
        }
        printPoint(point);
        cube.points.push_back(point);
        for(int i=0; i < 32; i++){//int has 32 bits
            if ((len>>i)&1){
                cube.edges.push_back({len, len-(1<<i)});
                std::cout<<"edge: "<<len<<"-"<<len-(1<<i)<<std::endl;
            }
        }
    }
    return cube;
}

object makeNCube(float size, int dim){
    object ncube;
    ncube.dimension = dim; 
    ncube = cubeface(ncube, size, dim, 0);
    std::cout<<"Created "<<dim<<"-dimensional hypercube."<<std::endl;
    std::cout<<ncube.points.size()<<" points/ "<<ncube.edges.size()<<" edges"<<std::endl;
    for(int i=0;i<ncube.points.size();i++){
        printPoint(ncube.points[i]);
    }
    return ncube;
}

object makeCube(float size){
    object cube;
    cube.dimension = 3;
    cube.numPoints = 8;
    cube.numEdges = 12;
    int count = 0;
    for (int z=0; z<=1; z+=1){
        for (int y=0; y<=1; y+=1){
            for (int x=0; x<=1; x+=1){
                pointnd* point = new pointnd();
                point->dim = 3;
                point->vec.push_back(size*(x-0.5));
                point->vec.push_back(size*(y-0.5));
                point->vec.push_back(size*(z-0.5));
                if (x==1) cube.edges.push_back({count-1, count});
                if (y==1) cube.edges.push_back({count-2, count});
                if (z==1) cube.edges.push_back({count-4, count});
                cube.points.push_back(*point);
                count++;
            }
        }
    }
    return cube;
}

object rotateAroundX(object obj, float ang){
    for (int i=0; i<obj.numPoints; i++){
        pointnd* point = &obj.points[i];
        point->vec[1] = point->vec[1]*cos(ang) - point->vec[2]*sin(ang);
        point->vec[2] = point->vec[1]*sin(ang) + point->vec[2]*cos(ang);
    }
    return obj;
}

object rotateAroundY(object obj, float ang){
    for (int i=0; i<obj.numPoints; i++){
        pointnd* point = &obj.points[i];
        point->vec[0] = point->vec[0]*cos(ang) - point->vec[2]*sin(ang);
        point->vec[2] = point->vec[0]*sin(ang) + point->vec[2]*cos(ang);
    }
    return obj;
}

object renormalizeObject(object obj){
    for (int i=0; i<obj.points.size(); i++){
        renormalize(&obj.points[i]);
    }
    return obj;
}
