#ifndef GEOMETRY
#define GEOMETRY

#include <vector>

typedef struct point2d {
    float x;
    float y;
} point2d;

typedef struct pointnd {
    std::vector<float> vec;
    int dim;
} pointnd;
pointnd operator+(pointnd a, pointnd b);
pointnd operator-(pointnd a, pointnd b);

typedef struct edge {
    int idxa;
    int idxb;
} edge;

typedef struct object {
    std::vector<pointnd> points;
    std::vector<edge> edges;
    int numPoints;
    int numEdges;
    int dimension;
} object;

void printPoint(pointnd p);
object makeNCube(float size, int dim);
object makeCube(float size);
object rotateAroundX(object obj, float ang);
object rotateAroundY(object obj, float ang);
object renormalizeObject(object obj);

#endif
