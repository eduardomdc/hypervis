#include "geometry.hpp"
#include <math.h>

object makeCube(float size){
    object cube;
    cube.dimension = 3;
    cube.points = new pointnd[8];
    cube.numPoints = 8;
    cube.edges = new edge[12];
    cube.numEdges = 12;
    int pointCount = 0;
    int edgeCount = 0;
    for (float zPlane = -size/2; zPlane <= size/2; zPlane+=size){
        for (float yPlane = -size/2; yPlane <= size/2; yPlane+=size){
            for (float xPlane = -size/2; xPlane <= size/2; xPlane+=size){
                pointnd* point = &cube.points[pointCount];
                point->vec = new float[cube.dimension];
                point->dim = 3;
                point->vec[0] = xPlane;
                point->vec[1] = yPlane;
                point->vec[2] = zPlane;
                pointCount++;
            }
        }
    }
    return cube;
}

void rotateAroundX(object obj, float ang){
    for (int i=0; i<obj.numPoints; i++){
        pointnd* point = &obj.points[i];
        point->vec[1] = point->vec[1]*cos(ang) - point->vec[2]*sin(ang);
        point->vec[2] = point->vec[1]*sin(ang) + point->vec[2]*cos(ang);
    }
}
